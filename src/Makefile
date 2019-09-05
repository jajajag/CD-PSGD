CXX=g++
CXXFLAGS=""

main: main.o data_manager.o
	$(CXX) $(CXXFLAGS) -o main main.o data_manager.o

data_manager.o: data_manager.hpp data_manager.cpp
	$(CXX) $(CXXFLAGS) -c data_manager.cpp

main.o: data_manager.hpp main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

clean:
	-rm *.o
	mv main	../
