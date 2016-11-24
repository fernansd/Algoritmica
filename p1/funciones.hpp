#ifndef FUNCIONES_HPP
#define FUNCIONES_HPP

#include <vector>
#include <cmath>

typedef std::vector<std::vector<double>> Matriz;
typedef std::vector<double> Fila;

struct Tiempos {
	int tam;
	double real;
	double est;
};

double sumatorio(std::vector<double>& v, double exponente);

Tiempos sumatorioTiempos(std::vector<Tiempos>& v, double exponente);

Matriz generarMatriz(int tam);

Matriz matrizVacia(int fil, int col);

void imprimirMatriz(Matriz &m);

Matriz productoMatrices(Matriz &m1, Matriz &m2);

int generarFibonacci(int n);

// Otras operaciones matriciales
long double determinanteMatriz(Matriz &m);
Matriz invertirMatriz(Matriz &m);



#endif
