#!/usr/bin/python

import os, math, sys

#### job version
job_version = ".CAOD_HIGG5D1.v00-00-05"

####
#user = "user.XXXX."
user = "group.phys-higgs."

#### input file -> take care not to put / in the end, it will be handled later
file_in = sys.argv[1]
sample_file  = open('./'+file_in, 'r')

#### output file, to take back jobs
out_file = open('./out_sample.txt', 'w')

for i_sample in sample_file :
  # protect from commented lines
  if i_sample.find("#")>=0 : continue
  #
  count = 0
  sample_out = user
  for char in i_sample :
    if char == "." : count += 1
    if count < 3 : sample_out += char
  sample_out += job_version+"\n"
  out_file.write(sample_out)

sample_file.close()
out_file.close()
