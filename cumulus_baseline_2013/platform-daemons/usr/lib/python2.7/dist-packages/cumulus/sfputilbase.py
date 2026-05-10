#! /usr/bin/python
#--------------------------------------------------------------------------
#
# Copyright 2012 Cumulus Networks, inc  all rights reserved
#
#--------------------------------------------------------------------------
try:
	import fcntl
	import struct
	import sys
	import time
	import binascii
	import os
	import getopt
	import re
	import bcmshell
	import pprint
	import eeprom_dts
	from math import log10
	from sff8472 import sff8472InterfaceId
	from sff8472 import sff8472Dom
	from sff8472 import sff8436QsfpInterfaceId
	from sff8472 import sff8436QsfpDom

except ImportError, e:
    raise ImportError (str(e) + "- required module not found")

class SfpUtilError(Exception):
        """Base class for exceptions in this module."""
        pass

class DeviceTreeError(SfpUtilError):
        """Exception raised when unable to find SFP device attributes in the device tree."""

        def __init__(self, value):
                self.value = value
        def __str__(self):
                return repr(self.value)

class sfputilbase(object):
	""" Base class for sfp utility. This class
	provides base eeprom read attributes and methods common
	to most platforms."""

	# Physical port range
	port_start = 1
	port_end = 52

	# List to specify filter for sfp_ports
	# Needed by platforms like dni-6448 which
	# have only a subset of ports that support sfp
	sfp_ports = []

	# List of logical port names available on a system
	""" ['swp1', 'swp5', 'swp6', 'swp7', 'swp8' ...] """
	logical = []

	# dicts for easier conversions between logical, physical and bcm ports
	logical_to_bcm = {}

	logical_to_physical = {}

	"""
	phytab_mappings stores mapping between logical, physical and bcm ports
	from /var/lib/cumulus/phytab
	For a normal non-ganged port:
	'swp8': {'bcmport': 'xe4', 'physicalport': [8], 'phyid': ['0xb']}

	For a ganged 40G/4 port:
	'swp1': {'bcmport': 'xe0', 'physicalport': [1, 2, 3, 4], 'phyid': ['0x4', '0x5', '0x6', '0x7']}

	For ganged 4x10G port:
	'swp52s0': {'bcmport': 'xe51', 'physicalport': [52], 'phyid': ['0x48']},
	'swp52s1': {'bcmport': 'xe52', 'physicalport': [52], 'phyid': ['0x49']},
	'swp52s2': {'bcmport': 'xe53', 'physicalport': [52], 'phyid': ['0x4a']},
	'swp52s3': {'bcmport': 'xe54', 'physicalport': [52], 'phyid': ['0x4b']},
	"""
	phytab_mappings = {}

	physical_to_logical = {}

	physical_to_phyaddrs = {}

	port_to_i2cbus_mapping = None
	port_to_eeprom_mapping = None


	_qsfp_ports = []
	_identity_eeprom_addr = 0x50
	_dom_eeprom_addr = 0x51
	_sfp_device_type = '24c02'

	def __init__(self, port_num):
		self.port_num = port_num
		self._bcm_port = self._get_bcm_port(port_num)
		self.eeprom_ifraw = None
		self.eeprom_domraw = None

		if self.is_valid_port(port_num) == 0:
			print 'Error: Invalid port num'
			return None

		# Read interface id eeprom at addr 0x50
		self.eeprom_ifraw = self._read_eeprom_devid(port_num,
						self._identity_eeprom_addr, 0)
		# Read dom eeprom at addr 0x51
		self.eeprom_domraw = self._read_eeprom_devid(port_num,
						self._dom_eeprom_addr, 0)


	def _get_bcm_port(self, port_num):
		bcm_port = None

		logical_port = sfputilbase.physical_to_logical.get(port_num)
		if logical_port != None and len(logical_port) > 0 :
			bcm_port = sfputilbase.logical_to_bcm.get(logical_port[0])

		if bcm_port == None:
			bcm_port = 'xe' + '%d' %(port_num - 1)

		return bcm_port

	def _get_port_i2c_adapter_id(self, port_num):
		if len(self.port_to_i2cbus_mapping) == 0:
			return -1

		return self.port_to_i2cbus_mapping.get(port_num, -1)

	# Adds new sfp device on i2c adapter/bus via i2c bus new_device
	# sysfs attribute
	def _add_new_sfp_device(self, sysfs_sfp_i2c_adapter_path, devaddr):
		try:
			sysfs_nd_path = sysfs_sfp_i2c_adapter_path + '/new_device'

			# Write device address to new_device file
			nd_file = open(sysfs_nd_path, 'w')
			nd_str = self._sfp_device_type + ' ' + hex(devaddr)
			nd_file.write(nd_str)
			nd_file.close()

		except Exception, err:
			print 'Error writing to new device file ', str(err)
			return 1
		else:
			return 0


	# Deletes sfp device on i2c adapter/bus via i2c bus delete_device
	# sysfs attribute
	def _delete_sfp_device(self, sysfs_sfp_i2c_adapter_path, devaddr):
		try:
			sysfs_nd_path = sysfs_sfp_i2c_adapter_path + '/delete_device'
			print devaddr > sysfs_nd_path

			# Write device address to delete_device file
			nd_file = open(sysfs_nd_path, 'w')
			nd_file.write(devaddr)
			nd_file.close()
		except Exception, err:
			print 'Error writing to delete device file ', str(err)
			return 1
		else:
			return 0


	# Returns 1 if sfp eeprom found. Returns 0 otherwise
	def _sfp_present(self, sysfs_sfp_i2c_client_eeprompath, offset):
		"""Tries to read the eeprom file to determine if the
		device/sfp is present or not. If sfp present, the read returns
		valid bytes. If not, read returns error 'Connection timed out"""

		if not os.path.exists(sysfs_sfp_i2c_client_eeprompath):
			return 0
		else:
			try:
				sysfsfile = open(sysfs_sfp_i2c_client_eeprompath
						 ,"r+b")
				sysfsfile.seek(offset)
				sysfsfile.read(1)
			except IOError:
				return 0
			except:
				return 0
			else:
				return 1


	# Read eeprom
	def _read_eeprom_devid(self, port_num, devid, offset):
		sysfs_i2c_adapter_base_path='/sys/class/i2c-adapter'
		eeprom_raw = []
		num_bytes = 256

		for i in range (0, num_bytes):
			eeprom_raw.append('0x00')

		if port_num in self.port_to_eeprom_mapping.keys():
			sysfs_sfp_i2c_client_eeprom_path = self.port_to_eeprom_mapping[port_num]
		else:
			sysfs_i2c_adapter_base_path='/sys/class/i2c-adapter'

			i2c_adapter_id = self._get_port_i2c_adapter_id(port_num)
			if i2c_adapter_id == None:
				print 'Error getting i2c bus num'
				return Non

			# Get i2c virtual bus path for the sfp
			sysfs_sfp_i2c_adapter_path = sysfs_i2c_adapter_base_path + \
					 	'/i2c-' + str(i2c_adapter_id)


			# If i2c bus for port does not exist
			if not os.path.exists(sysfs_sfp_i2c_adapter_path):
				print ('Could not find i2c bus %s'
					%sysfs_sfp_i2c_adapter_path +
					'. Driver not loaded ?')
				return None

			sysfs_sfp_i2c_client_path = sysfs_sfp_i2c_adapter_path + \
				'/' + str(i2c_adapter_id) + '-' + '00' + hex(devid)[-2:]


			# If sfp device is not present on bus, Add it
			if not os.path.exists(sysfs_sfp_i2c_client_path):
				ret = self._add_new_sfp_device(
						sysfs_sfp_i2c_adapter_path, devid)
				if ret != 0:
					print("error adding sfp device")
					return None

			sysfs_sfp_i2c_client_eeprom_path = \
				sysfs_sfp_i2c_client_path + '/eeprom'

		if self._sfp_present(sysfs_sfp_i2c_client_eeprom_path, offset) == 0:
			return None


		try:
			sysfsfile_eeprom = open(
					sysfs_sfp_i2c_client_eeprom_path,"r+b")
			sysfsfile_eeprom.seek(offset)
			raw = sysfsfile_eeprom.read(num_bytes)
		except IOError:
			print ('Error: reading sysfs file %s' %
				sysfs_sfp_i2c_client_eeprom_path)
			return None

		try:
			for n in range(0, num_bytes):
				eeprom_raw[n] = hex(ord(raw[n]))[2:].zfill(2)
		except:
			return None

		try:
			sysfsfile_eeprom.close()
		except:
			return 0

		return eeprom_raw


	def get_interface_eeprom_bytes(self):
		return self.eeprom_ifraw

	def get_dom_eeprom_bytes(self):
		return self.eeprom_domraw

	def is_valid_port(self, port_num):
		if port_num >= self.port_start and port_num <= self.port_end:
			return 1
		else:
			return 0

	def get_sfp_data(self, port_num):
		"""Returns dictionary of interface and dom data.
		format: {<port_num> : {'interface': {'version' : '1.0',
						     'data' : {
							...
							}},
					'dom' : {'version' : '1.0',
						 'data' : {
						...
						}}}}
		"""

		sfp_data = {}

		if self.eeprom_ifraw == None:
			return None

		if port_num in self._qsfp_ports:
			sfpi_obj = sff8436QsfpInterfaceId(self.eeprom_ifraw)
			if sfpi_obj != None:
				sfp_data['interface'] = sfpi_obj.get_data_pretty()
			# For Qsfp's the dom data is part of eeprom_if_raw
			# The first 128 bytes

			sfpd_obj = sff8436QsfpDom(self.eeprom_ifraw)
			if sfpd_obj != None:
				sfp_data['dom'] = sfpd_obj.get_data_pretty()
			return sfp_data

		sfpi_obj = sff8472InterfaceId(self.eeprom_ifraw)
		if sfpi_obj != None:
			sfp_data['interface'] = sfpi_obj.get_data_pretty()
			cal_type = sfpi_obj.get_calibration_type()

		if self.eeprom_domraw != None:
			sfpd_obj = sff8472Dom(self.eeprom_domraw, cal_type)
			if sfpd_obj != None:
				sfp_data['dom'] = sfpd_obj.get_data_pretty()

		return sfp_data

	@classmethod
	def read_porttab_mappings(cls, porttabfile):
		logical = []
		logical_to_bcm = {}
		logical_to_physical = {}
		physical_to_logical = {}
		last_physical_port = 0
		last_logical_port = ''
		first = 1

		try:
			f = open(porttabfile)
		except:
			raise

		# Read the porttab file and generate dicts
		# with mapping for future reference.
		# XXX: move the porttab
		# parsing stuff to a separate module, or reuse
		# if something already exists
		for line in f:
			line.strip()
			if len(line) < 4:
				continue
			if re.search('^#', line) != None:
				continue
			(logical_port, bcm_port) = line.split()[:2]

			if re.match('xe', bcm_port) == None:
				continue

			physical_port = logical_port.split('swp').pop()
			physical_port = int(physical_port.split('s').pop(0))

			if ((len(cls.sfp_ports) > 0) and
				(physical_port not in cls.sfp_ports)):
				continue

			if first == 1:
				# Initialize last_[physical|logical]_port
				# to the first valid port
				last_physical_port = physical_port
				last_logical_port = logical_port
				first = 0

			logical.append(logical_port)

			logical_to_bcm[logical_port] = bcm_port
			logical_to_physical[logical_port] = [physical_port]
			if physical_to_logical.get(physical_port) == None:
				physical_to_logical[physical_port] = [logical_port]
			else:
				physical_to_logical[physical_port].append(
					logical_port)

			if (physical_port - last_physical_port) > 1:
				# last port was a gang port
				for p in range (last_physical_port+1,
						physical_port):
					logical_to_physical[last_logical_port].append(p)
					if physical_to_logical.get(p) == None:
						physical_to_logical[p] = [last_logical_port]
					else:
						physical_to_logical[p].append(
							last_logical_port)

			last_physical_port = physical_port
			last_logical_port  = logical_port

		sfputilbase.logical = logical
		sfputilbase.logical_to_bcm = logical_to_bcm
		sfputilbase.logical_to_physical = logical_to_physical
		sfputilbase.physical_to_logical = physical_to_logical

		"""
		print 'logical:'
		print sfputilbase.logical
		print 'logical to bcm:'
		print sfputilbase.logical_to_bcm
		print 'logical to physical:'
		print sfputilbase.logical_to_physical
		print 'physical to logical:'
		print sfputilbase.physical_to_logical
		"""

	@classmethod
	def read_phytab_mappings(cls, phytabfile):
		logical = []
		phytab_mappings = {}
		physical_to_logical = {}
		physical_to_phyaddrs = {}

		try:
			f = open(phytabfile)
		except:
			raise

		# Read the phytab file and generate dicts
		# with mapping for future reference.
		# XXX: move the phytabfile
		# parsing stuff to a separate module, or reuse
		# if something already exists
		for line in f:
			line = line.strip()
			line = re.sub(r'\s+', ' ', line)
			if len(line) < 4:
				continue
			if re.search('^#', line) != None:
				continue
			(phy_addr, logical_port, bcm_port, type) = line.split(' ', 3)

			if re.match('xe', bcm_port) == None:
				continue

			lport = re.findall('swp(\d+)s*(\d*)', logical_port)
			if lport != None:
				lport_tuple = lport.pop()
				physical_port  = int(lport_tuple[0])
			else:
				physical_port = logical_port.split('swp').pop()
				physical_port = int(physical_port.split('s').pop(0))



			# Some platforms have a list of physical sfp ports
			# defined. If such a list exists, check to see if this
			# port is blacklisted
			if ((len(cls.sfp_ports) > 0) and
				(physical_port not in cls.sfp_ports)):
				continue

			if logical_port not in logical:
				logical.append(logical_port)

			if phytab_mappings.get(logical_port) == None:
				phytab_mappings[logical_port] = {}
				phytab_mappings[logical_port]['physicalport'] = []
				phytab_mappings[logical_port]['phyid'] = []
				phytab_mappings[logical_port]['type'] = type


			# If the port is 40G/4 ganged, there will be multiple
			# physical ports corresponding to the logical port.
			# Generate the next physical port number in the series
			# and append it to the list
			tmp_physical_port_list = phytab_mappings[logical_port]['physicalport']
			if (type == '40G/4' and
				physical_port in tmp_physical_port_list):
				# Aha!...ganged port
				new_physical_port = tmp_physical_port_list[-1] + 1
			else:
				new_physical_port = physical_port

			if (new_physical_port not in
					phytab_mappings[logical_port]['physicalport']):
				phytab_mappings[logical_port]['physicalport'].append(new_physical_port)
			phytab_mappings[logical_port]['phyid'].append(phy_addr)
			phytab_mappings[logical_port]['bcmport'] = bcm_port

			# Store in physical_to_logical dict
			if physical_to_logical.get(new_physical_port) == None:
				physical_to_logical[new_physical_port] = []
			physical_to_logical[new_physical_port].append(logical_port)

			# Store in physical_to_phyaddrs dict
			if physical_to_phyaddrs.get(new_physical_port) == None:
				physical_to_phyaddrs[new_physical_port] = []
			physical_to_phyaddrs[new_physical_port].append(phy_addr)

		sfputilbase.logical = logical
		sfputilbase.phytab_mappings = phytab_mappings
		sfputilbase.physical_to_logical = physical_to_logical
		sfputilbase.physical_to_phyaddrs = physical_to_phyaddrs

		"""
		pp = pprint.PrettyPrinter(indent=4)
		pp.pprint(sfputilbase.phytab_mappings)

		print 'logical:'
		print sfputilbase.logical
		print 'logical to bcm:'
		print sfputilbase.logical_to_bcm
		print 'phytab mappings:'
		print sfputilbase.phytab_mappings
		print 'physical to logical:'
		print sfputilbase.physical_to_logical
		print 'physical to phyaddrs:'
		print sfputilbase.physical_to_phyaddrs
		"""

	@staticmethod
	def get_physical_to_logical(port_num):
		"""Returns list of logical ports for the given physical port"""

		return sfputilbase.physical_to_logical[port_num]

	@staticmethod
	def get_logical_to_physical(logical_port):
		"""Returns list of physical ports for the given logical port"""
		return sfputilbase.logical_to_physical[logical_port]

	@classmethod
	def is_logical_port(cls, port):
		if port in cls.logical:
			return 1
		else:
			return 0

	@classmethod
	def is_logical_port_ganged_40_by_4(cls, logical_port):
		physical_port_list = sfputilbase.logical_to_physical[logical_port]
		if len(physical_port_list) > 1:
			return 1
		else:
			return 0

	@classmethod
	def is_physical_port_ganged_40_by_4(cls, port_num):
		logical_port = cls.get_physical_to_logical(port_num)
		if logical_port != None:
			return cls.is_logical_port_ganged_40_by_4(logical_port[0])

		return 0

	@classmethod
	def get_physical_port_phyid(cls, physical_port):
		"""Returns list of phyids for a physical port"""
		return cls.physical_to_phyaddrs[physical_port]

	@classmethod
	def get_40_by_4_gangport_phyid(cls, logical_port):
		""" Return the first ports phyid. One use case
		for this is to address the gang port in
		single mode """
		phyid_list = cls.phytab_mappings[logical_port]['phyid']
		if phyid_list != None:
			return phyid_list[0]

	@classmethod
	def is_valid_sfputil_port(cls, port):
		if port.startswith('swp'):
			if cls.is_logical_port(port):
				return 1
			else:
				return 0
		else:
			return 0

	@classmethod
	def read_port_mappings(cls):
		if cls.port_to_eeprom_mapping is None or cls.port_to_i2cbus_mapping is  None:
			cls.read_port_to_eeprom_mapping()
			cls.read_port_to_i2cbus_mapping()

	@classmethod
	def read_port_to_eeprom_mapping(cls):
		eeprom_dev = '/sys/class/eeprom_dev'
		cls.port_to_eeprom_mapping = {}
		for eeprom_path in [ os.path.join(eeprom_dev, x) for x in os.listdir(eeprom_dev) ]:
			eeprom_label = open(os.path.join(eeprom_path, 'label'), 'r').read().strip()
			if eeprom_label.startswith('port'):
				port = int(eeprom_label[4:])
				cls.port_to_eeprom_mapping[port] = os.path.join(eeprom_path, 'device', 'eeprom')

	@classmethod
	def read_port_to_i2cbus_mapping(cls):
		if cls.port_to_i2cbus_mapping is not None and len(cls.port_to_i2cbus_mapping) > 0:
			return

		cls.eep_dict = eeprom_dts.get_dev_attr_from_dtb(['sfp'])
		if len(cls.eep_dict) == 0:
			return

		# XXX: there should be a cleaner way to do this.
		i2cbus_list = []
		cls.port_to_i2cbus_mapping = {}
		s = cls.port_start
		for sfp_sysfs_path, attrs in sorted(cls.eep_dict.iteritems()):
			i2cbus = attrs.get('dev-id')
			if i2cbus == None:
				raise DeviceTreeError("No 'dev-id' attribute found in attr: " + repr(attrs))
			if i2cbus in i2cbus_list:
				continue
			i2cbus_list.append(i2cbus)
			cls.port_to_i2cbus_mapping[s] = i2cbus
			s = s + 1
			if s > cls.port_end:
                                break

class sfputil_bcm_mdio(sfputilbase):
    """Provides SFP+/QSFP EEPROM access via BCM MDIO methods"""

    _identity_eeprom_addr = 0xa000
    _dom_eeprom_addr = 0xa200

    def __init__(self, port_num):
        sfputilbase.__init__(self, port_num)

    def _read_eeprom_devid(self, port_num, devid, offset):
            """
            Reads 256 bytes of data from specified devid
            using the bcmshell's 'phy' command..

            Use port_num to identify which EEPROM to read.
            """
            eeprom_raw = None
            num_bytes = 256
            phy_addr = None
            bcm_port = None

            # Register Offsets and Constants
            eeprom_addr = 0x8007
            twowire_control_reg = 0x8000
            twowire_control_enable_mask = 0x8000
            twowire_control_read_cmd_mask = 0x0002
            twowire_control_cmd_status_mask    = 0xc
            twowire_control_cmd_status_idle    = 0x0
            twowire_control_cmd_status_success = 0x4
            twowire_control_cmd_status_busy    = 0x8
            twowire_control_cmd_status_failed  = 0xc

            twowire_internal_addr_reg = 0x8004
            twowire_internal_addr_regval = eeprom_addr

            twowire_transfer_size_reg = 0x8002
            twowire_transfer_size_regval = num_bytes

            twowire_transfer_slaveid_addr_reg = 0x8005
            twowire_transfer_slaveid_addr = 0x0001 | devid

            try:
                    bcm = bcmshell.bcmshell()
            except:
                    raise RuntimeError('unable to obtain exclusive access'
                            ' to hardware')

            ganged_40_by_4 = sfputilbase.is_physical_port_ganged_40_by_4(port_num)
            if ganged_40_by_4 == 1:
                # In 40G/4 gang mode, the port is by default configured in
                # single mode. To read the individual sfp details, the port
                # needs to be in quad mode. Set the port mode to quad mode
                # for the duration of this function. Switch it back to
                # original state after we are done
                logical_port = sfputilbase.get_physical_to_logical(port_num)
                gang_phyid = sfputilbase.get_40_by_4_gangport_phyid(logical_port[0])

                # Set the gang port to quad mode
                chip_mode_reg = 0xc805
                chip_mode_mask = 0x1

                # /usr/lib/cumulus/bcmcmd phy raw c45 <phyid> 1 <mode_reg_addr> <mode_mask>
                # Eg: /usr/lib/cumulus/bcmcmd phy raw c45 0x4 1 0xc805 0x0070
                gang_chip_mode_orig = self._phy_reg_get(bcm, gang_phyid, None, chip_mode_reg)
                quad_mode_mask = gang_chip_mode_orig & ~(chip_mode_mask)
                self._phy_reg_set(bcm, gang_phyid, None, chip_mode_reg, quad_mode_mask)

                phy_addr = sfputilbase.get_physical_port_phyid(port_num)[0]

            if phy_addr == None:
                bcm_port = self._get_bcm_port(port_num)

            # Enable 2 wire master
            regval = self._phy_reg_get(bcm, phy_addr, bcm_port,
                                       twowire_control_reg)
            regval = regval | twowire_control_enable_mask
            self._phy_reg_set(bcm, phy_addr, bcm_port,
                              twowire_control_reg, regval)

            # Set 2wire internal addr reg
            self._phy_reg_set(bcm, phy_addr, bcm_port,
                              twowire_internal_addr_reg,
                              twowire_internal_addr_regval)

            # Set transfer count
            self._phy_reg_set(bcm, phy_addr, bcm_port,
                              twowire_transfer_size_reg,
                              twowire_transfer_size_regval)

            # Set eeprom dev id
            self._phy_reg_set(bcm, phy_addr, bcm_port,
                              twowire_transfer_slaveid_addr_reg,
                              twowire_transfer_slaveid_addr)

            # Initiate read
            regval = self._phy_reg_get(bcm, phy_addr, bcm_port,
                                       twowire_control_reg)
            regval = regval | twowire_control_read_cmd_mask
            self._phy_reg_set(bcm, phy_addr, bcm_port,
                              twowire_control_reg, regval)

            # Read command status
            regval = self._phy_reg_get(bcm, phy_addr, bcm_port,
                                       twowire_control_reg)
            cmd_status = regval & twowire_control_cmd_status_mask

            # poll while command busy
            poll_count = 0
            while cmd_status == twowire_control_cmd_status_busy:
                regval = self._phy_reg_get(bcm, phy_addr, bcm_port,
                                           twowire_control_reg)
                cmd_status = regval & twowire_control_cmd_status_mask
                poll_count += 1
                if poll_count > 500:
                    raise RuntimeError("Timeout waiting for two-wire transaction completion");

            if cmd_status == twowire_control_cmd_status_success:
                # Initialize return buffer
                eeprom_raw = []
                for i in range (0, num_bytes):
                    eeprom_raw.append('0x00')

                # Read into return buffer
                for i in range(0, num_bytes):
                    addr = eeprom_addr + i
                    out = self._phy_reg_get(bcm, phy_addr, bcm_port, addr)
                    eeprom_raw[i] = hex(out)[2:].zfill(2)

            if ganged_40_by_4 == 1:
                # Restore original ganging mode
                self._phy_reg_set(bcm, gang_phyid, bcm_port,
                                  chip_mode_reg, gang_chip_mode_orig)

            return eeprom_raw

    def _phy_reg_get(self, bcm, phy_addr, bcm_port, regaddr):
        if phy_addr != None:
            cmd = ('phy raw c45 ' + phy_addr + ' 1 ' + '0x%x' %regaddr)
        else:
            cmd = ('phy ' + bcm_port + ' ' + '0x%x' %regaddr +
                    ' 1')

        try:
            out = bcm.run(cmd)
        except:
            raise RuntimeError('Error getting access to hardware'
                    ' (bcm cmd \'' + cmd + '\' failed')

        return int(out.split().pop(), 16)

    def _phy_reg_set(self, bcm, phy_addr, bcm_port, regaddr, regval):
        if phy_addr != None:
            cmd = ('phy raw c45 ' + phy_addr + ' 1 ' + '0x%x' %regaddr +
                   ' ' + '0x%x' %regval)
        else:
            cmd = ('phy ' + bcm_port + ' ' + '0x%x' %regaddr +
                    ' 1 ' + '0x%x' %regval)

        try:
            return bcm.run(cmd)
        except:
            raise RuntimeError('Error getting access to hardware'
                    ' (bcm cmd ' + cmd + ' failed')
