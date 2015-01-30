#!/usr/bin/python

import os, math, sys

#############################
#############################
# VERY IMPORTANT :
# be in the directory where you have dq2-get your jobs to execute this script
#############################
#############################

#############################
# parameters
#############################

test = True
#test = False

#mkdir = True
mkdir = False

samples_tag = "p1784"

nrj = [
"8",
"13",
]

production_tag = "00-00-05"

our_samples = [
["muonData",		"physics_Muons",	"none"],
["egammaData",		"physics_Egamma",	"none"],
["metData",		"physics_JetTauEtmiss",	"none"],
["ZeeB",		"ZeeMassiveCBPt",	"BFilter"],
["ZeeC",		"ZeeMassiveCBPt",	"CFilterBVeto"],
["ZeeL",		"ZeeMassiveCBPt",	"CVetoBVeto"],
["ZmumuB",		"ZmumuMassiveCBPt",	"BFilter"],
["ZmumuC",		"ZmumuMassiveCBPt",	"CFilterBVeto"],
["ZmumuL",		"ZmumuMassiveCBPt",	"CVetoBVeto"],
["ZtautauB",		"ZtautauMassiveCBPt",	"BFilter"],
["ZtautauC",		"ZtautauMassiveCBPt",	"CFilterBVeto"],
["ZtautauL",		"ZtautauMassiveCBPt",	"CVetoBVeto"],
["ZnunuB",		"ZnunuMassiveCBPt",	"BFilter"],
["ZnunuC",		"ZnunuMassiveCBPt",	"CFilterBVeto"],
["ZnunuL",		"ZnunuMassiveCBPt",	"CVetoBVeto"],
["WenuB",		"WenuMassiveCBPt",	"BFilter"],
["WenuC",		"WenuMassiveCBPt",	"CJetFilterBVeto"],
["WenuL",		"WenuMassiveCBPt",	"CJetVetoBVeto"],
["WmunuB",		"WmunuMassiveCBPt",	"BFilter"],
["WmunuC",		"WmunuMassiveCBPt",	"CJetFilterBVeto"],
["WmunuL",		"WmunuMassiveCBPt",	"CJetVetoBVeto"],
["WtaunuB",		"WtaunuMassiveCBPt",	"BFilter"],
["WtaunuC",		"WtaunuMassiveCBPt",	"CJetFilterBVeto"],
["WtaunuL",		"WtaunuMassiveCBPt",	"CJetVetoBVeto"],
["ttbar",		"ttbar",		"none"],
["singletop_t",		"_tchan",		"none"],
["singletop_s",		"_schan",		"none"],
["singletop_Wt",	"_Wtchan",		"none"],
["ZHvv125",		"ZH125",		"nu"],
["WH125",		"W",			"H125"],
["ZHll125",		"ZH125",		"!nu"],
]

main_HSG5_path = "/eos/atlas/atlasgroupdisk/phys-higgs/HSG5/Run2/VH/"

#############################
# code
#############################

for i_nrj in nrj :

  ana = [
  "HIGG5D1_"+i_nrj+"TeV_"+samples_tag, # 0lep
  "HIGG5D2_"+i_nrj+"TeV_"+samples_tag, # 1lep
  #"HIGG5D2MET_"+i_nrj+"TeV_"+samples_tag, # 1lepMET -> for future
  "HIGG2D4_"+i_nrj+"TeV_"+samples_tag, # 2lep
  ]

  for i_ana in ana :

    #############################
    # make dirs
    if mkdir :
      path = main_HSG5_path+i_ana+"/"
      command = "xrd eosatlas mkdir "+path
      if test : print command
      else : os.system(command)
      #
      path = main_HSG5_path+i_ana+"/CxAOD_"+production_tag+"/"
      command = "xrd eosatlas mkdir "+path
      if test : print command
      else : os.system(command)
      #
      for i_our_samples in our_samples :
        path = main_HSG5_path+i_ana+"/CxAOD_"+production_tag+"/"+i_our_samples[0]+"/"
        command = "xrd eosatlas mkdir "+path
        if test : print command
        else : os.system(command)

    #############################
    # copy to eos
    else :
      for subdir, dirs, files in os.walk(".") :
        for i_dirs in dirs :
          #print i_dirs
          # find wich ana to copy
          count = 0
          file_ana = ""
          nrj_ana = ""
          for i_char in i_ana :
            if i_char == "_" : count += 1
            if count == 0 : file_ana += i_char
            if count == 1 : nrj_ana += i_char
          #print "file_ana="+file_ana
          if i_dirs.find(file_ana) < 0 : continue
          if i_dirs.find(nrj_ana) < 0 : continue
          #
          for i_our_samples in our_samples :
            if i_dirs.find(i_our_samples[1]) < 0 : continue
            if i_our_samples[2] != "none" :
              if i_our_samples[2] == "!nu" :
                if i_dirs.find("nu") >= 0 : continue
              else : 
                if i_dirs.find(i_our_samples[2]) < 0 : continue
            path = main_HSG5_path+i_ana+"/CxAOD_"+production_tag+"/"+i_our_samples[0]+"/"
            command = "xrdcp -r "+i_dirs+" root://eosatlas/"+path+i_dirs
            if test : print command
            else : os.system(command)

print "end of script"
