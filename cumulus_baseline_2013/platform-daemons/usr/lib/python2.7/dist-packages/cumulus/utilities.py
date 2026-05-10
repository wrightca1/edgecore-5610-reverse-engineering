#!/usr/bin/python
#--------------------------------------------------------------------------
#
# Copyright 2012 Cumulus Networks, inc  all rights reserved
#
#--------------------------------------------------------------------------

try:
        import os
        import fcntl

except ImportError, e:
        raise ImportError (str(e) + "- required module not found")


class utilities:

	@classmethod
	def lockFile(cls, lockfile):
		try:
			fp = os.open(lockfile, os.O_CREAT | os.O_TRUNC | os.O_WRONLY)
			fcntl.flock(fp, fcntl.LOCK_EX | fcntl.LOCK_NB)
		except IOError:
			return False

		return True

