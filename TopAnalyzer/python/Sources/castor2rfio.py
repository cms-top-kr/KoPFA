#!/usr/bin/env python

import sys, os

def usage():
    print """Usage : castor2rfio.py [OPTIONS] PATH
OPTIONS :
    -h : Show this message
    -g : Turn file globbing on
    -r : rfio name on
    -c : Output with python configuration (globbing, rfio automatically on)
"""

def getListOfRootFiles(dirName):
    from subprocess import Popen, PIPE
    from re import match

    # Validate file path in castor
    if dirName[0] != '/':
        dirName = os.path.join(os.environ['CASTOR_HOME'], dirName)

    # Now path is validated. now try listing files
    lines = Popen(['nsls', dirName], stdout=PIPE).communicate()[0]
    rootFiles = {}
    for line in lines.strip().split('\n'):
        line = line.strip()

        # Check file extension
        if len(line) <= len('.root') or line[-len('.root'):] != '.root':
            continue

        fields = line.split('_')
        if len(fields) > 3:
            fileIndex = int(fields[-3])
            if fileIndex in rootFiles:
                print "#" * 80
                print "### Duplicated file entry found in the directory %s" % dirName
                print "### File index = %d" % fileIndex
                print "#" * 80

        rootFiles[fileIndex] = os.path.join(dirName, line)

    if len(rootFiles) == 0:
        print "#" * 80
        print "##### No root file found in the directory %s" % dirName
        print lines.strip()
        print "#" * 80

    return rootFiles.values()

if __name__ == '__main__':

    ## Parse options
    if len(sys.argv) < 2:
        usage()
        sys.exit(1)

    opts = ""
    args = []
    for arg in sys.argv[1:]:
        if arg[0] == '-' and len(arg) > 1:
            opts += arg[1:]
        else:
            args.append(arg)

    if 'h' in opts:
        usage()
        sys.exit(0)

    doCfg = 'c' in opts
    doGlob = doCfg or 'g' in opts
    doRfio = doCfg or 'r' in opts


    ## Output format
    outForm = "%s"
    if doRfio:
        outForm = 'rfio:' + outForm
    if doGlob:
        outForm = '"' + outForm + '"'
    if doCfg:
        outForm = outForm + ','
    outForm += '\n'

    ## Get list of root files
    rootFiles = getListOfRootFiles(args[0])
    
    ## Make output text
    outContent = ""

    if doCfg:
        outContent += """import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
    noEventSort = cms.untracked.bool(True),
    duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
    fileNames = readFiles
)
readFiles.extend([
"""

    for rootFile in rootFiles:
        outContent += outForm % rootFile

    if doCfg:
        outContent += '])'

    ## Print output
    print outContent
