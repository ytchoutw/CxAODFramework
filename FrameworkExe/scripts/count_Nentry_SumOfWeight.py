#!/usr/bin/python

import os, math, sys, ROOT
ROOT.gROOT.SetBatch(True)

ana = "0lep"

nrj = [
#"8TeV",
"13TeV",
]

#user = "user.djamin"
user = "group.phys-higgs"

ini_count = 0

count_8 = [
# ["167740",ini_count,ini_count], 
# ["167741",ini_count,ini_count],
# ["167742",ini_count,ini_count],
# ["167743",ini_count,ini_count],
# ["167744",ini_count,ini_count],
# ["167745",ini_count,ini_count],
# ["167746",ini_count,ini_count],
# ["167747",ini_count,ini_count],
# ["167748",ini_count,ini_count],
#["167749",ini_count,ini_count],
#["167750",ini_count,ini_count],
#["167751",ini_count,ini_count],
#["167752",ini_count,ini_count],
#["167753",ini_count,ini_count],
#["167754",ini_count,ini_count],
#["167755",ini_count,ini_count],
#["167756",ini_count,ini_count],
#["167757",ini_count,ini_count],
# ["167758",ini_count,ini_count],
# ["167759",ini_count,ini_count],
# ["167760",ini_count,ini_count],
#["110119",ini_count,ini_count],
#["110140",ini_count,ini_count],
#["110101",ini_count,ini_count],
# ["117050",ini_count,ini_count],
#["189340",ini_count,ini_count],
#["189341",ini_count,ini_count],
#["189342",ini_count,ini_count],
# ["189343",ini_count,ini_count],
# ["189344",ini_count,ini_count],
# ["189345",ini_count,ini_count],
#["189420",ini_count,ini_count],
#["189421",ini_count,ini_count],
#["189422",ini_count,ini_count],
#["189423",ini_count,ini_count],
#["189424",ini_count,ini_count],
#["189425",ini_count,ini_count],
#["189426",ini_count,ini_count],
#["189427",ini_count,ini_count],
#["189428",ini_count,ini_count],
#["189429",ini_count,ini_count],
#["189430",ini_count,ini_count],
#["189431",ini_count,ini_count],
]

count_13 = [
["203883",ini_count,ini_count],
# ["167740",ini_count,ini_count], 
# ["167741",ini_count,ini_count],
# ["167742",ini_count,ini_count],
# ["180534",ini_count,ini_count],
# ["180535",ini_count,ini_count],
# ["180536",ini_count,ini_count],
# ["167761",ini_count,ini_count],
# ["167762",ini_count,ini_count],
# ["167763",ini_count,ini_count],
# ["167770",ini_count,ini_count],
# ["167771",ini_count,ini_count],
# ["167772",ini_count,ini_count],
# ["167779",ini_count,ini_count],
# ["167780",ini_count,ini_count],
# ["167781",ini_count,ini_count],
# ["167788",ini_count,ini_count],
# ["167789",ini_count,ini_count],
# ["167790",ini_count,ini_count],
# ["167743",ini_count,ini_count],
# ["167744",ini_count,ini_count],
# ["167745",ini_count,ini_count],
# ["180537",ini_count,ini_count],
# ["180538",ini_count,ini_count],
# ["180539",ini_count,ini_count],
# ["167764",ini_count,ini_count],
# ["167765",ini_count,ini_count],
# ["167766",ini_count,ini_count],
# ["167773",ini_count,ini_count],
# ["167774",ini_count,ini_count],
# ["167775",ini_count,ini_count],
# ["167782",ini_count,ini_count],
# ["167783",ini_count,ini_count],
# ["167784",ini_count,ini_count],
# ["167791",ini_count,ini_count],
# ["167792",ini_count,ini_count],
# ["167793",ini_count,ini_count],
# ["167746",ini_count,ini_count],
# ["167747",ini_count,ini_count],
# ["167748",ini_count,ini_count],
# ["180540",ini_count,ini_count],
# ["180541",ini_count,ini_count],
# ["180542",ini_count,ini_count],
# ["167767",ini_count,ini_count],
# ["167768",ini_count,ini_count],
# ["167769",ini_count,ini_count],
# ["167776",ini_count,ini_count],
# ["167777",ini_count,ini_count],
# ["167778",ini_count,ini_count],
# ["167785",ini_count,ini_count],
# ["167786",ini_count,ini_count],
# ["167787",ini_count,ini_count],
# ["167794",ini_count,ini_count],
# ["167795",ini_count,ini_count],
# ["167796",ini_count,ini_count],
# ["167749",ini_count,ini_count],
# ["167750",ini_count,ini_count],
# ["167751",ini_count,ini_count],
# ["167797",ini_count,ini_count],
# ["167798",ini_count,ini_count],
# ["167799",ini_count,ini_count],
# ["167809",ini_count,ini_count],
# ["167810",ini_count,ini_count],
# ["167811",ini_count,ini_count],
# ["167821",ini_count,ini_count],
# ["167822",ini_count,ini_count],
# ["167823",ini_count,ini_count],
# ["167833",ini_count,ini_count],
# ["167834",ini_count,ini_count],
# ["167835",ini_count,ini_count],
# ["167752",ini_count,ini_count],
# ["167753",ini_count,ini_count],
# ["167754",ini_count,ini_count],
# ["167800",ini_count,ini_count],
# ["167801",ini_count,ini_count],
# ["167802",ini_count,ini_count],
# ["167812",ini_count,ini_count],
# ["167813",ini_count,ini_count],
# ["167814",ini_count,ini_count],
# ["167824",ini_count,ini_count],
# ["167825",ini_count,ini_count],
# ["167826",ini_count,ini_count],
# ["167836",ini_count,ini_count],
# ["167837",ini_count,ini_count],
# ["167838",ini_count,ini_count],
# ["167755",ini_count,ini_count],
# ["167756",ini_count,ini_count],
# ["167757",ini_count,ini_count],
# ["167803",ini_count,ini_count],
# ["167804",ini_count,ini_count],
# ["167805",ini_count,ini_count],
# ["167815",ini_count,ini_count],
# ["167816",ini_count,ini_count],
# ["167817",ini_count,ini_count],
# ["167827",ini_count,ini_count],
# ["167828",ini_count,ini_count],
# ["167829",ini_count,ini_count],
# ["167839",ini_count,ini_count],
# ["167840",ini_count,ini_count],
# ["167841",ini_count,ini_count],
# ["167758",ini_count,ini_count],
# ["167759",ini_count,ini_count],
# ["167760",ini_count,ini_count],
# ["167806",ini_count,ini_count],
# ["167807",ini_count,ini_count],
# ["167808",ini_count,ini_count],
# ["167818",ini_count,ini_count],
# ["167819",ini_count,ini_count],
# ["167820",ini_count,ini_count],
# ["167830",ini_count,ini_count],
# ["167831",ini_count,ini_count],
# ["167832",ini_count,ini_count],
# ["167842",ini_count,ini_count],
# ["167843",ini_count,ini_count],
# ["167844",ini_count,ini_count],
# ["110351",ini_count,ini_count],
# ["110401",ini_count,ini_count],
# ["110302",ini_count,ini_count],
# ["110070",ini_count,ini_count],
# ["110071",ini_count,ini_count],
# ["110305",ini_count,ini_count],
# ["161805",ini_count,ini_count],
# ["161849",ini_count,ini_count],
#["161827",ini_count,ini_count],
]

# count
for subdir, dirs, files in os.walk(".") :
  for file in files :
    if file.find(user) >= 0 :
      my_file = os.path.join(subdir, file)
      #print my_file
      #
      f = ROOT.TFile.Open(my_file,"read")
      h = f.Get("MetaData_EventCount")
      n_entries = h.GetBinContent(7)
      n_sum = h.GetBinContent(8)
      #print str(subdir)+" -> "+str(n_entries)
      #
      for i_nrj in nrj :
        if i_nrj == "8TeV"  : count = count_8
        if i_nrj == "13TeV" : count = count_13
        #
        if my_file.find(i_nrj) < 0 : continue
        if my_file.find("_outputLabel.root") < 0 : continue
        for i_count in count :
          if my_file.find(i_count[0]) >= 0 :
            i_count[1] += n_entries
            i_count[2] += n_sum
            #if my_file.find(i_count[0]) >= 0 : print "good file -> "+my_file
      f.Close()

# write
for i_nrj in nrj :
  # pick the good table
  if i_nrj == "8TeV"  : count = count_8
  if i_nrj == "13TeV" : count = count_13
  # define file
  out_file = open('./yields.'+ana+'.'+i_nrj+'.txt', 'w')
  # write
  for i_count in count :
    #print str(i_nrj)+" -> "+i_count[0]+" = "+str(i_count[1])+" "+str(i_count[2])
    out_file.write(str(i_count[0])+"\t\t"+str(i_count[1])+"\t\t"+str(i_count[2])+"\n")
  out_file.close()
