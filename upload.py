#!/usr/bin/python
#usage: ./filename.py "commit content"
from subprocess import call
import sys

call('git add .', shell=True)
call('./recent_updates.py', shell=True)
call(['git', 'commit', '-m', sys.argv[1]])
call('git push', shell=True)
