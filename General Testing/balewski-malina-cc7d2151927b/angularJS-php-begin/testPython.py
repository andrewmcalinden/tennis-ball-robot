#!/usr/bin/env python
import sys
print 'testPython: Number of arguments:', len(sys.argv),'  List:', str(sys.argv)
inp1=99
if  len(sys.argv)>1:
    inp1=sys.argv[1]
print ' testPython: inp1=',inp1
