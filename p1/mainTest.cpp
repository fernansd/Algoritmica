#include <iostream>

#include "funciones.hpp"

using namespace std;

int main () {

	Matriz m1 = generarMatriz(3);
	Matriz m2 = generarMatriz(3);
	
	cout << "M1:" << endl;
	imprimirMatriz(m1);
	
	cout << "M2:" << endl;
	imprimirMatriz(m2);
	
	Matriz producto = productoMatrices(m1, m2);
	cout << "M1 x M2:" << endl;
	imprimirMatriz(producto);
	

return 0;
}
