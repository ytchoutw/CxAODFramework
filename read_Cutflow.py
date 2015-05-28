#!/usr/bin/python

import os, math, sys, ROOT
ROOT.gROOT.SetBatch(True)

count = 0.0 

#fb
luminosity = 5 




cut = [
"All",
"Pre",
"250MET",
"350MET",
"onefat",
"eleveto",
"muonveto",
"photonveto",
"addjet",
"phimet",
"500MET",
"mFatJ",
"mFatJ[H]",
"subjet",
"2subjet",
"2Bsubjet",
]


samples = [
"monoWjjIsrConD1m50",
"monoWjjIsrConD1m1300",
"monoWjjIsrConD5m50",
"monoWjjIsrConD5m1300",
"monoWjjIsrConD9m50",
"monoWjjIsrConD9m1300",

"monoWjjIsrDesD1m50",
"monoWjjIsrDesD1m1300",
"monoWjjIsrDesD5m50",
"monoWjjIsrDesD5m1300",
"monoWjjIsrDesD9m50",
"monoWjjIsrDesD9m1300",
"Zvv",
"Wev",
"Wmuv",
"Wtauv",
"Zll",
"ttbarallhad",
"ttbarnonall",
"singletop",
"diboson",
"dijet",
"gamma",
]

count_noweight = []
count_weight = []
count_noweight_err = []
count_weight_err = []

for isamples in samples:
	cutflow_row = []
	cutflow_row.append(isamples)
	for i in range(len(cut)):
		cutflow_row.append(count)
	count_noweight.append(cutflow_row)
	count_weight.append(cutflow_row)
	count_noweight_err.append(cutflow_row)
	count_weight_err.append(cutflow_row)	
	

# count
for subdir, dirs, files in os.walk("."):
	for file in files :
		if file.find("hist-") >= 0 :
			my_file = os.path.join(subdir, file)
			print my_file
			#
			f = ROOT.TFile.Open(my_file,"read")
			h = f.Get("Cutflow")
			n_count = []
			err = []
			for i in range(len(cut)):
				n_count.append(0)
				err.append(0)
			for i in range(len(cut)):
				n_count[i] = h.GetBinContent(h.GetXaxis().FindBin(cut[i]))
				err[i] = h.GetBinError(h.GetXaxis().FindBin(cut[i]))		
			for i_count in count_weight :
				if my_file.find(i_count[0]) >=0 :
					for i in range(len(cut)):
						i_count[i+1] = n_count[i]*luminosity*1000
			for i_count in count_weight_err :
				if my_file.find(i_count[0]) >=0 :
					for i in range(len(cut)):			
						i_count[i+1] = err[i]*luminosity*1000
			h_no = f.Get("Cutflow_noweight")
			for i in range(len(cut)) :
				n_count[i] = h_no.GetBinContent(i+1)
				err[i] = h_no.GetBinError(i+1)		
			for i_count in count_noweight :
				if my_file.find(i_count[0]) >=0 :
					for i in range(len(cut)) :
						i_count[i+1] = n_count[i]
			for i_count in count_noweight_err :
				if my_file.find(i_count[0]) >=0 :
					for i in range(len(cut)) :
						i_count[i+1] = err[i]
			
			f.Close()			
    

# write
out_file = open('./cutflow_number.txt','w')

#weight
for i_count in range(len(count_weight)):	
	if	count_weight[i_count][1]==0:
		continue
	out_file.write(str(count_weight[i_count][0])+"\n")
	for i in range (len(cut)) :
		out_file.write(str(i)+"\t"+cut[i]+"\t"+str(count_weight[i_count][i+1])+"+-"+str(count_weight_err[i_count][i+1])+"\n")
		
#noweight	
for i_count in range(len(count_noweight)) :	
	if	count_noweight[i_count][1]==0:
		continue
	out_file.write(str(count_noweight[i_count][0])+"\n")
	for i in range (len(cut)) :
		out_file.write(str(i)+"\t"+cut[i]+"\t"+str(count_noweight[i_count][i+1])+"+-"+str(count_noweight_err[i_count][i+1])+"\n")		

out_file.close()



