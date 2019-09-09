MPICXX=mpicxx
CXX=g++
CXXFLAGS=-std=c++11

main: main.o data_manager.o ecd_sgd.o
	$(MPICXX) $(CXXFLAGS) -o main main.o data_manager.o ecd_sgd.o

data_manager.o: data_manager.hpp data_manager.cpp
	$(CXX) $(CXXFLAGS) -c data_manager.cpp

ecd_sgd.o: ecd_sgd.hpp ecd_sgd.cpp data_manager.hpp
	$(MPICXX) $(CXXFLAGS) -c ecd_sgd.cpp

main.o: data_manager.hpp ecd_sgd.hpp main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

clean:
	-rm *.o
	mv main	../
