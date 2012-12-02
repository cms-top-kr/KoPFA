#!/usr/bin/env python

import fnmatch
import os
import sys
import subprocess

if __name__ == '__main__':

    from optparse import OptionParser
    
    parser = OptionParser()
    parser.add_option("-g", "--glob", dest="glob",action="store_true", default=False,help='Turn file globbing on')
    parser.add_option("-r", "--rfio", dest="rfio",action="store_true", default=False,help='Turn rfio name on')
    parser.add_option("-c", "--cfg", dest="cfg",action="store_true", default=False,help='Turn file cfg output on')
    (options, args) = parser.parse_args()

    fileNames = args

    if options.cfg:

        print """
import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
		     noEventSort = cms.untracked.bool(True),
		     duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
		     fileNames = readFiles
                    )
readFiles.extend(["""

    def printDir(fileName):
        glob = None
        castorDir = fileName
        if options.glob:
            castorDir = os.path.dirname(fileName)
            glob = os.path.basename(fileName)


        output = subprocess.Popen(['nsls',castorDir], stdout=subprocess.PIPE).communicate()[0]
        for o in output.split('\n'):
            if o:
                path = os.path.join(castorDir,o)
                if options.glob and not fnmatch.fnmatch(path, glob):
                    continue
                if options.cfg:
                    print "\t'rfio://%s'," % path
                elif options.rfio:
                    print 'rfio://%s' % path
                else:
                    print path

    for f in fileNames:
        printDir(f)

    if options.cfg:
        print """]
        )"""

