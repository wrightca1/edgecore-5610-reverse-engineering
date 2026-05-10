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
	import types
	from math import log10
except ImportError, e:
    raise ImportError (str(e) + "- required module not found")

#------------------------------------------------------------------------------

class sff8472(object):
	"""Class to parse and interpret sff8472 spec for
	Diagnostic monittoring interface for optical transceivers"""

	_indent = '\t'

	transceiver_codes = {	'10GEthernetComplianceCode':
				{'offset':3,
			 	 'size':1,
				 'type' : 'bitmap',
				 'decode' : {'10G Base-ER':
						{'offset': 3,
			 		 	 'bit': 7},
					     '10G Base-LRM':
						{'offset': 3,
			 		 	 'bit': 6},
					     '10G Base-LR':
						{'offset': 3,
			 		 	 'bit': 5},
					     '10G Base-SR':
						{'offset': 3,
						 'bit': 4}}},
				'InfinibandComplianceCode':
				{'offset':3,
				 'size':1,
				 'type' : 'bitmap',
				 'decode' : {'1X SX':
						{'offset': 3,
						 'bit': 3},
					     '1X LX':
						{'offset': 3,
						 'bit': 2},
					     '1X Copper Active':
						{'offset': 3,
				 	 	 'bit': 1},
					     '1X Copper Passive':
						{'offset': 3,
				 	 	 'bit': 0}}},
				'ESCONComplianceCodes':
				{'offset':4,
			 	 'size':1,
				 'type' : 'bitmap',
				 'decode' : {'ESCON MMF, 1310nm LED':
						{'offset': 4,
			 			'bit': 7},
					     'ESCON SMF, 1310nm Laser':
						{'offset': 4,
			 			'bit': 6}}},
				'SONETComplianceCodes':
				{'offset': 4,
				 'size':2,
				 'type' : 'bitmap',
				 'decode' : {	'OC-192, short reach':
							{'offset': 4,
				 	 	 	'bit': 5},
						'SONET reach specifier bit 1':
							{'offset': 4,
				 	 		 'bit': 4},
				 		'SONET reach specifier bit 2':
							{'offset': 4,
				 	 	 	'bit': 3},
				 		'OC-48, long reach':
							{'offset': 4,
				 	 	 	'bit': 2},
				 		'OC-48, intermediate reach':
							{'offset': 4,
				 	 		 'bit': 1},
				 		'OC-48, short reach':
							{'offset': 4,
				  			 'bit': 0},
				 		'OC-12, single mode, long reach':
							{'offset': 5,
							 'bit': 6},
				 		'OC-12, single mode, inter reach':
							{'offset': 5,
				 	 		 'bit': 5},
				 		'OC-12, short reach':
							{'offset': 5,
				 	 		 'bit': 4},
				 		'OC-3, single mode, long reach':
							{'offset': 5,
				 	 		 'bit': 2},
				 		'OC-3, single mode, inter reach':
							{'offset': 5,
				 	 		 'bit': 1},
				 		'OC-3, short reach':
							{'offset': 5,
				 	 		 'bit': 0}}},
				'EthernetComplianceCodes':
					{'offset': 6,
				 	 'size':2,
			 		 'type' : 'bitmap',
					 'decode' : {
						'BASE-PX':
							{'offset': 6,
			 	 			 'bit': 7},
			 			'BASE-BX10':
							{'offset': 6,
			 	 			'bit': 6},
			 			'100BASE-FX':
							{'offset': 6,
			 	 			'bit': 5},
			 			'100BASE-LX/LX10':
							{'offset': 6,
			 	 			'bit': 4},
			 			'1000BASE-T':
							{'offset': 6,
			 	 			'bit': 3},
			 			'1000BASE-CX':
							{'offset': 6,
			 	 			'bit': 2},
			 			'1000BASE-LX':
							{'offset': 6,
			 	 			'bit': 1},
			 			'1000BASE-SX':
							{'offset': 6,
			 	 			'bit': 0}}},
				'FibreChannelLinkLength':
					{'offset': 7,
				 	 'size':2,
					 'type' : 'bitmap',
					 'decode' :
						{'very long distance (V)':
							{'offset': 7,
			 	 			'bit': 7},
			 			'short distance (S)':
							{'offset': 7,
			 	 			'bit': 6},
						'Intermediate distance (I)':
							{'offset': 7,
			 	 			'bit': 5},
			 			'Long distance (L)':
							{'offset': 7,
			 	 			'bit': 4},
			 			'medium distance (M)':
							{'offset': 7,
				 			'bit': 3}}},
			     	'FibreChannelTechnology':
					{'offset': 7,
				 	 'size':2,
					 'type' : 'bitmap',
					 'decode' :
						{'Shortwave laser, linear Rx (SA)':
							{'offset': 7,
			 	 			 'bit': 2},
			 			'Longwave Laser (LC)':
							{'offset': 7,
			 	 			'bit': 1},
			 			'Electrical inter-enclosure (EL)':
							{'offset': 7,
				 			 'bit': 0},
			 			'Electrical intra-enclosure (EL)':
							{'offset': 8,
			 	 			'bit': 7},
			 			'Shortwave laser w/o OFC (SN)':
							{'offset': 8,
			 	 			'bit': 6},
			 			'Shortwave laser with OFC (SL)':
							{'offset': 8,
			 	 			'bit': 5},
			 			'Longwave laser (LL)':
							{'offset': 8,
			 	 			'bit': 4}}},
				'SFP+CableTechnology':
					{'offset': 7,
				 	 'size':2,
					 'type' : 'bitmap',
					 'decode' :
						{'Active Cable':
							{'offset': 8,
			 	 			'bit': 3},
			 			'Passive Cable':
							{'offset': 8,
			 				 'bit': 2}}},
			    	'FibreChannelTransmissionMedia':
					{'offset': 7,
				 	 'size':2,
					 'type' : 'bitmap',
					 'decode' :
						{'Twin Axial Pair (TW)':
							{'offset': 9,
			 	 			 'bit': 7},
			 			 'Twisted Pair (TP)':
							{'offset': 9,
			 	 			'bit': 6},
			 			'Miniature Coax (MI)':
							{'offset': 9,
			 	 			'bit': 5},
			 			'Video Coax (TV)':
							{'offset': 9,
			 	 			'bit': 4},
			 			'Multimode, 62.5um (M6)':
							{'offset': 9,
			 	 			'bit': 3},
			 			'Multimode, 50um (M5, M5E)':
							{'offset': 9,
			 	 			'bit': 2},
			 			'Single Mode (SM)':
							{'offset': 9,
			 	 			'bit': 0}}},
				'FibreChannelSpeed':
					{'offset': 7,
				 	 'size':2,
				 	 'type': 'bitmap',
					 'decode' :
						{'1200 MBytes/sec':
							{'offset': 10,
			 	 			'bit': 7},
			 			'800 MBytes/sec':
							{'offset': 10,
			 	 			'bit': 6},
			 			'1600 MBytes/sec':
							{'offset': 10,
			 	 			'bit': 5},
						'400 MBytes/sec':
							{'offset': 10,
			 	 			'bit': 4},
			 			'200 MBytes/sec':
							{'offset': 10,
			 	 			'bit': 2},
						'100 MBytes/sec':
							{'offset': 10,
			 	 			'bit': 0}}}}

	type_of_transceiver = {'00':'Unknown',
			       '01':'GBIC',
			       '02': 'Module soldered to motherboard',
			       '03': 'SFP or SFP Plus',
			       '04': '300 pin XBI',
			       '05': 'XENPAK',
			       '06': 'XFP',
			       '07': 'XFF',
			       '08': 'XFP-E',
			       '09': 'XPAK',
			       '0a': 'X2',
			       '0b': 'DWDM-SFP',
			       '0d': 'QSFP'}

	exttypeoftransceiver = {'00': 'GBIC def not specified',
				'01':'GBIC is compliant with MOD_DEF 1',
				'02':'GBIC is compliant with MOD_DEF 2',
				'03':'GBIC is compliant with MOD_DEF 3',
				'04':'GBIC/SFP defined by twowire interface ID',
				'05':'GBIC is compliant with MOD_DEF 5',
				'06':'GBIC is compliant with MOD_DEF 6',
				'07':'GBIC is compliant with MOD_DEF 7'}

	connector = {'00': 'Unknown',
		     '01': 'SC',
		     '02': 'Fibre Channel Style 1 copper connector',
		     '03': 'Fibre Channel Style 2 copper connector',
		     '04': 'BNC/TNC',
		     '05': 'Fibre Channel coaxial headers',
		     '06': 'FibreJack',
		     '07': 'LC',
		     '08': 'MT-RJ',
		     '09': 'MU',
		     '0a': 'SG',
		     '0b': 'Optical pigtail',
		     '0C': 'MPO Parallel Optic',
		     '20': 'HSSDCII',
		     '21': 'CopperPigtail',
		     '22': 'RJ45'}

	encoding_codes = {'00':'Unspecified',
			  '01':'8B/10B',
			  '02':'4B/5B',
			  '03':'NRZ',
			  '04':'Manchester',
			  '05': 'SONET Scrambled',
			  '06':'64B/66B'}

	rate_identifier = {'00':'Unspecified',
			   '01':'Defined for SFF-8079 (4/2/1G Rate_Select & AS0/AS1)',
			   '02': 'Defined for SFF-8431 (8/4/2G Rx Rate_Select only)',
			   '03':'Unspecified',
			   '04': 'Defined for SFF-8431 (8/4/2G Tx Rate_Select only)',
			   '05':'Unspecified',
			   '06':'Defined for SFF-8431 (8/4/2G Independent Rx & Tx Rate_select)',
			   '07':'Unspecified',
			   '08': 'Defined for FC-PI-5 (16/8/4G Rx Rate_select only) High=16G only, Low=8G/4G',
			   '09': 'Unspecified',
			   '0a': 'Defined for FC-PI-5 (16/8/4G Independent Rx, Tx Rate_select) High=16G only, Low=8G/4G'}


	interface_id = {'TypeOfTransceiver':
				{'offset':0,
			 	 'size':1,
			 	 'type' : 'enum',
			 	 'decode' : type_of_transceiver},
			 'ExtIdentOfTypeOfTransceiver':
				{'offset':1,
			 	 'size':1,
				 'type' : 'enum',
				 'outlevel' : 2,
				 'decode': exttypeoftransceiver},
			 'Connector':
				{'offset':2,
				 'size':1,
				 'type' : 'enum',
				 'decode': connector},
			'EncodingCodes':
				{'offset':11,
				 'size':1,
				 'type' : 'enum',
				 'decode' : encoding_codes},
			'VendorName':
				{'offset' : 20,
				 'size' : 16,
				 'type' : 'str'},
			'VendorOUI':
				{'offset':20,
				 'size':3,
				 'type' : 'str'},
			'VendorPN':
				{'offset':40,
				 'size':16,
				 'type' : 'str'},
			'VendorSN':
				{'offset':68,
				 'size':16,
				 'type' : 'str'},
			'VendorRev':
				{'offset':56,
				 'size':4,
				 'type' : 'str'},
			'CalibrationType':
				{'offset':92,
				 'size':1,
				 'type' : 'bitmap',
				 'short_name' : 'calType',
				 'decode' : {'Internally Calibrated':
						{'offset': 92,
						 'bit':5},
					     'Externally Calibrated':
						{'offset': 92,
						 'bit':4},
					         }},
			'ReceivedPowerMeasurementType':
				{'offset':92,
				 'size':1,
				 'type' : 'bitmap',
				 'decode' : {'Avg power':
						{'offset': 92,
						 'bit':3},
					     'OMA':
						{'offset': 92,
						 'bit':3,
					         'value':0}}},
			'RateIdentifier':
				{'offset':13,
			 	 'size':1,
				 'type' : 'enum',
				 'decode' : rate_identifier},
			'TransceiverCodes':
				{'offset' : 3,
				 'type' : 'nested',
				 'decode' : transceiver_codes},
			'NominalSignallingRate(UnitsOf100Mbd)':
				{'offset': 12,
			 	 'size':1,
				 'type':'int'},
			'LengthSMFkm-UnitsOfKm':
				{'offset':14,
			 	 'size':1,
				 'type':'int'},
			'LengthSMF(UnitsOf100m)':
				{'offset':15,
			 	 'size':1,
				 'type':'int'},
			'Length50um(UnitsOf10m)':
				{'offset':16,
			 	'size':1,
				 'type':'int'},
			'Length62.5um(UnitsOfm)':
				{'offset':17,
			 	'size':1,
				 'type':'int'},
			'LengthCable(UnitsOfm)':
				{'offset':18,
			 	'size':1,
				 'type':'int'},
			'LengthOM3(UnitsOf10m)':
				{'offset':19,
			 	 'size':1,
				 'type':'int'},
			'VendorDataCode(YYYY-MM-DD Lot)':
				{'offset':84,
			 	'size':8,
			 	'type': 'date'}}

	def inc_indent(self):
		self._indent += '\t'

	def dec_indent(self):
		self._indent = self._indent[:-1]


	# Convert Hex to String
	def convertHexToString(self, arr, start, end):
		try:
			ret_str = ''
			for n in range(start, end):
				ret_str += arr[n]
			return str.strip(binascii.unhexlify(ret_str))
		except Exception, err:
			return str(err)

	# Convert Date to String
	def convertDateToString(self, eeprom_data, offset, size):
		try:
			year_offset  = 0
			month_offset = 2
			day_offset   = 4
			lot_offset   = 6

			date = self.convertHexToString(eeprom_data, offset, offset + size)
			retval = "20"+ date[year_offset:month_offset] + "-" + \
					date[month_offset:day_offset] + "-" + \
					date[day_offset:lot_offset] + " " + \
					date[lot_offset:size]
		except Exception, err:
			retval = str(err)
		return retval

	def test_bit(self, n, bitpos):
		try:
			mask = 1 << bitpos
			if (n & mask) == 0:
				return 0
			else:
				return 1
		except:
			return -1

	def twos_comp(self, num, bits):
		try:
			if ((num & (1 << (bits - 1))) != 0):
				num = num - (1 << bits)
			return num
		except:
			return 0

	def mw_to_dbm(self, mW):
		if mW == 0:
			return float("-inf")
		elif mW < 0:
			return float("NaN")
		return 10. * log10(mW)


	def power_in_dbm_str(self, mW):
		return "%.4f%s" % (self.mw_to_dbm(mW), "dBm")

	# Parse sff8472 base elements
	def parse_sff8472_element(self, eeprom_data, eeprom_ele, start_pos):
		value = None
		offset = eeprom_ele.get('offset') + start_pos
		size = eeprom_ele.get('size')
		type = eeprom_ele.get('type')
		decodeinfo = eeprom_ele.get('decode');
		if type == 'enum':
			# Get the matched value
			value = decodeinfo.get(str(eeprom_data[offset]),
						'Unknown')
		elif type == 'bitmap':
			# Get the 'on' bitname
			bitvalue_dict = {}
			for bitname, bitinfo in sorted(decodeinfo.iteritems()):
				bitinfo_offset = bitinfo.get('offset') + start_pos
				bitinfo_pos = bitinfo.get('bit')
				bitinfo_value = bitinfo.get('value')
				data = int(eeprom_data[bitinfo_offset], 16)
				bit_value = self.test_bit(data, bitinfo_pos)
				if bitinfo_value != None:
					if bit_value == bitinfo_value:
						value = bitname
						break
				elif bit_value == 1:
					value = bitname
					break
		elif type == 'bitvalue':
			# Get the value of the bit
			bitpos = eeprom_ele.get('bit')
			data = int(eeprom_data[offset], 16)
			bitval = self.test_bit(data, bitpos)
			value = ['Off', 'On'][bitval]
		elif type == 'func':
			# Call the decode func to get the value
			value = decodeinfo['func'](self, eeprom_data,
						 offset, size)
		elif type == 'str':
			value = self.convertHexToString(eeprom_data, offset,
						      offset + size)
		elif type == 'int':
			data = int(eeprom_data[offset], 16)
			if data != 0:
				value = data
		elif type == 'date':
			value = self.convertDateToString(eeprom_data, offset,
						      size)

		return value

	# Recursively parses sff8472 data into dictionary
	def parse_sff8472(self, eeprom_map, eeprom_data, start_pos):
		outdict = {}
		for name, meta_data in sorted(eeprom_map.iteritems()):
			type = meta_data.get('type')

			# Initialize output value
			value_dict = {}
			value_dict['outtype'] = meta_data.get('outtype')
			value_dict['short_name'] = meta_data.get('short_name')

			if type != 'nested':
				data = self.parse_sff8472_element(eeprom_data,
							  	  meta_data, start_pos)
			else:
				nested_map = meta_data.get('decode')
				data = self.parse_sff8472(nested_map,
							 eeprom_data, start_pos)
			if data != None:
				value_dict['value'] = data
				outdict[name] = value_dict

		return outdict


	# Main SF8472 parser function
	def parse(self, eeprom_map, eeprom_data, start_pos):
		""" Example Return format:
		{'version': '1.0', 'data': {'Length50um(UnitsOf10m)':
		{'outtype': None, 'value': 8, 'short_name': None},
		'TransceiverCodes': {'outtype': None, 'value':
		{'10GEthernetComplianceCode': {'outtype': None, 'value':
		'10G Base-SR', 'short_name': None}}, 'short_name': None},
		'ExtIdentOfTypeOfTransceiver': {'outtype': None, 'value':
		'GBIC/SFP func defined by two-wire interface ID', 'short_name':
		 None}, 'Length62.5um(UnitsOfm)': {'outtype': None,"""

		outdict = {}
		return_dict = {}

		outdict = self.parse_sff8472(eeprom_map, eeprom_data, start_pos)

		return_dict['version'] = self.version
		return_dict['data'] = outdict

		return return_dict


	# Returns sff8472 parsed data in a pretty dictionary format
	def get_data_pretty_dict(self, indict):
		outdict = {}

		for elem, elem_val in sorted(indict.iteritems()):
			value = elem_val.get('value')
			if type(value) == types.DictType:
				outdict[elem] = sff8472.get_data_pretty_dict(
								self, value)
			else:
				outdict[elem] = value

		return outdict

	def get_data_pretty(self, indata):
		"""Example Return format:
		{'version': '1.0', 'data': {'Length50um(UnitsOf10m)': 8,
		'TransceiverCodes': {'10GEthernetComplianceCode':
		'10G Base-SR'}, 'ExtIdentOfTypeOfTransceiver': 'GBIC/SFP func
		defined by two-wire interface ID', 'Length62.5um(UnitsOfm)': 3,
		 'VendorPN': 'FTLX8571D3BNL', 'RateIdentifier': 'Unspecified',
		 'NominalSignallingRate(UnitsOf100Mbd)': 103, 'VendorOUI': ..}}
		{'version': '1.0', 'data': {'AwThresholds':
		{'TXPowerLowWarning': '-5.0004 dBm', 'TempHighWarning':
		'88.0000C', 'RXPowerHighAlarm': '0.0000 dBm',
		'TXPowerHighAlarm': '-0.7998 dBm', 'RXPowerLowAlarm':
		'-20.0000 dBm', 'RXPowerHighWarning': '-1.0002 dBm',
		'VoltageLowAlarm': '2.9000Volts'"""

		return_dict = {}

		return_dict['version'] = indata.get('version')
		return_dict['data'] = self.get_data_pretty_dict(indata.get(
								'data'))
		return return_dict

	# Dumps dict in pretty format
	def dump_pretty(self, indict):
		for elem, elem_val in sorted(indict.iteritems()):
			if type(elem_val) == types.DictType:
				print self._indent, elem, ': '
				self.inc_indent()
				sff8472.dump_pretty(self, elem_val)
				self.dec_indent()
			elif type(elem_val) == types.ListType:
				if len(elem_val) == 1:
					print (self._indent, elem, ': ',
						elem_val.pop())
				else:
					print self._indent, elem, ': '
					self.inc_indent()
					for e in elem_val:
						print self._indent, e
					self.dec_indent()
			else:
				print self._indent, elem, ': ', elem_val



class sff8472InterfaceId(sff8472):
	"""Parser and interpreter for Two wire Interface ID Data fields
	- Address A0h

	Base types:
	XXX - Complete documentation

	outtype - can be used to dictate the type of output you get
	Mainly used with bitmap type.
	if outtype == 'allbits':
		parse gives all bitnames with values
	if outtype == 'onbits':
		parse gives all onbits with value = None
	"""

	version = '1.0'

	# Returns calibration type
	def _get_calibration_type(self, eeprom_data):
		try:
			data = int(eeprom_data[92], 16)
        		if self.test_bit(data, 5) != 0:
				return 1  # internally calibrated
			elif self.test_bit(data, 4) != 0:
				return 2  # externally calibrated
			else:
				return 0  # Could not find calibration type
		except:
			return 0

	def __init__(self, eeprom_raw_data=None):
		self.interface_data = None
		start_pos = 0

		if eeprom_raw_data != None:
			self.interface_data = sff8472.parse(self,
							sff8472.interface_id,
							eeprom_raw_data, start_pos)
			self.calibration_type = self._get_calibration_type(
							eeprom_raw_data)

	def parse(self, eeprom_raw_data, start_pos):
		return sff8472.parse(self, self.interface_id, eeprom_raw_data, start_pos)

	def dump_pretty(self):
		if self.interface_data == None:
			print 'Object not initialized, nothing to print'
			return
		sff8472.dump_pretty(self, self.interface_data)

	def get_calibration_type(self):
		return self.calibration_type

	def get_data(self):
		return self.interface_data

	def get_data_pretty(self):
		return sff8472.get_data_pretty(self, self.interface_data)


class sff8472Dom(sff8472):
	"""Parser and interpretor for Diagnostics data fields at address A2h"""

	version = '1.0'

	dom_ext_calibration_constants = {'RX_PWR_4':
						{'offset':56,
				 		 'size':4},
					'RX_PWR_3':
						{'offset':60,
				 	 	'size':4},
			     		'RX_PWR_2':
						{'offset':64,
				 		 'size':4},
			     		'RX_PWR_1':
						{'offset':68,
				 		 'size':4},
			     		'RX_PWR_0':
						{'offset':72,
				 		 'size':4},
			     		'TX_I_Slope':
						{'offset':76,
				 		 'size':2},
					'TX_I_Offset':
						{'offset':78,
						 'size':2},
					'TX_PWR_Slope':
						{'offset':80,
						 'size':2},
					'TX_PWR_Offset':
						{'offset':82,
						 'size':2},
					'T_Slope':
						{'offset':84,
						 'size':2},
					'T_Offset':
						{'offset':86,
						 'size':2},
					'V_Slope':
						{'offset':88,
						 'size':2},
					'V_Offset':
						{'offset':90,
						 'size':2}}


	def get_calibration_type(self):
		return self._calibration_type

	def calc_temperature(self, eeprom_data, offset, size):
		try:
			cal_type = self.get_calibration_type()

			msb = int(eeprom_data[offset], 16)
			lsb = int(eeprom_data[offset + 1], 16)

			result = (msb << 8) | (lsb & 0xff)
			result = self.twos_comp(result, 16)

			if cal_type == 1:

				# Internal calibration

				result = float(result / 256.0)
				retval = '%.4f' %result + 'C'
			elif cal_type == 2:

				# External calibration

				# T(C) = T_Slope * T_AD + T_Offset
				off = self.dom_ext_calibration_constants['T_Slope']['offset']
				msb_t = int(eeprom_data[off], 16)
				lsb_t = int(eeprom_data[off + 1], 16)
				t_slope = (msb_t << 8) | (lsb_t & 0xff)

				off = self.dom_ext_calibration_constants['T_Offset']['offset']
				msb_t = int(eeprom_data[off], 16)
				lsb_t = int(eeprom_data[off + 1], 16)
				t_offset = (msb_t << 8) | (lsb_t & 0xff)
				t_offset = self.twos_comp(t_offset, 16)

				result = t_slope * result + t_offset
				result = float(result / 256.0)
				retval = '%.4f' %result + 'C'
			else:
				retval = 'Unknown'
		except Exception, err:
			retval = str(err)

		return retval


	def calc_voltage(self, eeprom_data, offset, size):
		try:
			cal_type = self.get_calibration_type()

			msb = int(eeprom_data[offset], 16)
			lsb = int(eeprom_data[offset + 1], 16)
			result = (msb << 8) | (lsb & 0xff)

			if cal_type == 1:

				# Internal Calibration

				result = float(result * 0.0001)
				#print indent, name, ' : %.4f' %result, 'Volts'
				retval = '%.4f' %result + 'Volts'
			elif cal_type == 2:

				# External Calibration

				# V(uV) = V_Slope * VAD + V_Offset
				off = self.dom_ext_calibration_constants['V_Slope']['offset']
				msb_v = int(eeprom_data[off], 16)
				lsb_v = int(eeprom_data[off + 1], 16)
				v_slope = (msb_v << 8) | (lsb_v & 0xff)

				off = self.dom_ext_calibration_constants['V_Offset']['offset']
				msb_v = int(eeprom_data[off], 16)
				lsb_v = int(eeprom_data[off + 1], 16)
				v_offset = (msb_v << 8) | (lsb_v & 0xff)
				v_offset = self.twos_comp(v_offset, 16)

				result = v_slope * result + v_offset
				result = float(result * 0.0001)
				#print indent, name, ' : %.4f' %result, 'Volts'
				retval = '%.4f' %result + 'Volts'
			else:
				#print indent, name, ' : Unknown'
				retval = 'Unknown'
		except Exception, err:
			retval = str(err)

		return retval


	def calc_bias(self, eeprom_data, offset, size):
		try:
			cal_type = self.get_calibration_type()

			msb = int(eeprom_data[offset], 16)
			lsb = int(eeprom_data[offset + 1], 16)
			result = (msb << 8) | (lsb & 0xff)

			if cal_type == 1:
				# Internal Calibration

				result = float(result * 0.002)
				#print indent, name, ' : %.4f' %result, 'mA'
				retval = '%.4f' %result + 'mA'

			elif cal_type == 2:
				# External Calibration

				# I(uA) = I_Slope * I_AD + I_Offset
				off = self.dom_ext_calibration_constants['I_Slope']['offset']
				msb_i = int(eeprom_data[off], 16)
				lsb_i = int(eeprom_data[off + 1], 16)
				i_slope = (msb_i << 8) | (lsb_i & 0xff)

				off = self.dom_ext_calibration_constants['I_Offset']['offset']
				msb_i = int(eeprom_data[off], 16)
				lsb_i = int(eeprom_data[off + 1], 16)
				i_offset = (msb_i << 8) | (lsb_i & 0xff)
				i_offset = self.twos_comp(i_offset, 16)

				result = i_slope * result + i_offset
				result = float(result * 0.002)
				#print indent, name, ' : %.4f' %result, 'mA'
				retval = '%.4f' %result + 'mA'
			else:
				retval = 'Unknown'
		except Exception, err:
			retval = str(err)

		return retval


	def calc_tx_power(self, eeprom_data, offset, size):
		try:
			cal_type = self.get_calibration_type()

			msb = int(eeprom_data[offset], 16)
			lsb = int(eeprom_data[offset + 1], 16)
			result = (msb << 8) | (lsb & 0xff)

			if cal_type == 1:

				result = float(result * 0.0001)
				#print indent, name, ' : ', power_in_dbm_str(result)
				retval = self.power_in_dbm_str(result)

			elif cal_type == 2:

				# TX_PWR(uW) = TX_PWR_Slope * TX_PWR_AD + TX_PWR_Offset
				off = self.dom_ext_calibration_constants['TX_PWR_Slope']['offset']
				msb_tx_pwr = int(eeprom_data[off], 16)
				lsb_tx_pwr = int(eeprom_data[off + 1], 16)
				tx_pwr_slope = (msb_tx_pwr << 8) | (lsb_tx_pwr & 0xff)

				off = self.dom_ext_calibration_constants['TX_PWR_Offset']['offset']
				msb_tx_pwr = int(eeprom_data[off], 16)
				lsb_tx_pwr = int(eeprom_data[off + 1], 16)
				tx_pwr_offset = (msb_tx_pwr << 8) | (lsb_tx_pwr & 0xff)
				tx_pwr_offset = self.twos_comp(tx_pwr_offset, 16)

				result = tx_pwr_slope * result + tx_pwr_offset
				result = float(result * 0.0001)
				retval = self.power_in_dbm_str(result)
			else:
				retval = 'Unknown'
		except Exception, err:
				retval = str(err)

		return retval


	def calc_rx_power(self, eeprom_data, offset, size):
		try:
			cal_type = self.get_calibration_type()

			msb = int(eeprom_data[offset], 16)
			lsb = int(eeprom_data[offset + 1], 16)
			result = (msb << 8) | (lsb & 0xff)

			if cal_type == 1:

				# Internal Calibration
				result = float(result * 0.0001)
				#print indent, name, " : ", power_in_dbm_str(result)
				retval = self.power_in_dbm_str(result)

			elif cal_type == 2:

				# External Calibration

				# RX_PWR(uW) = RX_PWR_4 * RX_PWR_AD +
				#	       RX_PWR_3 * RX_PWR_AD +
				#	       RX_PWR_2 * RX_PWR_AD +
				#	       RX_PWR_1 * RX_PWR_AD +
				#	       RX_PWR(0)
				off = self.dom_ext_calibration_constants['RX_PWR_4']['offset']
				rx_pwr_byte3 = int(eeprom_data[off], 16)
				rx_pwr_byte2 = int(eeprom_data[off + 1], 16)
				rx_pwr_byte1 = int(eeprom_data[off + 2], 16)
				rx_pwr_byte0 = int(eeprom_data[off + 3], 16)
				rx_pwr_4 = (rx_pwr_byte3 << 24) | (rx_pwr_byte2 << 16) | (rx_pwr_byte1 << 8) | (rx_pwr_byte0 & 0xff)

				off = self.dom_ext_calibration_constants['RX_PWR_3']['offset']
				rx_pwr_byte3 = int(eeprom_data[off], 16)
				rx_pwr_byte2 = int(eeprom_data[off + 1], 16)
				rx_pwr_byte1 = int(eeprom_data[off + 2], 16)
				rx_pwr_byte0 = int(eeprom_data[off + 3], 16)
				rx_pwr_3 = (rx_pwr_byte3 << 24) | (rx_pwr_byte2 << 16) | (rx_pwr_byte1 << 8) | (rx_pwr_byte0 & 0xff)

				off = self.dom_ext_calibration_constants['RX_PWR_2']['offset']
				rx_pwr_byte3 = int(eeprom_data[off], 16)
				rx_pwr_byte2 = int(eeprom_data[off + 1], 16)
				rx_pwr_byte1 = int(eeprom_data[off + 2], 16)
				rx_pwr_byte0 = int(eeprom_data[off + 3], 16)
				rx_pwr_2 = (rx_pwr_byte3 << 24) | (rx_pwr_byte2 << 16) | (rx_pwr_byte1 << 8) | (rx_pwr_byte0 & 0xff)

				off = self.dom_ext_calibration_constants['RX_PWR_1']['offset']
				rx_pwr_byte3 = int(eeprom_data[off], 16)
				rx_pwr_byte2 = int(eeprom_data[off + 1], 16)
				rx_pwr_byte1 = int(eeprom_data[off + 2], 16)
				rx_pwr_byte0 = int(eeprom_data[off + 3], 16)
				rx_pwr_1 = (rx_pwr_byte3 << 24) | (rx_pwr_byte2 << 16) | (rx_pwr_byte1 << 8) | (rx_pwr_byte0 & 0xff)

				off = self.dom_ext_calibration_constants['RX_PWR_0']['offset']
				rx_pwr_byte3 = int(eeprom_data[off], 16)
				rx_pwr_byte2 = int(eeprom_data[off + 1], 16)
				rx_pwr_byte1 = int(eeprom_data[off + 2], 16)
				rx_pwr_byte0 = int(eeprom_data[off + 3], 16)
				rx_pwr_0 = (rx_pwr_byte3 << 24) | (rx_pwr_byte2 << 16) | (rx_pwr_byte1 << 8) | (rx_pwr_byte0 & 0xff)

				rx_pwr = (rx_pwr_4 * result) + (rx_pwr_3 * result) + (rx_pwr_2 * result) + (rx_pwr_1 * result) + rx_pwr_0

				result = float(result * 0.0001)
				#print indent, name, " : ", power_in_dbm_str(result)
				retval = self.power_in_dbm_str(result)
			else:
				retval = 'Unknown'
		except Exception, err:
			retval = str(err)

		return retval


	dom_aw_thresholds = {	'TempHighAlarm':
					{'offset':0,
				 	 'size':2,
				 	 'type': 'func',
				 	 'decode': { 'func':calc_temperature}},
				 'TempLowAlarm':
					{'offset':2,
					 'size':2,
				 	'type': 'func',
				 	'decode': { 'func':calc_temperature}},
		 		'TempHighWarning':
					{'offset':4,
				 	'size':2,
				 	'type': 'func',
				 	'decode': { 'func':calc_temperature}},
		 		'TempLowWarning':
					{'offset':6,
				 	'size':2,
				 	'type': 'func',
				 	'decode': { 'func':calc_temperature}},
		 		'VoltageHighAlarm':
					{'offset':8,
				 	'size':2,
				 	'type': 'func',
				 	'decode': { 'func':calc_voltage}},
				'VoltageLowAlarm':
					{'offset':10,
				 	 'size':2,
				 	 'type': 'func',
				 	'decode': { 'func':calc_voltage}},
		 		'VoltageHighWarning':
					{'offset':12,
				 	 'size':2,
				 	 'type': 'func',
				 	 'decode': { 'func':calc_voltage}},
		 		'VoltageLowWarning':
					{'offset':14,
				 	 'size':2,
				 	 'type': 'func',
				 	 'decode': { 'func':calc_voltage}},
		 		'BiasHighAlarm':
					{'offset':16,
				 	 'size':2,
				 	 'type': 'func',
				 	 'decode': { 'func':calc_bias}},
		 		'BiasLowAlarm':
					{'offset':18,
				 	 'size':2,
					 'type': 'func',
					 'decode': { 'func':calc_bias}},
		 		'BiasHighWarning':
					{'offset':20,
					 'size':2,
					 'type': 'func',
					 'decode': { 'func':calc_bias}},
				'BiasLowWarning':
					{'offset':22,
				 	 'size':2,
				 	 'type': 'func',
				 	 'decode': { 'func':calc_bias}},
		 		'TXPowerHighAlarm':
					{'offset':24,
				 	 'size':2,
				 	 'type': 'func',
				 	 'decode': { 'func':calc_tx_power}},
		 		'TXPowerLowAlarm':
					{'offset':26,
				 	 'size':2,
					 'type': 'func',
				 	 'decode': { 'func':calc_tx_power}},
		 		'TXPowerHighWarning':
					{'offset':28,
				 	 'size':2,
				 	 'type': 'func',
				 	 'decode': { 'func':calc_tx_power}},
		 		'TXPowerLowWarning':
					{'offset':30,
				 	 'size':2,
				 	 'type': 'func',
				 	 'decode': { 'func':calc_tx_power}},
		 		'RXPowerHighAlarm':
					{'offset':32,
				 	 'size':2,
				 	 'type': 'func',
				 	 'decode': { 'func':calc_rx_power}},
		 		'RXPowerLowAlarm':
					{'offset':34,
				 	 'size':2,
				 	 'type': 'func',
				 	 'decode': { 'func':calc_rx_power}},
		 		'RXPowerHighWarning':
					{'offset':36,
				 	 'size':2,
				 	 'type': 'func',
				 	 'decode': { 'func':calc_rx_power}},
		 		'RXPowerLowWarning':
					{'offset':38,
				 	 'size':2,
				 	 'type': 'func',
				 	 'decode': { 'func':calc_rx_power}}}

	dom_monitor = {'Temperature':
				{'offset':96,
				 'size':2,
				 'type': 'func',
				 'decode': { 'func':calc_temperature}},
			     'Vcc':
				{'offset':98,
				 'size':2,
				 'type': 'func',
				 'decode': { 'func':calc_voltage}},
			     'TXBias':
				{'offset':100,
				 'size':2,
				 'type': 'func',
				 'decode': { 'func':calc_bias}},
			     'TXPower':
				{'offset':102,
				 'size':2,
				 'type': 'func',
				 'decode': { 'func':calc_tx_power}},
			     'RXPower':
				{'offset':104,
				 'size':2,
				 'type': 'func',
				 'decode': { 'func':calc_rx_power}}}

	dom_status_control = {	'TXDisableState':
					{'offset': 110,
					 'bit': 7,
					 'type': 'bitvalue'},
				'SoftTXDisableSelect':
					{'offset': 110,
					 'bit': 6,
					 'type': 'bitvalue'},
		  	  	'RS1State':
					{'offset': 110,
					 'bit': 5,
					 'type': 'bitvalue'},
				'RateSelectState':
					{'offset': 110,
					 'bit': 4,
					 'type': 'bitvalue'},
				'SoftRateSelect':
					{'offset': 110,
					 'bit': 3,
					 'type': 'bitvalue'},
				'TXFaultState':
					{'offset': 110,
					 'bit': 2,
					 'type': 'bitvalue'},
				'RXLOSState':
					{'offset': 110,
					 'bit': 1,
					 'type': 'bitvalue'},
				'DataReadyBarState':
					{'offset': 110,
					 'bit': 0,
					'type': 'bitvalue'}}

	dom_alarm_flags = {'TempHighAlarm':
			 	{'offset':112,
				 'bit':7,
				'type': 'bitvalue'},
			   'TempLowAlarm':
			 	{'offset':112,
				 'bit':6,
				'type': 'bitvalue'},
			   'VccHighAlarm':
			 	{'offset':112,
				 'bit':5,
				'type': 'bitvalue'},
			   'VccLowAlarm':
			 	{'offset':112,
				 'bit':4,
				'type': 'bitvalue'},
			   'TXBiasHighAlarm':
			 	{'offset':112,
				 'bit':3,
				'type': 'bitvalue'},
			   'TXBiasLowAlarm':
			 	{'offset':112,
				 'bit':2,
				 'type': 'bitvalue'},
			   'TXPowerHighAlarm':
			 	{'offset':112,
				 'bit':1,
				'type': 'bitvalue'},
			   'TXPowerLowAlarm':
			 	{'offset':112,
				 'bit':0,
				'type': 'bitvalue'},
			   'RXPowerHighAlarm':
			 	{'offset':113,
				 'bit':7,
				'type': 'bitvalue'},
			   'RXPowerLowAlarm':
			 	{'offset':113,
				 'bit':6,
				'type': 'bitvalue'}}

	dom_warning_flags = {	'TempHighWarning':
			 		{'offset':116,
				 	 'bit':7,
				 	 'type': 'bitvalue'},
				'TempLowWarning':
			 		{'offset':116,
				 	 'bit':6,
					 'type': 'bitvalue'},
		       		'VccHighWarning':
			 		{'offset':116,
				 	 'bit':5,
					 'type': 'bitvalue'},
		       		'VccLowWarning':
			 		{'offset':116,
				 	 'bit':4,
					 'type': 'bitvalue'},
		       		'TXBiasHighWarning':
			 		{'offset':116,
				 	 'bit':3,
					 'type': 'bitvalue'},
		       		'TXBiasLowWarning':
			 		{'offset':116,
					 'bit':2,
					'type': 'bitvalue'},
				'TXPowerHighWarning':
			 		{'offset':116,
				 	'bit':1,
					'type': 'bitvalue'},
				'TXPowerLowWarning':
			 		{'offset':116,
				 	'bit':0,
					'type': 'bitvalue'},
				'RXPowerHighWarning':
			 		{'offset':117,
				 	 'bit':7,
					'type': 'bitvalue'},
				'RXPowerLowWarning':
			 		{'offset':117,
				 	'bit':6,
					'type': 'bitvalue'}}

	dom_map = {'AwThresholds':
			{'offset' : 0,
			 'size' : 40,
			 'type' : 'nested',
			 'decode' : dom_aw_thresholds},
	       	'MonitorData':
			{'offset':96,
			 'size':10,
			 'type' : 'nested',
			 'decode': dom_monitor},
	       'StatusControl':
			{'offset':110,
			 'size':1,
			 'type' : 'nested',
			 'decode':dom_status_control},
	       'AlarmFlagStatus':
			{'offset':112,
			 'size':2,
			 'type' : 'nested',
			 'decode':dom_alarm_flags},
	       'WarningFlagStatus':
			{'offset':112,
			 'size':2,
			 'type' : 'nested',
			 'decode':dom_warning_flags}}


	def __init__(self, eeprom_raw_data=None, calibration_type=0):
		self._calibration_type = calibration_type
		start_pos = 0

		if eeprom_raw_data != None:
			self.dom_data = sff8472.parse(self, self.dom_map,
						      eeprom_raw_data, start_pos)

	def parse(self, eeprom_raw_data, start_pos):
		return sff8472.parse(self, self.dom_map, eeprom_raw_data, start_pos)


	def dump_pretty(self):
		if self.dom_data == None:
			print 'Object not initialized, nothing to print'
			return
		sff8472.dump_pretty(self, self.dom_data)


	def get_data(self):
		return self.dom_data


	def get_data_pretty(self):
		return sff8472.get_data_pretty(self, self.dom_data)



class sff8436QsfpInterfaceId(sff8472):

	version = '1.0'

	def __init__(self, eeprom_raw_data=None):
		self.interface_data = None
		start_pos = 128

		if eeprom_raw_data != None:
			self.interface_data = sff8472.parse(self,
							sff8472.interface_id,
							eeprom_raw_data,
							start_pos)

	def parse(self, eeprom_raw_data, start_pos):
		return sff8472.parse(self, self.interface_id, eeprom_raw_data, start_pos)

	def dump_pretty(self):
		if self.interface_data == None:
			print 'Object not initialized, nothing to print'
			return
		sff8472.dump_pretty(self, self.interface_data)

	def get_calibration_type(self):
		return self.calibration_type

	def get_data(self):
		return self.interface_data

	def get_data_pretty(self):
		return sff8472.get_data_pretty(self, self.interface_data)


class sff8436QsfpDom(sff8472):

	version = '1.0'

	dom_status_indicator = {'DataNotReady':
				{'offset': 2,
				 'bit': 0,
				 'type': 'bitvalue'}}

	dom_channel_status = {'Tx4LOS':
				{'offset': 3,
				 'bit': 7,
				 'type': 'bitvalue'},
			      'Tx3LOS':
				{'offset': 3,
				 'bit': 6,
				 'type': 'bitvalue'},
			      'Tx2LOS':
				{'offset': 3,
				 'bit': 5,
				 'type': 'bitvalue'},
			      'Tx1LOS':
				{'offset': 3,
				 'bit': 4,
				 'type': 'bitvalue'},
			      'Rx4LOS':
				{'offset': 3,
				 'bit': 3,
				 'type': 'bitvalue'},
			      'Rx3LOS':
				{'offset': 3,
				 'bit': 2,
				 'type': 'bitvalue'},
			      'Rx2LOS':
				{'offset': 3,
				 'bit': 1,
				 'type': 'bitvalue'},
			      'Rx1LOS':
				{'offset': 3,
				 'bit': 0,
				 'type': 'bitvalue'},
			      'Tx4Fault':
				{'offset': 4,
				 'bit': 3,
				 'type': 'bitvalue'},
			      'Tx3Fault':
				{'offset': 4,
				 'bit': 2,
				 'type': 'bitvalue'},
			      'Tx2Fault':
				{'offset': 4,
				 'bit': 1,
				 'type': 'bitvalue'},
			      'Tx1Fault':
				{'offset': 4,
				 'bit': 0,
				 'type': 'bitvalue'}}

	dom_module_monitor = {'TempHighAlarm':
				{'offset': 6,
				 'bit': 7,
				 'type': 'bitvalue'},
			       'TempLowAlarm':
				{'offset': 6,
				 'bit': 6,
				 'type': 'bitvalue'},
			       'TempHighWarning':
				{'offset': 6,
				 'bit': 5,
				 'type': 'bitvalue'},
			       'TempLowWarning':
				{'offset': 6,
				 'bit': 4,
				 'type': 'bitvalue'},
			       'VccHighAlarm':
				{'offset': 7,
				 'bit': 7,
				 'type': 'bitvalue'},
			       'VccLowAlarm':
				{'offset': 7,
				 'bit': 6,
				 'type': 'bitvalue'},
			       'VccHighWarning':
				{'offset': 7,
				 'bit': 5,
				 'type': 'bitvalue'},
			       'VccLowWarning':
				{'offset': 7,
				 'bit': 4,
				 'type': 'bitvalue'}}

	dom_channel_monitor = {'Rx1PowerHighAlarm':
				{'offset': 9,
				 'bit': 7,
				 'type': 'bitvalue'},
			       'Rx1PowerLowAlarm':
				{'offset': 9,
				 'bit': 6,
				 'type': 'bitvalue'},
			       'Rx1PowerHighWarning':
				{'offset': 9,
				 'bit': 5,
				 'type': 'bitvalue'},
			       'Rx1PowerLowWarning':
				{'offset': 9,
				 'bit': 4,
				 'type': 'bitvalue'},
			       'Rx2PowerHighAlarm':
				{'offset': 9,
				 'bit': 3,
				 'type': 'bitvalue'},
			       'Rx2PowerLowAlarm':
				{'offset': 9,
				 'bit': 2,
				 'type': 'bitvalue'},
			       'Rx2PowerHighWarning':
				{'offset': 9,
				 'bit': 1,
				 'type': 'bitvalue'},
			       'Rx2PowerLowWarning':
				{'offset': 9,
				 'bit': 0,
				 'type': 'bitvalue'},
			       'Rx3PowerHighAlarm':
				{'offset': 10,
				 'bit': 7,
				 'type': 'bitvalue'},
			       'Rx3PowerLowAlarm':
				{'offset': 10,
				 'bit': 6,
				 'type': 'bitvalue'},
			       'Rx3PowerHighWarning':
				{'offset': 10,
				 'bit': 5,
				 'type': 'bitvalue'},
			       'Rx3PowerLowWarning':
				{'offset': 10,
				 'bit': 4,
				 'type': 'bitvalue'},
			       'Rx4PowerHighAlarm':
				{'offset': 10,
				 'bit': 3,
				 'type': 'bitvalue'},
			       'Rx4PowerLowAlarm':
				{'offset': 10,
				 'bit': 2,
				 'type': 'bitvalue'},
			       'Rx4PowerHighWarning':
				{'offset': 10,
				 'bit': 1,
				 'type': 'bitvalue'},
			       'Rx4PowerLowWarning':
				{'offset': 10,
				 'bit': 0,
				 'type': 'bitvalue'},
			       'Tx1BiasHighAlarm':
				{'offset': 11,
				 'bit': 7,
				 'type': 'bitvalue'},
			       'Tx1BiasLowAlarm':
				{'offset': 11,
				 'bit': 6,
				 'type': 'bitvalue'},
			       'Tx1BiasHighWarning':
				{'offset': 11,
				 'bit': 5,
				 'type': 'bitvalue'},
			       'Tx1BiasLowWarning':
				{'offset': 11,
				 'bit': 4,
				 'type': 'bitvalue'},
			       'Tx2BiasHighAlarm':
				{'offset': 11,
				 'bit': 3,
				 'type': 'bitvalue'},
			       'Tx2BiasLowAlarm':
				{'offset': 11,
				 'bit': 2,
				 'type': 'bitvalue'},
			       'Tx2BiasHighWarning':
				{'offset': 11,
				 'bit': 1,
				 'type': 'bitvalue'},
			       'Tx2BiasLowWarning':
				{'offset': 11,
				 'bit': 0,
				 'type': 'bitvalue'},
			       'Tx3BiasHighAlarm':
				{'offset': 12,
				 'bit': 7,
				 'type': 'bitvalue'},
			       'Tx3BiasLowAlarm':
				{'offset': 12,
				 'bit': 6,
				 'type': 'bitvalue'},
			       'Tx3BiasHighWarning':
				{'offset': 12,
				 'bit': 5,
				 'type': 'bitvalue'},
			       'Tx3BiasLowWarning':
				{'offset': 12,
				 'bit': 4,
				 'type': 'bitvalue'},
			       'Tx4BiasHighAlarm':
				{'offset': 12,
				 'bit': 3,
				 'type': 'bitvalue'},
			       'Tx4BiasLowAlarm':
				{'offset': 12,
				 'bit': 2,
				 'type': 'bitvalue'},
			       'Tx4BiasHighWarning':
				{'offset': 12,
				 'bit': 1,
				 'type': 'bitvalue'},
			       'Tx4BiasLowWarning':
				{'offset': 12,
				 'bit': 0,
				 'type': 'bitvalue'}}


	dom_map = {'StatusIndicators':
			{'offset' : 1,
			 'size' : 2,
			 'type' : 'nested',
			 'decode' : dom_status_indicator},
		   'ChannelStatus':
			{'offset': 3,
			 'size':2,
			 'type':'nested',
			 'decode': dom_channel_status},
		   'ModuleMonitor':
			{'offset': 6,
			 'size':2,
			 'type':'nested',
			 'decode': dom_module_monitor},
		   'ChannelMonitor':
			{'offset': 9,
			 'size':4,
			 'type':'nested',
			 'decode': dom_channel_monitor}}


	def __init__(self, eeprom_raw_data=None, calibration_type=0):
		self._calibration_type = calibration_type
		start_pos = 0

		if eeprom_raw_data != None:
			self.dom_data = sff8472.parse(self, self.dom_map,
					      eeprom_raw_data, start_pos)

	def parse(self, eeprom_raw_data, start_pos):
		return sff8472.parse(self, self.dom_map, eeprom_raw_data,
					start_pos)


	def dump_pretty(self):
		if self.dom_data == None:
			print 'Object not initialized, nothing to print'
			return
		sff8472.dump_pretty(self, self.dom_data)


	def get_data(self):
		return self.dom_data

	def get_data_pretty(self):
		return sff8472.get_data_pretty(self, self.dom_data)
