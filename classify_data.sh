#!/bin/bash

suffix = .CxAOD.v01_data_CxAOD.root.

for sample in ZnunuB ZnunuC ZnunuL WenuB WenuC WenuL WmunuB WmunuC WmunuL WtaunuB WtaunuL WtaunuC ZeeC ZeeB ZeeL ZmumuB ZmumuC ZmumuL ZtautauB ZtautauC ZtautauL singletop_t singletop_s singletop_Wt ttbar dijet gamma ExcitedQ \
monoWjjIsrDesD1m50 monoWjjIsrDesD1m1300 monoWjjIsrDesD5m50 monoWjjIsrDesD5m1300 monoWjjIsrDesD9m50 monoWjjIsrDesD9m1300 \
monoWjjIsrConD1m50 monoWjjIsrConD1m1300 monoWjjIsrConD5m50 monoWjjIsrConD5m1300 monoWjjIsrConD9m50 monoWjjIsrConD9m1300 \
WjjWwxxm50 monoWjjWwxxm1300 monoWjjSimDesSsdMed100m50 monoWjjSimDesSsdMed1500m50 monoWjjSimDesSsdMed1500m1300 monoWjjSimDesSvdMed100m50 monoWjjSimDesSvdMed1500m50 \
monoWjjSimDesSvdMed1500m1300 monoWjjSimDesTsdMed100m50 monoWjjSimDesTsdMed1500m50 monoWjjSimDesTsdMed1500m1300 monoWjjSimConSsdMed100m50 monoWjjSimConSsdMed1500m50 \
monoWjjSimConSsdMed1500m1300 monoWjjSimConSvdMed100m50 monoWjjSimConSvdMed1500m50 monoWjjSimConSvdMed1500m1300 \
monoZjjIsrD1m50 monoZjjIsrD1m1300 monoZjjIsrD5m50 monoZjjIsrD5m1300 monoZjjIsrD9m50 monoZjjIsrD9m1300 \
monoZjjZzxxm50 monoZjjZzxxm1300 \
monoZjjSimSsdMed100m50 monoZjjSimSsdMed1500m50 monoZjjSimSsdMed1500m1300 monoZjjSimSvdMed100m50 monoZjjSimSvdMed1500m50 \
monoZjjSimSvdMed1500m1300 monoZjjSimTsdMed100m50 monoZjjSimTsdMed1500m50 monoZjjSimTsdMed1500m1300 \
monoHbb_mx1_xdxhDh monoHbb_mx65_xdxhDh monoHbb_mx1000_xdxhDh monoHbb_mx1_xgxFhDh monoHbb_mx65_xgxFhDh monoHbb_mx1000_xgxFhDh \
monoHbb_mx1_zpzp100 monoHbb_mx65_zpzp100 monoHbb_mx1000_zpzp100 

do
	mkdir $sample
done

for sample in Znunu Wenu Wmunu Wtaunu Zee Zmumu Ztautau 
do 
	mv user.*.mc14_13TeV.*${sample}*_BFilter*.CxAOD.v01_data_CxAOD.root.* ./${sample}B
	mv user.*.mc14_13TeV.*${sample}*FilterBVeto*.CxAOD.v01_data_CxAOD.root.* ./${sample}C
	mv user.*.mc14_13TeV.*${sample}*_CJetVetoBVeto*.CxAOD.v01_data_CxAOD.root.* ./${sample}L
done

mv user.*.mc14_13TeV.*jetjet*.CxAOD.v01_data_CxAOD.root.* ./dijet
mv user.*.mc14_13TeV.*_st_schan_*.CxAOD.v01_data_CxAOD.root.* ./singletop_s


for sample in ttbar gamma ExcitedQ \
monoWjjIsrDesD1m50 monoWjjIsrDesD1m1300 monoWjjIsrDesD5m50 monoWjjIsrDesD5m1300 monoWjjIsrDesD9m50 monoWjjIsrDesD9m1300 \
monoWjjIsrConD1m50 monoWjjIsrConD1m1300 monoWjjIsrConD5m50 monoWjjIsrConD5m1300 monoWjjIsrConD9m50 monoWjjIsrConD9m1300 \
WjjWwxxm50 monoWjjWwxxm1300 monoWjjSimDesSsdMed100m50 monoWjjSimDesSsdMed1500m50 monoWjjSimDesSsdMed1500m1300 monoWjjSimDesSvdMed100m50 monoWjjSimDesSvdMed1500m50 \
monoWjjSimDesSvdMed1500m1300 monoWjjSimDesTsdMed100m50 monoWjjSimDesTsdMed1500m50 monoWjjSimDesTsdMed1500m1300 monoWjjSimConSsdMed100m50 monoWjjSimConSsdMed1500m50 \
monoWjjSimConSsdMed1500m1300 monoWjjSimConSvdMed100m50 monoWjjSimConSvdMed1500m50 monoWjjSimConSvdMed1500m1300 \
monoZjjIsrD1m50 monoZjjIsrD1m1300 monoZjjIsrD5m50 monoZjjIsrD5m1300 monoZjjIsrD9m50 monoZjjIsrD9m1300 \
monoZjjZzxxm50 monoZjjZzxxm1300 \
monoZjjSimSsdMed100m50 monoZjjSimSsdMed1500m50 monoZjjSimSsdMed1500m1300 monoZjjSimSvdMed100m50 monoZjjSimSvdMed1500m50 \
monoZjjSimSvdMed1500m1300 monoZjjSimTsdMed100m50 monoZjjSimTsdMed1500m50 monoZjjSimTsdMed1500m1300 \
monoHbb_mx1_xdxhDh monoHbb_mx65_xdxhDh monoHbb_mx1000_xdxhDh monoHbb_mx1_xgxFhDh monoHbb_mx65_xgxFhDh monoHbb_mx1000_xgxFhDh \
monoHbb_mx1_zpzp100 monoHbb_mx65_zpzp100 monoHbb_mx1000_zpzp100

do
	mv user.*.mc14_13TeV.*$sample*.CxAOD.v01_data_CxAOD.root.* ./$sample
done
