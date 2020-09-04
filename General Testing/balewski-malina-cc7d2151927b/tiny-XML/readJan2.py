#!/usr/bin/env python

import xml.etree.ElementTree as ET
tree = ET.parse('dmtpcData.xml')
root = tree.getroot()

print 'root=',root.tag,'  attrib:',root.attrib
for child1 in root:
   print '  ',child1.tag,child1.text,child1.attrib
   for child2 in child1:
      print '     ',child2.tag,child2.text,child2.attrib
      for child3 in child2:
         print '          ',child3.tag,child3.text,child3.attrib
