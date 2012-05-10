#!/usr/bin/python
# Author: Tae.Jeong.Kim@cern.ch
# Filename: analysis.py
# How to run: ./eps2pdf.py in your working directory where eps files are  

import sys

path = sys.argv[1]

import os,commands
cmd  = 'ls %s*.eps' % (path)

for i in commands.getoutput(cmd).split('\n'):
  print i
  os.system("epstopdf "+i)

