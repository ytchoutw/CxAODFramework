#!/bin/bash
rm -r Zvv
rm -r Wev
rm -r Wmuv
rm -r Wtauv
rm -r ttbarall
rm -r ttbarnon
rm -r ttbarnon1
rm -r gamma1
rm -r gamma2
rm -r gamma3
rm -r gamma4
rm -r gamma5
rm -r gamma6
rm -r gamma7
rm -r dijet
rm -r dijet1
rm -r Zee
rm -r Zmumu
rm -r Ztautau
rm -r singletop
rm -r signal
nohup hsg5frameworkReadCxAOD Zvv 1 &
nohup hsg5frameworkReadCxAOD Wev 2 &
nohup hsg5frameworkReadCxAOD Wmuv 3 &
nohup hsg5frameworkReadCxAOD Wtauv 4 &
nohup hsg5frameworkReadCxAOD ttbarall 5 &
nohup hsg5frameworkReadCxAOD ttbarnon1 6 &
nohup hsg5frameworkReadCxAOD ttbarnon2 7 &
nohup hsg5frameworkReadCxAOD dijet1 8 &
nohup hsg5frameworkReadCxAOD dijet2 9 &
nohup hsg5frameworkReadCxAOD singletop 10 &
nohup hsg5frameworkReadCxAOD signal 11 &
nohup hsg5frameworkReadCxAOD gamma1 12 &
nohup hsg5frameworkReadCxAOD gamma2 13 &
nohup hsg5frameworkReadCxAOD gamma3 14 &
nohup hsg5frameworkReadCxAOD gamma4 15 &
nohup hsg5frameworkReadCxAOD gamma5 16 &
nohup hsg5frameworkReadCxAOD gamma6 17 &
nohup hsg5frameworkReadCxAOD gamma7 18 &
nohup hsg5frameworkReadCxAOD Zee 19 &
nohup hsg5frameworkReadCxAOD Zmumu 20 &
nohup hsg5frameworkReadCxAOD Ztautau 21 &