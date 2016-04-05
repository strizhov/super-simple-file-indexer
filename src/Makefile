CXX = g++
PROG = ssfi

CXXFLAGS = -g -O2 -Wfatal-errors -Wshadow -Wall -std=c++11 -lstdc++ -L/usr/local/lib -I/usr/include/boost
LDFLAGS = -lboost_system -lboost_filesystem -lboost_program_options -lboost_thread 

OBJECTDIR = ../obj
BINDIR = ../bin

all: $(PROG)

clean:
	rm -f $(PROG) $(OBJECTS)

OBJECTS = $(OBJECTDIR)/FileFinder.o \
	  $(OBJECTDIR)/SSFI.o \
          $(OBJECTDIR)/SSFIManager.o \
          $(OBJECTDIR)/ThreadManager.o \
	  $(OBJECTDIR)/WordCount.o 

$(PROG): $(OBJECTS) 
	$(CXX) $(CXXFLAGS) $(OBJECTS) $(LDFLAGS) -o $(BINDIR)/$(PROG)

$(OBJECTDIR)/FileFinder.o: FileFinder.cpp
	$(CXX) $(CXXFLAGS) -c FileFinder.cpp -o $(OBJECTDIR)/FileFinder.o

$(OBJECTDIR)/SSFI.o: SSFI.cpp
	$(CXX) $(CXXFLAGS) -c SSFI.cpp -o $(OBJECTDIR)/SSFI.o

$(OBJECTDIR)/SSFIManager.o: SSFIManager.cpp
	$(CXX) $(CXXFLAGS) -c SSFIManager.cpp -o $(OBJECTDIR)/SSFIManager.o

$(OBJECTDIR)/ThreadManager.o: ThreadManager.cpp
	$(CXX) $(CXXFLAGS) -c ThreadManager.cpp -o $(OBJECTDIR)/ThreadManager.o

$(OBJECTDIR)/WordCount.o: WordCount.cpp
	$(CXX) $(CXXFLAGS) -c WordCount.cpp -o $(OBJECTDIR)/WordCount.o

