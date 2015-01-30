RC_CXX       = c++
RC_LD        = c++
RC_CXXFLAGS  = -I/afs/cern.ch/user/y/ychou/private/monoWZH/CxAODFramework/TupleReader/Root -I/afs/cern.ch/user/y/ychou/private/monoWZH/CxAODFramework/TupleReader -O2 -Wall -fPIC -pthread -std=c++11 -Wno-deprecated-declarations -m64 -I/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase/x86_64/root/5.34.22-x86_64-slc6-gcc48-opt/include -I/afs/cern.ch/user/y/ychou/private/monoWZH/CxAODFramework/RootCoreBin/include -g -DROOTCORE -pthread -std=c++11 -Wno-deprecated-declarations -m64 -I/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase/x86_64/root/5.34.22-x86_64-slc6-gcc48-opt/include -DROOTCORE_PACKAGE=\"TupleReader\" 
RC_DICTFLAGS = -I/afs/cern.ch/user/y/ychou/private/monoWZH/CxAODFramework/TupleReader/Root -I/afs/cern.ch/user/y/ychou/private/monoWZH/CxAODFramework/TupleReader -O2 -Wall -fPIC -pthread -std=c++11 -Wno-deprecated-declarations -m64 -I/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase/x86_64/root/5.34.22-x86_64-slc6-gcc48-opt/include -I/afs/cern.ch/user/y/ychou/private/monoWZH/CxAODFramework/RootCoreBin/include -g -DROOTCORE -pthread -std=c++11 -Wno-deprecated-declarations -m64 -I/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase/x86_64/root/5.34.22-x86_64-slc6-gcc48-opt/include -DROOTCORE_PACKAGE=\"TupleReader\" 
RC_INCFLAGS  = -I/afs/cern.ch/user/y/ychou/private/monoWZH/CxAODFramework/TupleReader/Root -I/afs/cern.ch/user/y/ychou/private/monoWZH/CxAODFramework/TupleReader -I/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase/x86_64/root/5.34.22-x86_64-slc6-gcc48-opt/include -I/afs/cern.ch/user/y/ychou/private/monoWZH/CxAODFramework/RootCoreBin/include -DROOTCORE -I/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase/x86_64/root/5.34.22-x86_64-slc6-gcc48-opt/include -DROOTCORE_PACKAGE=\"TupleReader\"
RC_LIBFLAGS  = -shared -m64 -L/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase/x86_64/root/5.34.22-x86_64-slc6-gcc48-opt/lib -lCore -lCint -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lTree -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -pthread -lm -ldl -rdynamic 
RC_BINFLAGS  = -L/afs/cern.ch/user/y/ychou/private/monoWZH/CxAODFramework/RootCoreBin/obj/x86_64-slc6-gcc48-opt/TupleReader/lib -L/afs/cern.ch/user/y/ychou/private/monoWZH/CxAODFramework/RootCoreBin/lib/x86_64-slc6-gcc48-opt -lTupleReader -lCintex -lReflex -m64 -L/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase/x86_64/root/5.34.22-x86_64-slc6-gcc48-opt/lib -lCore -lCint -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lTree -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -pthread -lm -ldl -rdynamic


all_TupleReader : dep_TupleReader package_TupleReader

package_TupleReader :  /afs/cern.ch/user/y/ychou/private/monoWZH/CxAODFramework/RootCoreBin/obj/x86_64-slc6-gcc48-opt/TupleReader/lib/libTupleReader.so postcompile_TupleReader

/afs/cern.ch/user/y/ychou/private/monoWZH/CxAODFramework/RootCoreBin/obj/x86_64-slc6-gcc48-opt/TupleReader/lib/libTupleReader.so :  /afs/cern.ch/user/y/ychou/private/monoWZH/CxAODFramework/RootCoreBin/obj/x86_64-slc6-gcc48-opt/TupleReader/obj/Tuple.o | /afs/cern.ch/user/y/ychou/private/monoWZH/CxAODFramework/RootCoreBin/obj/x86_64-slc6-gcc48-opt/TupleReader/lib
	$(SILENT)echo Linking `basename $@`
	$(SILENT)$(RC_LD) /afs/cern.ch/user/y/ychou/private/monoWZH/CxAODFramework/RootCoreBin/obj/x86_64-slc6-gcc48-opt/TupleReader/obj/Tuple.o $(RC_LIBFLAGS) -L/afs/cern.ch/user/y/ychou/private/monoWZH/CxAODFramework/RootCoreBin/lib/x86_64-slc6-gcc48-opt -o $@

/afs/cern.ch/user/y/ychou/private/monoWZH/CxAODFramework/RootCoreBin/obj/x86_64-slc6-gcc48-opt/TupleReader/obj/%.o : /afs/cern.ch/user/y/ychou/private/monoWZH/CxAODFramework/TupleReader/Root/%.cxx | /afs/cern.ch/user/y/ychou/private/monoWZH/CxAODFramework/RootCoreBin/obj/x86_64-slc6-gcc48-opt/TupleReader/obj/Tuple.d
	$(SILENT)echo Compiling `basename $@`
	$(SILENT)$(RC_CXX) $(RC_CXXFLAGS) $(INCLUDES) -c $< -o $@

/afs/cern.ch/user/y/ychou/private/monoWZH/CxAODFramework/RootCoreBin/obj/x86_64-slc6-gcc48-opt/TupleReader/obj/%.d : /afs/cern.ch/user/y/ychou/private/monoWZH/CxAODFramework/TupleReader/Root/%.cxx | /afs/cern.ch/user/y/ychou/private/monoWZH/CxAODFramework/RootCoreBin/obj/x86_64-slc6-gcc48-opt/TupleReader/obj /afs/cern.ch/user/y/ychou/private/monoWZH/CxAODFramework/RootCoreBin/obj/x86_64-slc6-gcc48-opt/TupleReader/obj
	$(SILENT)echo Making dependency for `basename $<`
	$(SILENT)rc --internal make_dep $(RC_CXX) $(RC_CXXFLAGS) $(INCLUDES)  -- $@ $< 

/afs/cern.ch/user/y/ychou/private/monoWZH/CxAODFramework/RootCoreBin/obj/x86_64-slc6-gcc48-opt/TupleReader/obj : 
	$(SILENT)echo Making directory $@
	$(SILENT)mkdir -p $@

/afs/cern.ch/user/y/ychou/private/monoWZH/CxAODFramework/RootCoreBin/obj/x86_64-slc6-gcc48-opt/TupleReader/lib : 
	$(SILENT)echo Making directory $@
	$(SILENT)mkdir -p $@

postcompile_TupleReader :  /afs/cern.ch/user/y/ychou/private/monoWZH/CxAODFramework/RootCoreBin/obj/x86_64-slc6-gcc48-opt/TupleReader/lib/libTupleReader.so
	$(SILENT)rc --internal postcompile_pkg TupleReader


dep_TupleReader : /afs/cern.ch/user/y/ychou/private/monoWZH/CxAODFramework/RootCoreBin/obj/x86_64-slc6-gcc48-opt/TupleReader/obj/Tuple.d


-include  /afs/cern.ch/user/y/ychou/private/monoWZH/CxAODFramework/RootCoreBin/obj/x86_64-slc6-gcc48-opt/TupleReader/obj/Tuple.d
