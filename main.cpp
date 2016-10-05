#include <iostream>
#include "funciones.hpp"
#include "Tiempo.hpp" // Clase para medir el tiempo que pasa

using std::cout;
using std::endl;

int main () {
	srand(time(NULL));

	Matriz m1 = generarMatriz(3);
	Matriz m2 = generarMatriz(3);
	
	imprimirMatriz(m1);
	cout << endl;
	imprimirMatriz(m2);
	cout << endl;
	
	Matriz producto = productoMatrices(m1, m2);
	imprimirMatriz(producto);
}
