#!bin/bash
cp ZvvB/hist-* Workdir_13TeV/
cp ZvvC/hist-* Workdir_13TeV/
cp ZvvL/hist-* Workdir_13TeV/
cp WevB/hist-* Workdir_13TeV/
cp WevC/hist-* Workdir_13TeV/
cp WevL/hist-* Workdir_13TeV/
cp WmuvB/hist-* Workdir_13TeV/
cp WmuvC/hist-* Workdir_13TeV/
cp WmuvL/hist-* Workdir_13TeV/
cp WtauvB/hist-* Workdir_13TeV/
cp WtauvC/hist-* Workdir_13TeV/
cp WtauvL/hist-* Workdir_13TeV/
cp ZeeB/hist-* Workdir_13TeV/
cp ZeeC/hist-* Workdir_13TeV/
cp ZeeL/hist-* Workdir_13TeV/
cp ZmumuB/hist-* Workdir_13TeV/
cp ZmumuC/hist-* Workdir_13TeV/
cp ZmumuL/hist-* Workdir_13TeV/
cp ZtautauB/hist-* Workdir_13TeV/
cp ZtautauC/hist-* Workdir_13TeV/
cp ZtautauL/hist-* Workdir_13TeV/
cp gamma0/hist-* Workdir_13TeV/
cp gamma1/hist-* Workdir_13TeV/
cp gamma2/hist-* Workdir_13TeV/
cp gamma3/hist-* Workdir_13TeV/
cp gamma4/hist-* Workdir_13TeV/
cp gamma5/hist-* Workdir_13TeV/
cp gamma6/hist-* Workdir_13TeV/
cp gamma7/hist-* Workdir_13TeV/
cp dijet1/hist-* Workdir_13TeV/
cp dijet2/hist-* Workdir_13TeV/
cp singletop_s/hist-* Workdir_13TeV/
cp singletop_t/hist-* Workdir_13TeV/
cp singletop_Wt/hist-* Workdir_13TeV/
cp signal/hist-* Workdir_13TeV/
cp ttbarall/hist-* Workdir_13TeV/
cp ttbarnon1/hist-* Workdir_13TeV/
cp ttbarnon2/hist-* Workdir_13TeV/
cd Workdir_13TeV/
rm -r hist-gamma.root
rm -r hist-Zll.root
rm -r hist-dijet.root
rm -r hist-ttbarnonall.root
rm -r hist-Zvv.root
rm -r hist-Wev.root
rm -r hist-Wtauv.root
rm -r hist-Wmuv.root
rm -r hist-singletop.root
hadd hist-gamma.root hist-gamma{0..7}.root
hadd hist-Zll.root hist-ZeeB.root hist-ZeeC.root hist-ZeeL.root hist-ZmumuB.root hist-ZmumuC.root hist-ZmumuL.root hist-ZtautauB.root hist-ZtautauC.root hist-ZtautauL.root
hadd hist-dijet.root hist-dijet1.root hist-dijet2.root
hadd hist-ttbarnonall.root hist-ttbarnonall1.root hist-ttbarnonall2.root
hadd hist-Zvv.root hist-ZvvB.root hist-ZvvC.root hist-ZvvL.root 
hadd hist-Wev.root hist-WevB.root hist-WevC.root hist-WevL.root 
hadd hist-Wmuv.root hist-WmuvB.root hist-WmuvC.root hist-WmuvL.root
hadd hist-Wtauv.root  hist-WtauvB.root hist-WtauvC.root hist-WtauvL.root 
hadd hist-singletop.root hist-singletop_s.root hist-singletop_Wt.root hist-singletop_t.root
