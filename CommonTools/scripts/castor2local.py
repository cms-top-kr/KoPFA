#!/usr/bin/python
# Author: Tae.Jeong.Kim@cern.ch
# Filename: analysis.py
# How to run: analysis.py ../tagged-person-status.txt 

import sys

path = sys.argv[1]
to = sys.argv[2]

import os,commands
cmd  = 'nsls %s/ ' % (path)
list = []

for f in commands.getoutput(cmd).split('\n'):
  print "copying..." + f
  os.system("rfcp " + path+"/"+ f+ " " + to +" &")




