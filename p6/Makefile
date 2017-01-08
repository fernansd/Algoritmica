.PHONY: clean dist

ARCHIVE_NAME = p6_SanchezDelgado

CC = g++ -std=c++11
OBJECT_FLAGS = -c -Wall -g
EXE_FLAGS = -g -Wall

MAIN = main.out

all:    $(MAIN)
	@echo  Terminado

main.out: main.cpp Conjunto.hpp Solucion.hpp funciones.hpp Menu.hpp cli.hpp
	$(CC) $(EXE_FLAGS) $^ -o $@

clean:
	$(RM) -r *.o *~ $(MAIN) log-*.txt html/

dist:
	cp *.cpp *.hpp Makefile $(ARCHIVE_NAME)
	tar zcvf $(ARCHIVE_NAME).tar.gz $(ARCHIVE_NAME)
