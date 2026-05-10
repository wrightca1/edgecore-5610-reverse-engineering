#!/usr/bin/python
#
# Copyright 2013.  Cumulus Networks, Inc.
# Author: Roopa Prabhu, roopa@cumulusnetworks.com
#
# aclpoilcy.py --
#     module to parse and process cumulus acl policy files
#
try:
	import re
	import string
	import pprint
	from cumulus.linuxpktfilter import *

except ImportError, e:
    raise ImportError (str(e) + "- required module not found")


class aclRuleType:
	""" acl rule types """
	iptables = 1

	ip6tables = 2

	arptables = 3

	ebtables = 4

	iptables_raw = 5

	@classmethod
	def to_str(cls, type):
		if type == cls.iptables:
			return 'iptables'
		elif type == cls.ip6tables:
			return 'ip6tables'
		elif type == cls.arptables:
			return 'arptables'
		elif type == cls.ebtables:
			return 'ebtables'
		else:
			return None

	@classmethod
	def from_str(cls, str_type):
		if str_type == 'iptables':
			return cls.iptables
		elif str_type == 'ip6tables':
			return cls.ip6tables
		elif str_type == 'ebtables':
			return cls.ebtables

		return -1

	@classmethod
	def to_str_short(cls, type):
		if type == cls.iptables:
			return 'ip'
		elif type == cls.ip6tables:
			return 'ip6'
		elif type == cls.arptables:
			return 'arp'
		elif type == cls.ebtables:
			return 'eb'
		else:
			return None

	@classmethod
	def from_str_short(cls, str_type):
		if str_type == 'ip':
			return cls.iptables
		elif str_type == 'ip6':
			return cls.ip6tables
		elif str_type == 'eb':
			return cls.ebtables

		return -1

class aclRule(object):
	""" acl rule """

	# Flags
	HAS_SIBLING = 0x1

	def __init__(self, rule_str, type):
		# Original rule
		self.rule_str = rule_str

		# To start with contains the orig str, but
		# is preprocessed with env variables
		self.preprocessed_rule_str = rule_str

		# rule type
		self.type = type

		# rule parsed into a dict, with option name as the key
		self.parsed_rule = {}

		# List of rules orig rule_str is expanded to
		self.processed_rule_str_list = []

		self.input_intf_option = None
		self.output_intf_option = None
		self.input_intf = None
		self.output_intf = None
		self.flags = 0

	def set_flags(self, flags):
		self.flags = flags

	def set_flag(self, flag):
		self.flags |= flag

	def get_flags(self):
		return self.flags


	def has_sibling(self):
		return (self.flags & self.HAS_SIBLING)

	def get_rule_str(self):
		return self.rule_str

	def get_type(self):
		return self.type

	def get_preprocessed_rule_str(self):
		return self.preprocessed_rule_str

	def set_parsed_rule(self, parsed_rule):
		self.parsed_rule = parsed_rule

	def set_processed_rule_str_list(self, rule_str_list):
		self.processed_rule_str_list = rule_str_list

	def set_lineno(self, lineno):
		self.lineno = lineno

	def get_lineno(self):
		return self.lineno

	def get_parsed_rule(self):
		return self.parsed_rule

	def get_processed_rule_str_list(self):
		return self.processed_rule_str_list

	def append_processed_rule_str_list(self, rule_str):
		self.processed_rule_str_list.append(rule_str)

	def substitute_var(self, key, value):
		self.preprocessed_rule_str = re.sub('\$' + key, value,
				self.preprocessed_rule_str)


	def get_chain(self):
		""" Get Chain from parsed rule """
		parsed_rule = self.get_parsed_rule()
		if parsed_rule == None:
			return None
		parsed_rule_command = parsed_rule.get('command')
		parsed_rule_command_args = parsed_rule.get(parsed_rule_command)
		return parsed_rule_command_args.get('chain')

	def get_table(self):
		""" Get table from parsed rule """
		parsed_rule = self.get_parsed_rule()
		if parsed_rule == None:
			return None

		return parsed_rule.get('table')

	def get_rule_spec(self):
		""" Get table from parsed rule """
		parsed_rule = self.get_parsed_rule()
		if parsed_rule == None:
			return None

		parsed_rule_command = parsed_rule.get('command')
		parsed_rule_command_args = parsed_rule.get(parsed_rule_command)

		return parsed_rule_command_args.get('rule_spec')

	def set_input_intf_option(self, input_option):
		""" store input interface option '-i' or '--in-interface' """
		self.input_intf_option = input_option

	def get_input_intf_option(self):
		return self.input_intf_option

	def set_output_intf_option(self, output_option):
		""" store output option '-o' or '--out-interface' """
		self.output_intf_option = output_option


	def get_output_intf_option(self):
		return self.output_intf_option

	def set_input_intf(self, intf_str):
		""" store input interface string """
		self.input_intf = intf_str

	def set_output_intf(self, intf_str):
		""" store output interface string """
		self.output_intf = intf_str

	def parse(self):
		""" iptables rule parser """
		type = self.get_type()
		if type == aclRuleType.iptables:
			parser = iptables()
		elif type == aclRuleType.ip6tables:
			parser = ip6tables()
		elif type == aclRuleType.ebtables:
			parser = ebtables()
		else:
			return -1

		parsed_rule = parser.parse(
			self.get_preprocessed_rule_str().split())

		self.set_parsed_rule(parsed_rule)

		if parsed_rule == None:
			return 0

		rule_spec = self.get_rule_spec()
		if rule_spec == None:
			return 0

		intf_str = rule_spec.get('i')
		if intf_str == None:
			intf_str = rule_spec.get(
					'in_interface')
			option = '--in-interface'
		else:
			option = '-i'

		if intf_str != None:
			self.set_input_intf(intf_str)
			self.set_input_intf_option(option)

		intf_str = rule_spec.get('o')
		if intf_str == None:
			intf_str = rule_spec.get(
					'out_interface')
			option = '--out-interface'
		else:
			option = '-o'

		if intf_str != None:
			self.set_output_intf(intf_str)
			self.set_output_intf_option(option)

		return 0

	def get_input_intf(self):
		return self.input_intf

	def get_output_intf(self):
		return self.output_intf

	def is_valid_table(self, table):
		# if not swp interface, then table
		# must be one of the supported tables
		if (self.get_type() == aclRuleType.iptables):
			if table not in iptables.kernel_tables:
				return 0
			else:
				return 1
		elif (self.get_type() == aclRuleType.ip6tables):
			if table not in ip6tables.kernel_tables:
				return 0
			else:
				return 1


	def applies_to_swp_interface(self):
		""" Returns 1 if rule applies to non eth interface
		0 if not """
		blacklist_intf_pattern = '^eth'
		input_interface = self.get_input_intf()
		output_interface = self.get_output_intf()

		if (input_interface == None and
			output_interface == None):
			return 1

		if input_interface != None:
			input_intf_list = input_interface.split(',')
			for intf in input_intf_list:
				if re.search(blacklist_intf_pattern,
					intf) == None:
					# If you find any interface that is
					# not blacklisted, assume it applies
					# to swp port
					return 1

		if output_interface != None:
			output_intf_list = output_interface.split(',')
			for intf in output_intf_list:
				if re.search(blacklist_intf_pattern,
					intf) == None:
					# If you find any interface that is
					# not blacklisted, assume it applies
					# to swp port
					return 1

		return 0


	def dump(self):
		pp = pprint.PrettyPrinter(indent=4)
		print 'rule_str : %s' %self.rule_str
		print 'rule_type : %d' %self.type
		print 'preprocessed rule str : ' + self.preprocessed_rule_str
		print 'parsed_rule : '
		pp.pprint(self.parsed_rule)
		print 'processed rule list : '
		pp.pprint(self.processed_rule_str_list)


class aclPolicy(object):
	""" acl policy """

	def __init__(self, name, env_vars={}):
		self.name = name
		self.lineno = 0
		self.rules = []
		self.iptables_raw = []
		self.env_vars = {}
		self.env_vars_global = env_vars

	def get_rules(self):
		return self.rules

	def get_name(self):
		return self.name

	def save_var(self, key, value):
		self.env_vars[key] = value

	def save_rule(self, rule):
		self.rules.append(rule)
		
	def save_iptables_raw(self, line):
		self.iptables_raw.append(self, line);

	def parse_iptables_rules(self, rule):
		return aclRule(rule, aclRuleType.iptables)

	def parse_ip6tables_rules(self, rule):
		return aclRule(rule, aclRuleType.ip6tables)

	def parse_ebtables_rules(self, rule):
		return aclRule(rule, aclRuleType.ebtables)

	rule_block_parsers = { '[iptables]' :
				{ 'type' : aclRuleType.iptables,
				  'parse_func': parse_iptables_rules,
				  'save_func': save_rule,},
			       '[ip6tables]' : 
				{ 'type' : aclRuleType.ip6tables,
			    	  'parse_func': parse_ip6tables_rules,
				  'save_func': save_rule,},
			       '[ebtables]' : 
				{ 'type' : aclRuleType.ebtables,
			    	  'parse_func': parse_ebtables_rules,
				  'save_func': save_rule},
			       '[iptables-raw]' : 
				{ 'type' : aclRuleType.iptables_raw,
				'save_func': save_iptables_raw}}
	

	def dump(self):
		""" Dump acl policy """
		i = 0
		pp = pprint.PrettyPrinter(indent=4)

		print 'Dumping acl policy : ' + self.get_name()
		print '========================='
		print 'Env vars: '
		print '---------'
		pp.pprint(self.env_vars)

		print '\n'

		print 'Rules: '
		print '------\n'

		for r in self.rules:
			print 'rule %d' %i + ' : '
			print '---------'
			r.dump()
			i = i + 1
			print '\n'


	def read_rules(self):
		""" Read acl rules from acl policy file """
		rule_block_parser = None
		rulefile_lines = []
		lineno = 0

		try:
			rulefile = open(self.name, "r")
			rulefile_lines = rulefile.readlines()
		except Exception as e:
			raise RuntimeError(str(e))

		for line in rulefile_lines:
			lineno = lineno + 1

			l = line.strip()
			l = l.strip('\n')

			if len(l.strip()) == 0:
				continue

			if l[0] == '#':
				continue;

			#print 'processing line  \"' + l + '\"'

			# If variable, save it 
			if re.search('^.*=.*', l, 0) != None:
				l = re.sub(r'\s+', '', l)
				l = l.rstrip('\n')
				var = string.split(l, '=', 1)

				if len(var[0]) > 0 and len(var[1]) > 0:
					self.save_var(var[0], var[1])
				continue

			parser_data = aclPolicy.rule_block_parsers.get(l)
			if parser_data != None:
				rule_block_parser = parser_data
				tmp_rulestr_dict = {}
				continue
			else:
				if re.search(r'\[.*\]', l, 0) != None:
					print 'error: unknown rule type ' + l
					return -1

			if rule_block_parser != None:
				# We are inside a rule block, parse the rule
				rule = None
				if rule_block_parser.get('parse_func') != None:
					rule = rule_block_parser['parse_func'](
							self, l)
					rule.set_lineno(lineno)

				if rule_block_parser['save_func'] != None:
					if rule != None:
						# Save the parsed rule
						rule_block_parser['save_func'](
								self, rule)
						rule.set_lineno(lineno)

						if tmp_rulestr_dict.get(
							rule.get_rule_str()) != None:
							print 'error: duplicate rule at lineno %d' %rule.get_lineno()
							return -1

						tmp_rulestr_dict[rule.get_rule_str()] = 1

					else:
						# Save raw lines
						rule_block_parser['save_func'](
								self, l)
			else:
				print ('warn: ignoring rule \'%s\' at lineno %d. (%s)'
						%(l, lineno, 'unable to determine rule type'))

		return 0


	def expand_interface_list(self, intf_str):
		intf_list = intf_str.split(',')

		# XXX: Process any regular expression

		return intf_list


	def process_rule_interface(self, rule, interface_type):
		processed_rules = rule.get_processed_rule_str_list()
		option = ''
		expanded_rule_list = []
		intf_str = None


		if interface_type == 0:
			intf_str = rule.get_input_intf()
			option = rule.get_input_intf_option()
		else:
			intf_str = rule.get_output_intf()
			option = rule.get_output_intf_option()

		if intf_str == None:
			# XXX: Or maybe generate two rules one
			# for management interface and the other for
			# swp+
			return 0

		pattern = option + ' ' + intf_str

		intf_list = self.expand_interface_list(intf_str)
		if len(intf_list) == 1:
			return 0

		for r in processed_rules:
			for i in intf_list:
				expanded_rule_list.append(r.replace(pattern,
							option + ' ' + i))


		# Replace the interface list
		rule.set_processed_rule_str_list(expanded_rule_list)

		return 0


	def expand_chain_list(self, chain_str):
		chain_list = chain_str.split(',')

		# XXX: Process any regular expression

		return chain_list

	def process_table(self, rule):
		"""Process table substitutions"""
		expanded_rule_list = []
		processed_rules = rule.get_processed_rule_str_list()

		table = rule.get_table()
		if table != None:
			for r in processed_rules:
				# Delete '-t <table>' from rule
				expanded_rule_list.append(r.replace('-t %s' %table,''))

		# Replace the interface list
		rule.set_processed_rule_str_list(expanded_rule_list)

		return 0
	
	def process_rule_chain(self, rule):
		"""Process chain substitutions"""

		processed_rules = rule.get_processed_rule_str_list()
		parsed_rule = rule.get_parsed_rule()
		expanded_rule_list = []

		parsed_rule_command = parsed_rule.get('command')
		parsed_rule_command_args = parsed_rule.get(parsed_rule_command)
		chain = parsed_rule_command_args.get('chain')
		if chain == None:
			return 0

		chain_list = self.expand_chain_list(chain)
		if len(chain_list) == 1:
			return 0

		for r in processed_rules:
			for c in chain_list:
				expanded_rule_list.append(r.replace(chain,c))


		# Replace the interface list
		rule.set_processed_rule_str_list(expanded_rule_list)

		return 0


	def process_intf_arg(self, rule):
		"""Process rule interface """

		# Process input interface and rewrite if required
		ret = self.process_rule_interface(rule, 0)
		if ret != 0:
			return -1


		# Process output interface and rewrite if required
		return self.process_rule_interface(rule, 1)


	def process_chain_arg(self, rule):
		# Process chain and rewrite if required
		return self.process_rule_chain(rule)

	def validate_intf_str(self, intf_str):
		# Check interface string
		for i in intf_str.split(','):
			if (re.search('swp', i) != None and
				re.search('\\+', i) != None):
			# Dont support swp<num>+
				if i != 'swp+':
					return -1
		return 0


	def validate_rule(self, rule):
		err = 0
		unsupported_strings = []
		valid_chains_for_swp_ports = ['INPUT', 'OUTPUT', 'FORWARD']
		processed_rules = rule.get_processed_rule_str_list()
		in_intf_str = rule.get_input_intf()
		out_intf_str = rule.get_output_intf()
		table = rule.get_table()

		# XXX: validate_rule_block checks for LOG target
		# with constraints. So comment out this check
		#if (self.is_log_rule(rule) == 1 and
		#		rule.applies_to_swp_interface() == 1):
		#	print ('error: line %d : ' %rule.get_lineno() +
		#		'LOG target is currently not supported for '
		#		'swp interfaces')
		#	err += 1

		if in_intf_str != None:
			ret = self.validate_intf_str(in_intf_str)
			if ret != 0:
				print ('error: line %d : ' %rule.get_lineno() +
					'unsupported interface string %s'
					%in_intf_str)
				err += 1


			# Check table validity, for given input interface
			if re.search('swp', in_intf_str) != None:
				# If interface list has swp, then table must be
				# filter
				if (table is not None and
					table not in ['filter', 'mangle']):
					print ('error: line %d : '
						%rule.get_lineno() +
						'table %s' %table +
						' not supported for swp '
						+ 'interfaces')
					err += 1
			elif rule.is_valid_table(table) == 0:
				print ('error: line %d : '
					%rule.get_lineno() +
					'table %s' %table +
					' not supported')
				err += 1

		if (out_intf_str != None):
			ret = self.validate_intf_str(out_intf_str)
			if ret != 0:
				print ('error: line %d : ' %rule.get_lineno() +
					'unsupported interface string %s'
					%out_intf_str)
				err += 1

			if (re.search('swp', out_intf_str) != None):
				# If interface list has swp, then table must be
				# filter
				if table != None and table != 'filter':
					print ('error: line %d : '
						%rule.get_lineno() +
						'table %s' %table +
						' not supported for swp interfaces')
					err += 1
			elif table != None and rule.is_valid_table(table) == 0:
				print ('error: line %d : '
					%rule.get_lineno() +
					'table %s' %table +
					' not supported')
				err += 1

		# sanity check on input/output interface option
		chain = rule.get_chain()
		if chain != None:
			if (re.search('OUTPUT', chain) != None and 
				in_intf_str != None):
				print ('error: line %d : input '
					'interface specified with '
					'OUTPUT chain' %rule.get_lineno())
				err += 1
			elif (re.search('INPUT', chain) != None and 
				out_intf_str != None):
				print ('error: line %d : output '
					'interface specified with '
					'INPUT chain' %rule.get_lineno())
				err += 1

			applies_to_swp = rule.applies_to_swp_interface()
			if (applies_to_swp == 1):
				for c in chain.split(','):
					if c not in valid_chains_for_swp_ports:
						print ('error: line %d : '
							%rule.get_lineno() +
							'Invalid chain %s'
							%chain + '. Supported' +
							' chains for ' +
							'swp ports :' +
						str(valid_chains_for_swp_ports))
						err += 1


		# This is a simple check, guess unsupported config
		# by a simple string match wherever we can
		for r in processed_rules:
			for u in unsupported_strings:
				if re.search(u, r) != None:
					print ('error: line %d :'
						%rule.get_lineno() +
						' unsupported %s' %u)
					err += 1

		#
		# XXX: For global and rules that contain swp interfaces
		# make sure chain only contains the built-in chain
		#

		if err != 0:
			return -1

		return 0


	# Rule processing handlers, each handler takes a single rule as arg
	rule_processing_handlers = { 
			aclRuleType.iptables : {
				'00_validate_rule' : validate_rule,
				'01_process_table' : process_table,
				'process_intf' : process_intf_arg,
				'process_chain' : process_chain_arg,
			},
			aclRuleType.ip6tables : {
				'00_validate_rule' : validate_rule,
				'01_process_table' : process_table,
				'process_intf' : process_intf_arg,
				'process_chain' : process_chain_arg,
			},
			aclRuleType.ebtables : {
				'00_validate_rule' : validate_rule,
				'01_process_table' : process_table,
				'process_intf' : process_intf_arg,
				'process_chain' : process_chain_arg,
			}
	}

	def is_log_rule(self, rule):
		if (re.search('-j LOG', rule.get_rule_str()) != None or
			(re.search('-j ULOG', rule.get_rule_str()) != None) or
			(re.search('--log', rule.get_rule_str()) != None) or
			(re.search('--log-', rule.get_rule_str()) != None)):
			return 1

		return 0

	def validate_logrule_sibling(self, log_rule, log_rule_sibling):
		""" Checks if log_rule_sibling is a valid sibling rule
		for log targets """
		srule = None

		if log_rule.get_type() != log_rule_sibling.get_type():
			return 1

		if (self.is_log_rule(log_rule) == 1 and
				self.is_log_rule(log_rule_sibling) == 1):
			return 1

		log_rule_str = log_rule.get_rule_str()

		if re.search('-j LOG', log_rule_str) != None:
			tmp_log_rule_strlist = re.findall('.*-j LOG',
							log_rule_str)
			srule = string.replace(tmp_log_rule_strlist[0],
					' -j LOG', ' -j DROP')
			#		' -j [a-zA-Z]+')
			srule = srule.replace('$', '\\$')

		elif re.search('-j ULOG', log_rule_str) != None:
			tmp_log_rule_strlist = re.findall('.*-j ULOG',
							log_rule_str)
			srule = string.replace(tmp_log_rule_strlist[0],
						' -j ULOG',
						' -j [a-zA-Z]+')
			srule = srule.replace('$', '\\$')
		else:
			# Nothing to check, return 0
			return 0
	
		if srule == None:
			return 0

		pattern = re.compile(srule)
		if pattern.search(log_rule_sibling.get_rule_str()) == None:
			return 1

		return 0

	def validate_rule_block(self):
		found_log_rule = 0
		err = 0
		rules = self.get_rules()


		# Validate LOG rules, they always need to be accompanied
		# by a sibling rule
		log_errmsg = ('LOG rule must be followed by a rule with ' +
				'exact same match and target DROP ')
		for r in rules:
			rule_str = r.get_rule_str()

			applies_to_swp_intf = r.applies_to_swp_interface()

			if r.get_type() == aclRuleType.ebtables:
				if (applies_to_swp_intf == 1 and
					re.search('--log', rule_str) != None and
					re.search('-j DROP', rule_str) == None):
					print('error: line %d : '
						%r.get_lineno() + ' log rule '
						+ 'must contain target DROP')
					err += 1
				continue

			if self.is_log_rule(r) == 1:
				# If found LOG rule, it should be accompanied by
				# a similar rule without the log target
				if found_log_rule == 1:
					print('error: line %d : '
						%log_rule.get_lineno() +
						log_errmsg)
					err += 1
					found_log_rule = 0

				if applies_to_swp_intf == 1:
					found_log_rule = 1
					log_rule = r
			else:
				if found_log_rule == 1:
					if r.get_type() != log_rule.get_type():
						print('error: line %d : '
							%r.get_lineno() +
							log_errmsg)
						err += 1
						found_log_rule = 0
						continue

					if self.validate_logrule_sibling(
						log_rule, r) != 0:
						print('error: line %d : '
							%r.get_lineno() +
							log_errmsg)
						err += 1
					else:
						log_rule.set_flag(aclRule.HAS_SIBLING)

					found_log_rule = 0

		if found_log_rule == 1:
			print('error: line %d : ' %log_rule.get_lineno() +
				log_errmsg)
			err += 1

		if err != 0:
			return -1

		return 0

	def substitute_vars(self, rule):
		[rule.substitute_var(key, val) for key,val in self.env_vars.items()]
		[rule.substitute_var(key, val) for key,val in self.env_vars_global.items()]

	def process(self):
		""" Pre process environment variables in rules """
		ret = self.read_rules()
		if ret != 0:
			return -1

		[self.substitute_vars(r) for r in self.rules]
		for r in self.rules:
			ret = r.parse()
			if ret:
				print('error parsing rule at line %d'
					%r.get_lineno())
				return -1

		""" Initialize final processed list with preprocessed strings """
		for r in self.rules:
			r.append_processed_rule_str_list(
					r.get_preprocessed_rule_str())

		# Validate all preprocessed rule str 
		ret = self.validate_rule_block()
		if ret != 0:
			return -1

		for r in self.rules:
			if not r.get_parsed_rule():
				continue

			handlers = self.rule_processing_handlers.get(
							r.get_type())
			if not handlers:
				print ('Warn: Unsupported rule type %d'
						%r.get_type() + ' found')
				continue

			for hndlr_name, hndlr in sorted(handlers.iteritems()):
				ret = hndlr(self, r)
				if ret != 0:
					print ('error ' +
						'processing rule \'%s\''
							%r.get_rule_str())
					return ret
		return 0
