#!/usr/bin/python
#
# Copyright 2013.  Cumulus Networks, Inc.
# Author: Roopa Prabhu, roopa@cumulusnetworks.com
#
# linuxpktfilter.py --
#     module with wrapper functions to linux packet filter tools namely:
#     iptables, ip6tables and ebtables
#

try:
	import argparse
	import subprocess
	import os

except ImportError, e:
	raise ImportError (str(e) + "- required module not found")


class pktFilterBase():
	"""Base rule parser for linux acl
	rules.
	XXX: Currently only supports parsing of args we are interested in """

	kernel_tables = ['filter', 'mangle', 'raw']

	def __init__(self):


		#
		# Initialize root parser
		# Root parser: returns [table, 'rest of the args']"
		#
		self.root_parser = argparse.ArgumentParser(add_help=False)
		self.root_parser.add_argument('-t', dest='table',
						default='filter')

		#
		# Initialize commands parser
		# Command parser:  returns ['command', 'rest of the args']
		#
		self.command_parser = self.root_parser.add_mutually_exclusive_group()
		self.command_parser.add_argument('-A', nargs=argparse.REMAINDER)
		self.command_parser.add_argument('-I', nargs=argparse.REMAINDER)
		self.command_parser.add_argument('-P', nargs=argparse.REMAINDER)

		#
		# Initialize append command parser
		# append command parser:  returns ['chain', 'rule_spec']
		#
		self.append_comm_parser = argparse.ArgumentParser(add_help=False)
		self.append_comm_parser.add_argument('chain')
		self.append_comm_parser.add_argument('rule_spec',
						nargs=argparse.REMAINDER)

		#
		# Initialize Insert command parser
		# Insert command parser:  returns ['chain', 'rule_num',
		#		'rule_spec']
		#
		self.insert_comm_parser = argparse.ArgumentParser(
								add_help=False)
		self.insert_comm_parser.add_argument('chain')
		self.insert_comm_parser.add_argument('rule_num', type=int,
							default=1)
		self.insert_comm_parser.add_argument('rule_spec',
						nargs=argparse.REMAINDER)

		#
		# Initialize policy command parser
		# policy command parser:  returns ['chain', target]
		#		'rule_spec']
		#
		self.policy_comm_parser = argparse.ArgumentParser(
								add_help=False)
		self.policy_comm_parser.add_argument('chain')
		self.policy_comm_parser.add_argument('target')


		#
		# Initialize rule parser
		#
		self.rule_spec_parser = argparse.ArgumentParser(add_help=False)
		self.rule_spec_parser.add_argument('-i')
		self.rule_spec_parser.add_argument('--in-interface')
		self.rule_spec_parser.add_argument('-o')
		self.rule_spec_parser.add_argument('--out-interface')


	def parse(self, arg_list):
		""" Returns a dict of parsed rule elements :
		Example:
		rule '-A INPUT --in-interface swp1,swp5 -p tcp --dport 80
		     -j ACCEPT'

		is parsed into the below dict:
		(Note: 'args_rem' always carries the unknown args at
		 every level)
		{   'A': {   'args_rem': [],
			     'chain': 'INPUT',
			     'rule_spec': {   'args_rem': [   '-p',
				     			      'tcp',
							      '--dport',
							      '80',
							      '-j',
							      'ACCEPT'],
					       'i': None,
					       'in_interface': 'swp1,swp5',
					       'o': None,
					       'out_interface': None}},
		     'args_rem': [],
		     'command': 'A',
		     'table': 'filter'}
		"""

		return_dict = {}
		command_args = None
		args_rem = None

		# Parse root args
		(parsed_out, args_rem) = self.root_parser.parse_known_args(
								arg_list)
		return_dict = vars(parsed_out)
		return_dict['args_rem'] = args_rem

		if return_dict.get('A') != None:
			p = self.append_comm_parser
			(command_args, command_args_rem) = p.parse_known_args(
							return_dict.get('A'))
			command = 'A'
		elif return_dict.get('I') != None:
			p = self.insert_comm_parser
			(command_args, command_args_rem) = p.parse_known_args(
							return_dict.get('I'))
			command = 'I'
		elif return_dict.get('P') != None:
			p = self.policy_comm_parser
			(command_args, command_args_rem) = p.parse_known_args(
							return_dict.get('P'))
			command = 'P'


		if not command_args:
			return None

		command_dict = vars(command_args)
		command_dict['args_rem'] = command_args_rem 

		#
		# Parse rule spec
		#
		rule_spec = command_dict.get('rule_spec')
		if rule_spec != None:
			p = self.rule_spec_parser
			(rule_args, rule_spec_args_rem) = p.parse_known_args(
								rule_spec)
			rule_spec_dict = vars(rule_args)
			rule_spec_dict['args_rem'] = rule_spec_args_rem
			command_dict['rule_spec'] = rule_spec_dict

		return_dict['command'] = command
		return_dict[command] = command_dict

	
		#print 'Return dict ..'
		#print return_dict

		return return_dict


	@classmethod
	def exec_command(cls, cmd, verbose):
		retval = 0

		try:
			if verbose == True:
				print('Executing ' + cmd)
			ch = subprocess.Popen(cmd.split(),
					stdout=subprocess.PIPE,
					shell=False, stderr=subprocess.STDOUT)
			cmd_out = ch.communicate()[0]
			retval = ch.wait()
		except OSError, e:
			cmd_out = ('error: executing ' + cmd +
					'(' + str(e) + ')')
			retval = -1

		return (retval, cmd_out)


class iptables(pktFilterBase):
	""" iptables rule parser """

	def __init__(self):
		pktFilterBase.__init__(self)

	@classmethod
	def zero_counters(cls, table, extra_options, verbose):
		""" Returns a tuple of (retval, cmdreturncode, cmdout) """
		options = ' -t %s ' %table + ' -Z ' + extra_options
		cmd = '/sbin/iptables ' + options

		retval, cmd_out = cls.exec_command(cmd, verbose)
		return (cmd, retval, cmd_out)

	@classmethod
	def flush(cls, table, extra_options, verbose):
		""" Returns a tuple of (retval, cmdreturncode, cmdout) """
		options = ' -t %s ' %table + ' -F ' + extra_options
		cmd = '/sbin/iptables ' + options

		retval, cmd_out = cls.exec_command(cmd, verbose)
		return (cmd, retval, cmd_out)

	@classmethod
	def save(cls, table, filename, extra_options, verbose):
		retval = 0
		options = ' -t %s ' %table + ' ' + extra_options + ' >' + filename
		cmd = '/sbin/iptables-save ' + options

		try:
			if verbose == True:
				print('Executing: ' + cmd)
			os.system(cmd)
		except OSError, e:
			print('error executing command : ' + cmd)
			retval = -1

		return (cmd, retval, '')

	@classmethod
	def restore(cls, table, filename, noflush,
			extra_options, verbose):
		retval = 0
		options = ' -T %s ' %table + extra_options

		if noflush == 1:
			options = options + ' --noflush '

		cmd = '/sbin/iptables-restore ' + options
		try:
			restore_fd = open(filename)
		except IOError, e:
			print('error opening restore file %s '
					%filename)
			return ('open %s' %filename, -1, '')

		try:
			if verbose == True:
				print('Executing: ' + cmd + ' <' + filename)

			ch = subprocess.Popen(cmd.split(),
					stdout=subprocess.PIPE,
					stdin=restore_fd,
					shell=False, stderr=subprocess.STDOUT)
			cmd_out = ch.communicate()[0]
			retval = ch.wait()
		except OSError, e:
			cmd_out = ('error: executing ' + cmd +
					'(' + str(e) + ')')
			retval = -1

		return (cmd, retval, cmd_out)

	@classmethod
	def list(cls, table, extra_options, verbose):
		options = ' -t %s ' %table + ' -L ' + extra_options
		cmd = '/sbin/iptables ' + options

		retval, cmd_out = cls.exec_command(cmd, verbose)
		if retval == 0:
			print cmd_out
		return (cmd, retval, cmd_out)

class ip6tables(pktFilterBase):
	""" ip6tables rule parser """

	def __init__(self):
		pktFilterBase.__init__(self)

	@classmethod
	def zero_counters(cls, table, extra_options, verbose):
		options = ' -t %s ' %table + ' -Z ' + extra_options
		cmd = '/sbin/ip6tables ' + options

		retval, cmd_out = cls.exec_command(cmd, verbose)
		return (cmd, retval, cmd_out)

	@classmethod
	def flush(cls, table, extra_options, verbose):
		options = ' -t %s ' %table + ' -F ' + extra_options
		cmd = '/sbin/ip6tables ' + options

		retval, cmd_out = cls.exec_command(cmd, verbose)
		return (cmd, retval, cmd_out)

	@classmethod
	def save(cls, table, filename, extra_options, verbose):
		retval = 0
		options = ' -t %s ' %table + ' ' + extra_options + ' >' + filename
		cmd = '/sbin/ip6tables-save ' + options

		try:
			if verbose == True:
				print('Executing: ' + cmd)
			os.system(cmd)
		except OSError, e:
			print('error executing command : ' + cmd + ' : %s'
					%str(e))
			retval = -1

		return (cmd, retval, '')

	@classmethod
	def restore(cls, table, filename, noflush, extra_options, verbose):
		retval = 0
		options = ' -T %s ' %table + extra_options

		if noflush == 1:
			options += ' --noflush '

		cmd = '/sbin/ip6tables-restore ' + options
		try:
			restore_fd = open(filename)
		except IOError, e:
			print('error opening restore file %s '
					%filename)
			return ('open %s' %filename, -1, '')

		try:
			if verbose == True:
				print('Executing: ' + cmd + ' <' + filename)

			ch = subprocess.Popen(cmd.split(),
					stdout=subprocess.PIPE,
					stdin=restore_fd,
					shell=False, stderr=subprocess.STDOUT)
			cmd_out = ch.communicate()[0]
			retval = ch.wait()
		except OSError, e:
			cmd_out = ('error: executing ' + cmd +
					'(' + str(e) + ')')
			retval = -1

		return (cmd, retval, cmd_out)

	@classmethod
	def list(cls, table, extra_options, verbose):
		options = ' -t %s ' %table + ' -L ' + extra_options
		cmd = '/sbin/ip6tables ' + options

		retval, cmd_out = cls.exec_command(cmd, verbose)
		if retval == 0:
			print cmd_out
		return (cmd, retval, cmd_out)

class ebtables(pktFilterBase):
	""" ip6tables rule parser """

	kernel_tables = ['filter']

	def __init__(self):
		pktFilterBase.__init__(self)

	@classmethod
	def zero_counters(cls, table, extra_options, verbose):
		""" Returns a tuple of (retval, cmdreturncode, cmdout) """
		options = ' -t %s ' %table + ' -Z ' + extra_options
		cmd = '/sbin/ebtables ' + options

		retval, cmd_out = cls.exec_command(cmd, verbose)
		return (cmd, retval, cmd_out)

	@classmethod
	def flush(cls, table, extra_options, verbose):
		""" Returns a tuple of (retval, cmdreturncode, cmdout) """
		options = ' -t %s ' %table + ' -F ' + extra_options
		cmd = '/sbin/ebtables ' + options

		retval, cmd_out = cls.exec_command(cmd, verbose)
		return (cmd, retval, cmd_out)

	@classmethod
	def save(cls, table, filename, extra_options, verbose):
		""" Returns a tuple of (retval, cmdreturncode, cmdout) """
		options = ' -t %s' %table + ' --atomic-file ' + filename + ' --atomic-save'
		cmd = '/sbin/ebtables ' + options + ' ' + extra_options

		retval, cmd_out = cls.exec_command(cmd, verbose)
		return (cmd, retval, cmd_out)

	@classmethod
	def restore(cls, table, filename, extra_options, verbose):
		options = ' -t %s' %table + ' --atomic-file ' + filename + ' --atomic-commit-with-countersave'
		cmd = '/sbin/ebtables ' + options + ' ' + extra_options

		retval, cmd_out = cls.exec_command(cmd, verbose)
		return (cmd, retval, cmd_out)

	@classmethod
	def list(cls, table, extra_options, verbose):
		options = ' -t %s ' %table + '-L'
		cmd = '/sbin/ebtables ' + options + ' ' + extra_options

		retval, cmd_out = cls.exec_command(cmd, verbose)
		if retval == 0:
			print cmd_out
		return (cmd, retval, cmd_out)
