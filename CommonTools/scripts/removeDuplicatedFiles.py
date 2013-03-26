#!/usr/bin/python
# Author: Tae.Jeong.Kim@cern.ch
# Filename: analysis.py
# How to run: analysis.py ../tagged-person-status.txt 

import sys

path = sys.argv[1]
option = sys.argv[2]

import os,commands
prev = ""
cmd  = 'nsls %s/ ' % (path)
for i in commands.getoutput(cmd).split('\n'):
  splitfilename = i.split("_")
  if splitfilename[2] == prev:
    if( option == "true" ):
      print i
      os.system("rfrm -r "+path+"/"+i)
    elif( option == "false"):
      print i
  prev = splitfilename[2]

