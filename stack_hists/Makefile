SRC := $(wildcard *.cpp)
OBJ := $(SRC:.cpp=.o)
CFLAGS := -O3
LDFLAGS= -L$(DELPHESPATH) -lDelphes
INCLUDES =  -I$(DELPHESPATH)
ROOTCFLAGS := $(shell root-config --cflags)
ROOTGLIBS := $(shell root-config --glibs)

%.o:%.cpp
	g++ -c -o $@ $< $(CFLAGS) $(INCLUDES) $(ROOTCFLAGS)

stack_hists: $(OBJ)
	g++ $(OBJ) $(CFLAGS) $(LDFLAGS) $(ROOTGLIBS) -o stack_hists

clean:
	rm -rf *.o stack_hists
