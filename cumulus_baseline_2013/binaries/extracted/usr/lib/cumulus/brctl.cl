#! /usr/bin/python

# Copyright 2012 Cumulus Networks LLC, all rights reserved

#############################################################################
#
# This script is a cumulus wrapper script for a bridge-utils
# command brctl
#
#
############################################################################


try:
	import fcntl
	import struct
	import sys
	import os
	import subprocess
	import string

except ImportError, e:
	raise ImportError (str(e) + "- required module not found")

try:
	if os.path.exists("/sbin/brctl.bridge-utils") == True:
		brctl_cmd = 'brctl.bridge-utils'
	else:
		brctl_cmd = 'brctl'
except OSError, e:
	print 'Error: ' + str(e)
	sys.exit(1)

brctl_cmd_path = '/sbin/' + brctl_cmd

#
# Get Bridge port no and name map
# from sysfs
#
def create_bridge_port_no_name_map(bridge_name):
	bridge_port_map = {}
	sysfs_path = "/sys/class/net"
	sysfs_bridge_path = sysfs_path + '/' + bridge_name
	sysfs_bridge_port_path = sysfs_bridge_path + '/' + "brif"

	try:	
		dirList = os.listdir(sysfs_bridge_port_path)
	except:
		return None

	# Scan through sysfs bridge port directory
	# Example: /sys/class/net/br0/brif
	# Looking for port num
	for port_name in dirList:
		sysfs_bridge_port_no_file = sysfs_bridge_port_path + '/' + port_name + '/port_no'
		try:
			f = open (sysfs_bridge_port_no_file)
			port_num_str = f.readline()
		except IOError:
			return None 

		port_num = int(port_num_str.strip(), 16)
		bridge_port_map[port_num] = port_name
		f.close()

	return bridge_port_map


#
# Rewrite brctl showmacs output
# replacing port number with port name
#
def brctl_rewrite_showmacs(brctl_cmdline, brctl_cmdout):
	brctl_lines = brctl_cmdout.split("\n")
	bridge_name = brctl_cmdline[2]
	new_brctl_output = ''

	bridge_port_map = create_bridge_port_no_name_map(bridge_name)
	if bridge_port_map is None:
		return None	

	(first, sep, rem) = brctl_lines[0].strip().partition('\t')
	new_brctl_output += 'port name' + ' ' + rem + '\n'

	for i in range(1, len(brctl_lines)):

		brctl_lines[i].strip()

		# Skip blank lines
		if brctl_lines[i] == '':
			continue

		(first, sep, rem) = brctl_lines[i].strip().partition('\t')

		port_name = bridge_port_map.get(int(first.strip()))
		if port_name is None:
			return None

		new_brctl_line = "%-9s %s" % (port_name, rem)
		new_brctl_output += new_brctl_line + '\n'

	return str(new_brctl_output)


#
# brctl output filter function
# Currently Only filters brctl showmacs command output 
#
def brctl_output_filter(brctl_cmdline, brctl_cmdout, brctl_retval):
	if brctl_retval == 0 and len(brctl_cmdline) > 1 and brctl_cmdline[1] == 'showmacs':
		return brctl_rewrite_showmacs(brctl_cmdline, brctl_cmdout)
	else:
		if 'Usage: brctl [commands]' in brctl_cmdout:
			msg, command, cmdlist = brctl_cmdout.partition('commands:')
			usage_lines = cmdlist.splitlines()
			usage_lines.sort()
			brctl_cmdout = msg + command + '\n'.join(T for T in usage_lines)
		return brctl_cmdout


#
# loop through all the bridges and display the stp info for each
#
def show_stp(all_bridges):

        for i in range(0, len(all_bridges)):

                showstp_line = []
                showstp_line.append(brctl_cmd_path)
                showstp_line.append('showstp')

                all_bridges[i].strip()
                showstp_line.append(all_bridges[i])

                try:
                        p = subprocess.Popen((showstp_line), stdout=subprocess.PIPE, shell=False, stderr=subprocess.STDOUT)
                        cmdout = p.communicate()[0]
                        p.wait()
                        retval = p.returncode

                except EnvironmentError as e:
                        print e,e.errno
                        sys.exit(e.errno)

                if cmdout is None:
                        print ''
                else:
                        print cmdout

        return



#
# Get all the bridges from 'brctl show'
#
def get_all_brdges(br_cmdout):
        bridges = []
        brctl_lines = br_cmdout.split("\n")
        for i in range (1, len(brctl_lines)):

                brctl_lines[i].strip()

                (bridge_name, sep, rem) = brctl_lines[i].strip().partition('\t')

                if rem == '':
                        continue

                bridges.append(bridge_name)

        return bridges


#
# execute cbrctl showstpall command
#
def execute_showstpall():
	cmd_line = []
	cmd_line.append(brctl_cmd_path)
	cmd_line.append('show')

	try:
        	p = subprocess.Popen(cmd_line, stdout=subprocess.PIPE,
                                     shell=False, stderr=subprocess.STDOUT)
        	cmdout = p.communicate()[0]
	        p.wait()
	        retval = p.returncode

	except EnvironmentError as e:
	        print e,e.errno
	        sys.exit(e.errno)

	all_brdges = get_all_brdges(cmdout)
	show_stp(all_brdges)
	return


#
# check bridge membership
#
def is_bridge_member(bridge, port):
	brif_path = '/sys/class/net/' + bridge + '/brif/' + port
	return os.path.exists(brif_path)
	

def get_bond_list():
	bond_masters = '/sys/class/net/bonding_masters'
	if os.path.exists(bond_masters):
		f = open (bond_masters)
                all_bonds = f.readline()
		f.close()

	bond_keys = all_bonds.strip().split(' ')
	return bond_keys
		
def get_bond_slaves(bond):
	bond_slaves = []
        try:
		ps = subprocess.Popen(('cat', '/proc/net/bonding/' + bond), stdout=subprocess.PIPE)
		cmdout = subprocess.check_output(('grep', 'Slave Interface'), stdin=ps.stdout)
		ps.wait()
        except subprocess.CalledProcessError, e:
		return bond_slaves

	lines = cmdout.strip().split('\n')
	for l in lines:
		swp = l.strip().split(' ')[-1]
		bond_slaves.append(swp)

	return bond_slaves
			

#
# Check and reject command if multiple sub-interfaces of the same swp port
# are being added to the same bridge.  Reject by returning False, otherwise,
# return True to fall through to letting brctl handle the command.
#
def validate_addif(cmdline):
	if len(cmdline) < 4:
		return True

	bridge = cmdline[2]
	bridge_path = '/sys/class/net/' + bridge

	if os.path.exists(bridge_path) and os.path.exists(bridge_path + '/bridge') :
		syspath = bridge_path + '/brif'
	else:
		return True

	bonds = get_bond_list()

	port_list = {}
	for fn in os.listdir(syspath):
		swp = fn.split('.')[0]
		port_list[swp] = fn
		if swp in bonds:
			slaves = get_bond_slaves(swp)
			for slave in slaves:
				port_list[slave] = fn

	brifs = cmdline[3:]
	for brif in brifs:
                swps = []
		swps.append(brif.split('.')[0])
		if swps[0] in bonds:
			swps = swps + get_bond_slaves(swps[0])

		for swp in swps:
			if swp not in port_list.keys():
				port_list[swp] = brif
			else:
				if brif != port_list[swp]:
					if port_list[swp] in bonds:
						print 'bridge cannot contain multiple sub-interfaces of the same port: ' + port_list[swp] + ' member ' + swp + ', ' + brif
					else:
						print 'bridge cannot contain multiple sub-interfaces of the same port: ' + port_list[swp] + ', ' + brif
					return False
				
	return True


# Build brctl command line to execute
cmd_line = []
cmd_line.append(brctl_cmd_path)
for i in range(1, len(sys.argv)):
	cmd_line.append(sys.argv[i])

# Check for extension commands and execute them first
if len(cmd_line) > 1:
	if cmd_line[1] == 'addif':
		# Do vlan sub-interface check if the command is 'addif'
		if not validate_addif(cmd_line):
			sys.exit(0)
	if cmd_line[1] == 'stpshowall':
                execute_showstpall()
                sys.exit(0)
 

# Execute command
try:
	p = subprocess.Popen((cmd_line), stdout=subprocess.PIPE,
			shell=False, stderr=subprocess.STDOUT)
	cmdout = p.communicate()[0]
	p.wait()
	retval = p.returncode

except EnvironmentError as e:
	print e,e.errno
	sys.exit(e.errno)


# Filter brctl cmd output
new_cmdout = brctl_output_filter(cmd_line, cmdout, retval)
if new_cmdout is None:
	if cmdout != '':
		print cmdout,
else:
	if new_cmdout != '':
		print new_cmdout,

sys.exit(0)

