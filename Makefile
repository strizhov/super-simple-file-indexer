PROG = ssfi

CXX = g++
EXEC = ssfi
CXXFLAGS = -g -O2 -Wfatal-errors -Wshadow -Wall -std=c++11 -lstdc++ -L/usr/local/lib -I/usr/include/boost
LDFLAGS = -lboost_system -lboost_filesystem -lboost_program_options -lboost_thread 

all:
	$(MAKE) -C src

clean:
	$(MAKE) clean -C src
