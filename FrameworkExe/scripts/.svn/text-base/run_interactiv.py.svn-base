#!/usr/bin/python

import os, math, sys


#### input file -> take care not to put / in the end, it will be handled later
file_in = sys.argv[1]
sample_file = open('./FrameworkSub/In/'+file_in, 'r')

#### make a tmp dir to store the submit dirs
os.system("mkdir tmp")

for i_sample in sample_file :
  # protect from commented lines
  if i_sample.find("#")>=0 : continue
  # define input jobs
  sample_in = i_sample.strip()
  # if need to prune the input name, do here
  small_sample_in = sample_in
  # define output jobs
  sample_out = small_sample_in
  # define submit dir name
  submit_dir = "tmp/submitDir_"+small_sample_in
  # define command and take care of / in names
  command = "hsg5frameworkTuple "+sample_in+" "+sample_out+" "+submit_dir
  print command
  os.system(command)

sample_file.close()
