MPICXX=mpicxx
CXX=g++
CXXFLAGS=-std=c++11

main: main.o data_manager.o dcd_psgd.o ecd_psgd.o
	$(MPICXX) $(CXXFLAGS) -o main main.o data_manager.o dcd_psgd.o ecd_psgd.o

data_manager.o: data_manager.hpp data_manager.cpp
	$(CXX) $(CXXFLAGS) -c data_manager.cpp

ecd_psgd.o: ecd_psgd.hpp ecd_psgd.cpp data_manager.hpp
	$(MPICXX) $(CXXFLAGS) -c ecd_psgd.cpp

dcd_psgd.o: dcd_psgd.hpp dcd_psgd.cpp data_manager.hpp
	$(MPICXX) $(CXXFLAGS) -c dcd_psgd.cpp

main.o: data_manager.hpp dcd_psgd.hpp ecd_psgd.hpp main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

clean:
	-rm *.o
	mv main	../
