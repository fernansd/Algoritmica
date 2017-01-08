#ifndef FUNCIONES_HPP
#define FUNCIONES_HPP

#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::cin;
using std::endl;

typedef std::vector<std::vector<long>> Tabla;
typedef std::vector<long> Fila;

// Menú
int menu();

// Algoritmos de números combinatorios
long combinatorioRecursivo(int n, int k);
long combinatorioTabla(int n, int k, Tabla& t);
long combinatorioIterativo(int n, int k);

// Opción 2: Hanoi
int hanoi(int n);

#endif
