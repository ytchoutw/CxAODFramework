#!/usr/bin/python

import os, math, sys

in_file = sys.argv[1]

type_file = [
#"_tuple.root/", # tuple
"_outputLabel.root/", # CxAOD
#"_hist-output.root/", # histo for normalisation
]

#### output job file list to read
read_file = open('./'+in_file, 'r')

for line in read_file :
 for type in type_file :
  # protect from commented lines
  if line.find("#")>=0 : continue
  # define input/output jobs
  sample = line.strip()
  # define command and take car of / in names
  command = "dq2-get -f \'*.root*\' "+sample+type
  print command
  os.system(command)

print "end of script"
