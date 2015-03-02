#!/usr/bin/python

import os, math, sys, ROOT
ROOT.gROOT.SetBatch(True)

count = 0.0 

#fb
luminosity = 2 

count_noweight = [
["Zvv",count,count,count,count,count,count,count,count,count,count,count,count,count,count,count,count,count,count],
["Wlv",count,count,count,count,count,count,count,count,count,count,count,count,count,count,count,count,count,count],
["Zll",count,count,count,count,count,count,count,count,count,count,count,count,count,count,count,count,count,count],
["top",count,count,count,count,count,count,count,count,count,count,count,count,count,count,count,count,count,count],
["singletop",count,count,count,count,count,count,count,count,count,count,count,count,count,count,count,count,count,count],
["diboson",count,count,count,count,count,count,count,count,count,count,count,count,count,count,count,count,count,count],
]


count_weight = [
["Zvv",count,count,count,count,count,count,count,count,count,count,count,count,count,count,count,count,count,count],
["Wlv",count,count,count,count,count,count,count,count,count,count,count,count,count,count,count,count,count,count],
["Zll",count,count,count,count,count,count,count,count,count,count,count,count,count,count,count,count,count,count],
["top",count,count,count,count,count,count,count,count,count,count,count,count,count,count,count,count,count,count],
["singletop",count,count,count,count,count,count,count,count,count,count,count,count,count,count,count,count,count,count],
["diboson",count,count,count,count,count,count,count,count,count,count,count,count,count,count,count,count,count,count],
]


# count
for subdir, dirs, files in os.walk(".") :
	for file in files :
		if file.find("hist-") >= 0 :
			my_file = os.path.join(subdir, file)
			print my_file
			#
			f = ROOT.TFile.Open(my_file,"read")
			h = f.Get("Cutflow")
			n_count = [0,0,0,0,0,0,0,0,0,0,0]
			err = [0,0,0,0,0,0,0,0,0,0,0]
			for i in range(1,10) :
				n_count[i] = h.GetBinContent(i)
				err[i] = h.GetBinError(i)		
			for i_count in count_weight :
				if my_file.find(i_count[0]) >=0 :
					for i in range(1,10) :
						i_count[2*i-1] = n_count[i]*luminosity*1000
						i_count[2*i] = err[i]*luminosity*1000
			h_no = f.Get("Cutflow_noweight")
			for i in range(1,10) :
				n_count[i] = h_no.GetBinContent(i)
				err[i] = h_no.GetBinError(i)		
			for i_count in count_noweight :
				if my_file.find(i_count[0]) >=0 :
					for i in range(1,10) :
						i_count[2*i-1] = n_count[i]
						i_count[2*i] = err[i]
			
			f.Close()			
    

# write
out_file = open('./cutflow_number.txt','w')

#weight
for i_count in count_weight :	
	out_file.write(str(i_count[0])+"\n")
	for i in range (1,10) :
		out_file.write(str(i)+"\t"+str(i_count[2*i-1])+"+-"+str(i_count[2*i])+"\n")
		
#noweight	
for i_count in count_noweight :	
	out_file.write(str(i_count[0])+"\n")
	for i in range (1,10) :
		out_file.write(str(i)+"\t"+str(i_count[2*i-1])+"+-"+str(i_count[2*i])+"\n")		
	
out_file.close()



