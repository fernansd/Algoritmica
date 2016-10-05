.PHONY: clean dist

PROJECT_NAME = alg_practica1

CC = g++ -std=c++11
OBJECT_FLAGS = -c -Wall -g
EXE_FLAGS = -g -Wall

MAIN = Tiempo.o main.out

all:    $(MAIN)
	@echo  Terminado

Tiempo.o: Tiempo.hpp
	$(CC) $(OBJECT_FLAGS) $<  -o $@

main.out: main.cpp funciones.cpp funciones.hpp Tiempo.hpp
	$(CC) $(EXE_FLAGS) $^ -o $@

clean:
	$(RM) -r *.o *~ $(MAIN) log-*.txt html/

dist:
	tar zcvf $(PROJECT_NAME).tar.gz *.cpp *.hpp Makefile Doxyfile
