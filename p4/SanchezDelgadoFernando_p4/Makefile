.PHONY: clean dist

ARCHIVE_NAME = p4_SanchezDelgado.tar.gz

CC = g++ -std=c++11
OBJECT_FLAGS = -c -Wall -g
EXE_FLAGS = -g -Wall

MAIN = main.out

all:    $(MAIN)
	@echo  Terminado

main.out: main.cpp Moneda.o SistemaMonetario.o funciones.o
	$(CC) $(EXE_FLAGS) $^ -o $@

funciones.o: funciones.cpp funciones.hpp
	$(CC) $(OBJECT_FLAGS) $<

Moneda.o: Moneda.cpp Moneda.hpp
	$(CC) $(OBJECT_FLAGS) $<

SistemaMonetario.o: SistemaMonetario.cpp SistemaMonetario.hpp Moneda.o
	$(CC) $(OBJECT_FLAGS) $<

clean:
	$(RM) -r *.o *~ $(MAIN) log-*.txt html/

dist:
	cp *.cpp *.hpp Makefile $(ARCHIVE_NAME)
	tar zcvf $(ARCHIVE_NAME).tar.gz $(ARCHIVE_NAME)
