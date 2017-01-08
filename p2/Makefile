CXX = g++ -std=c++11
FLAGS = -g -Wall
OBJ_FLAGS = -c

all: main.out

main.out: main.cpp funciones.o
	$(CXX) $(FLAGS) $^	-o $@

funciones.o: funciones.cpp funciones.hpp
	$(CXX) $(FLAGS) $(OBJ_FLAGS) $<	-o $@
	
clean:
	$(RM) *.o *.out
