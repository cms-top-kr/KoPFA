#!/usr/bin/env python
# Author: Tae.Jeong.Kim@cern.ch
import os
import re
import sys
import time
import commands

from os.path import join, getsize

def doWork(finalpath, action):

  sample = os.path.basename(finalpath)

  if action == "report" or action == "submit":
    joblist = os.listdir(finalpath+"/Log")
    for i in joblist:
      num = i.split("_")
      file = finalpath+"/Res/vallot_"+sample+"_"+num[1]+".root"
      filesize = 0
      if os.path.isfile( file ):
        filesize = os.path.getsize( file )
      if filesize < 10000:
        if action == "report":
          if filesize == 0:
            print "Bad job number : " + num[1] + " : file was not created"
          else: 
            print "Bad job number : " + num[1] + " : file size is too small. it must be corrupted." 
        if action == "submit":
          print "Submitting job : " + num[1] 
          currdir = commands.getoutput('pwd')
          os.chdir("%s/Log/Job_%s" % (finalpath,num[1]) )
          os.system("bsub -q 8nm < ./batchScript.sh")
          os.chdir(currdir)

  if action == "merge":
    pathdir = os.path.dirname(finalpath)
    print "Merging files in " + finalpath
    destinationfile = pathdir+"/vallot_"+sample+".root"
    if os.path.isfile( destinationfile ):
      print destinationfile + " exists."
    else:
      os.system("hadd -f "+destinationfile+" "+finalpath+"/Res/vallot_*.root")

    x = raw_input("Remove directory %s (y/n)?" % (finalpath))
    if x == "y":
      os.system("rm -rf "+finalpath+"/Log")
      os.system("rm -rf "+finalpath+"/Res")
      os.system("rm -rf "+finalpath)

def jobReport( path , action):
   list = os.listdir(path)
   for sample in list:
     finalpath = path + "/" + sample
     if os.path.isdir(finalpath):
       print "Checking " + finalpath
       logdir = os.path.exists(finalpath+"/Log")
       if logdir == True:
         doWork(finalpath, action)
       else:
         print "No sample Log directory!"
  

if __name__ == '__main__':

    from optparse import OptionParser

    parser = OptionParser()
    parser.usage = """
    %prog [options] <sample_dir>
    
    Prints the list of bad jobs.
    Using the options, you can get a log of what happened during each bad job,
    and you can resubmit these jobs.
    """

    parser.add_option("-r", "--report", dest="report",
                      action = 'store_true',
                      default=False,
                      help='Print report for bad jobs.')

    parser.add_option("-s", "--submit", dest="submit",
                      action = 'store_true',
                      default=False,
                      help='Resubmission command')

    parser.add_option("-m", "--merge", dest="merge",
                      action = 'store_true',
                      default=False,
                      help='hadd -f merged.root *.root')


    (options,args) = parser.parse_args()
 
    path = args[0]

    if options.report:
        jobReport(path, "report")
    if options.submit:
        jobReport(path, "submit")
    if options.merge:
        jobReport(path, "merge")

