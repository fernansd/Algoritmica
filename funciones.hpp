#ifndef FUNCIONES_HPP
#define FUNCIONES_HPP

#include <vector>

typedef std::vector<std::vector<double>> Matriz;
typedef std::vector<double> Fila;

Matriz generarMatriz(int tam);

Matriz matrizVacia(int fil, int col);

void imprimirMatriz(Matriz &m);

Matriz productoMatrices(Matriz &m1, Matriz &m2);

int determinanteMatriz(Matriz &m);

Matriz invertirMatriz(Matriz &m);

double generarFibonacci(int n);

#endif
