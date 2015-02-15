#CxAODFramework
This code are based on HSG5 team CxAODFramework tag 00-00-06.
Modified for monoWZH run II search 

#Using CxAODReader
##Quick start
    setupATLAS
    localSetupDQ2Client --skipConfirm # just for dq2-get -> no need for job submission 
    voms-proxy-init -voms atlas   
    localSetupDQ2Wrappers
    localSetupPandaClient --noAthenaCheck
    cd CxAODFramework/
##Setup RootCore
    rcSetup Base,2.0.22
##Modified following files before compile it.
1. CxAODFramework/FrameworkExe/util/hsg5frameworkReadCxAOD.cxx
    Line:51-56 dataset you want to run <br/>
    Line:89 std::string afsdir("/phys/groups/tev/scratch3/users/ytchou/monoWZ/Dataset_CxAOD/"); <br/>
Location of your CxAOD dataset.It should have the structure like .../$YOURDATASET/top/user.xxxx.
2. Using the script in FrameworEXE/script/count_Nentry _SumOfWeight.py in $YOURDATASET to get Sumofweight    
  txt(yield.0lep.8/13TeV.txt).Move this txt to CxAODTool/data/. It'll help us normalied the event.

##Complie code
    rc find_packages
    rc compile

##Run Analysis
    hsg5frameworkReadCxAOD output_dir

##Useful Links
###CxAODFrameWork  <br/>
Development https://twiki.cern.ch/twiki/bin/view/AtlasProtected/CxAODFrameworkDevelopment <br/>
Tutorial https://twiki.cern.ch/twiki/bin/view/AtlasProtected/CxAODFrameworkTutorial

