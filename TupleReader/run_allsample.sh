#!/bin/bash
rm -r log_*
rm -r ZvvB
rm -r ZvvC
rm -r ZvvL
rm -r WevB
rm -r WevC
rm -r WevL
rm -r WmuvB
rm -r WmuvC
rm -r WmuvL
rm -r WtauvB
rm -r WtauvC
rm -r WtauvL
rm -r ttbarall
rm -r ttbarnon1
rm -r ttbarnon2
rm -r gamma0
rm -r gamma1
rm -r gamma2
rm -r gamma3
rm -r gamma4
rm -r gamma5
rm -r gamma6
rm -r gamma7
rm -r dijet1
rm -r dijet2
rm -r ZeeB
rm -r ZeeC
rm -r ZeeL
rm -r ZmumuB
rm -r ZmumuC
rm -r ZmumuL
rm -r ZtautauB
rm -r ZtautauC
rm -r ZtautauL
rm -r singletop_s
rm -r singletop_t
rm -r singletop_Wt
rm -r signal
nohup hsg5frameworkReadCxAOD ZvvB 1 >/dev/null 2>log_ZvvB &
#
nohup hsg5frameworkReadCxAOD ZvvC 2 >/dev/null 2> log_ZvvC &
#
nohup hsg5frameworkReadCxAOD ZvvL 3 >/dev/null 2>log_ZvvL &
#
nohup hsg5frameworkReadCxAOD WevB 4 >/dev/null 2>log_WeB & 
#
nohup hsg5frameworkReadCxAOD WevC 5 >/dev/null 2>log_WeC & 
#
nohup hsg5frameworkReadCxAOD WevL 6 >/dev/null 2>log_WeL & 
#
nohup hsg5frameworkReadCxAOD WmuvB 7 >/dev/null 2>log_WmuB &
#
nohup hsg5frameworkReadCxAOD WmuvC 8 >/dev/null 2>log_WmuC &
#
nohup hsg5frameworkReadCxAOD WmuvL 9 >/dev/null 2>log_WmuL &
#
nohup hsg5frameworkReadCxAOD WtauvB 10 >/dev/null 2>log_WtauB &
#
nohup hsg5frameworkReadCxAOD WtauvC 11 >/dev/null 2>log_WtauC &
#
nohup hsg5frameworkReadCxAOD WtauvL 12 >/dev/null 2>log_WtauL &
#
nohup hsg5frameworkReadCxAOD ttbarall 13 >/dev/null 2>log_ttall &
#
nohup hsg5frameworkReadCxAOD ttbarnon1 14 >/dev/null 2>log_ttn1 &
#
nohup hsg5frameworkReadCxAOD ttbarnon2 15 >/dev/null 2>log_ttn2 &
#
nohup hsg5frameworkReadCxAOD singletop_t 16 >/dev/null 2>log_t &
#
nohup hsg5frameworkReadCxAOD singletop_s 17 >/dev/null 2>log_s &
#
nohup hsg5frameworkReadCxAOD singletop_Wt 18 >/dev/null 2>log_Wt &
#
nohup hsg5frameworkReadCxAOD ZeeB 19 >/dev/null 2>log_ZeeB &
#
nohup hsg5frameworkReadCxAOD ZeeC 20 >/dev/null 2>log_ZeeC &
#
nohup hsg5frameworkReadCxAOD ZeeL 21 >/dev/null 2>log_ZeeL &
#
nohup hsg5frameworkReadCxAOD ZmumuB 22 >/dev/null 2>log_ZmumuB &
#
nohup hsg5frameworkReadCxAOD ZmumuC 23 >/dev/null 2>log_ZmumuC &
#
nohup hsg5frameworkReadCxAOD ZmumuL 24 >/dev/null 2>log_ZmumuL &
#
nohup hsg5frameworkReadCxAOD ZtautauB 25 >/dev/null 2>log_ZtautauB &
#
nohup hsg5frameworkReadCxAOD ZtautauC 26 >/dev/null 2>log_ZtautauC &
#
nohup hsg5frameworkReadCxAOD ZtautauL 27 >/dev/null 2>log_ZtautauL &
#
nohup hsg5frameworkReadCxAOD dijet1 28 >/dev/null 2>log_dij1 &
#
nohup hsg5frameworkReadCxAOD dijet2 29 >/dev/null 2>log_dij2 &
#
nohup hsg5frameworkReadCxAOD signal 30 >/dev/null 2>log_signal &
#
nohup hsg5frameworkReadCxAOD gamma0 31 >/dev/null 2>log_g0 &
#
nohup hsg5frameworkReadCxAOD gamma1 32 >/dev/null 2>log_g1 &
#
nohup hsg5frameworkReadCxAOD gamma2 33 >/dev/null 2>log_g2 &
#
nohup hsg5frameworkReadCxAOD gamma3 34 >/dev/null 2>log_g3 &
#
nohup hsg5frameworkReadCxAOD gamma4 35 >/dev/null 2>log_g4 &
#
nohup hsg5frameworkReadCxAOD gamma5 36 >/dev/null 2>log_g5 &
#
nohup hsg5frameworkReadCxAOD gamma6 37 >/dev/null 2>log_g6 &
#
nohup hsg5frameworkReadCxAOD gamma7 38 >/dev/null 2>log_g7 &
#
