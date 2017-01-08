.PHONY: clean dist

PROJECT_NAME = alg_practica3

CC = g++ -std=c++11
OBJECT_FLAGS = -c -Wall -g
EXE_FLAGS = -g -Wall

MAIN = main.out

all:    $(MAIN)
	@echo  Terminado

main.out: main.cpp funciones.hpp cli.hpp
	$(CC) $(EXE_FLAGS) $^ -o $@

clean:
	$(RM) -r *.o *~ $(MAIN) log-*.txt html/

dist:
	tar zcvf $(PROJECT_NAME).tar.gz *.cpp *.hpp Makefile
