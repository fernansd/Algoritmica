#ifndef FUNCIONES_HPP
#define FUNCIONES_HPP

#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::cin;
using std::endl;

typedef std::vector<std::vector<int>> Tabla;
typedef std::vector<int> Fila;

// Menú
int menu();

// Opción 1: combinatorio
int combinatorio(int n, int k);
int combinatorioTabla(int n, int k, Tabla& t);
int combinatorioIterativo(int n, int k);

// Opción 2: Hanoi
int hanoi(int n);

#endif
