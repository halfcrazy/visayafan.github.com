#!/usr/bin/python
import subprocess
import sys

subprocess.call('git add .', shell=True)
subprocess.call(['git', 'commit', '-m', sys.argv[1]])
subprocess.call('git push', shell=True)
