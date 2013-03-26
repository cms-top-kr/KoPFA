#!/usr/bin/python
# Author: Tae.Jeong.Kim@cern.ch
# Filename: castor2local.py
# How to run: castor2local.py from to 

import sys

path = sys.argv[1]
to = sys.argv[2]

import os,commands
cmd  = 'nsls %s/ ' % (path)
list = []

for f in commands.getoutput(cmd).split('\n'):
  print "copying..." + f
  os.system("rfcp " + path+"/"+ f+ " " + to +" &")




