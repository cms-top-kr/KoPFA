#!/usr/bin/env python

from string import Template
import sys,os

# use in the folder Out   
# modify the name aaa by a channel for merging.

aaa="TTbarTuneZ2"
os.system("ls %s/Res/val* -1 | grep -c val > log  "% aaa)
f = open("log","r")
bb = f.read()
aa=int(bb)
print "entries : %d "%aa

if aa > 1000:
    for i in range(0,10):
        cmd_=("hadd %s/vallot_" % aaa)
        cmd_=cmd_+("%s_" % aaa)
        cmd_=cmd_+("n1%d.root " % i)
        cmd_=cmd_+("%s/Res/vallot_" % aaa)
        cmd_=cmd_+("%s_" % aaa)
        cmd_=cmd_+("1%d*" % i)
        command_=cmd_
        print command_
        os.system(command_)
else:
    cmd_=("hadd %s/vallot_" % aaa)
    cmd_=cmd_+("%s_" % aaa)
    cmd_=cmd_+("n1.root ")
    cmd_=cmd_+("%s/Res/vallot_" % aaa)
    cmd_=cmd_+("%s_" % aaa)
    cmd_=cmd_+("1*" )
    command_=cmd_
    print command_
    os.system(command_)


for i in range(2,10):
    cmd_=("hadd %s/vallot_" % aaa)
    cmd_=cmd_+("%s_" % aaa)
    cmd_=cmd_+("n%d.root " % i)
    cmd_=cmd_+("%s/Res/vallot_" % aaa)
    cmd_=cmd_+("%s_" % aaa)
    cmd_=cmd_+("%d*" % i)
    command_=cmd_
    print command_
    os.system(command_)

cmd_=("cp %s/Res/vallot_"% aaa)
cmd_=cmd_+("%s_0.root" % aaa)
cmd_=cmd_+(" %s/" % aaa)
command_=cmd_
print command_
os.system(command_)

