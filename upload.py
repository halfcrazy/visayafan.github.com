#!/usr/bin/python
import subprocess
import sys

subprocess.Popen(args='git add .', shell=True)
cmt = sys.argv[1]
subprocess.Popen(args='git commit -m'+cmt, shell=True)
subprocess.Popen(args='git push')
