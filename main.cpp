#include <iostream>
#include "funciones.hpp"
#include "Tiempo.hpp" // Clase para medir el tiempo que pasa

using std::cout;
using std::endl;

int main () {
	srand(time(NULL));
	Clock reloj;
	reloj.start();

	Matriz m1 = generarMatriz(3);
	Matriz m2 = generarMatriz(3);
	
	cout << "Matriz 1:" << endl;
	imprimirMatriz(m1);
	cout << endl;

	cout << "Matriz 2:" << endl;
	imprimirMatriz(m2);
	cout << endl;
	
	cout << "Matriz producto M1xM2:" << endl;
	Matriz producto = productoMatrices(m1, m2);
	imprimirMatriz(producto);

	cout << "Determinante matriz de m1: "
		<< determinanteMatriz(m1) << endl;

	cout << "Determinante matriz de m2: "
		<< determinanteMatriz(m2) << endl;

	Matriz inv1 = invertirMatriz(m1);
	Matriz inv2 = invertirMatriz(m2);

	cout << "Inversa m1:" << endl;
	imprimirMatriz(inv1);


	cout << "Inversa m2:" << endl;
	imprimirMatriz(inv2);

	reloj.stop();
	cout << "Tiempo pasado: " << reloj.elapsed() << endl;

	int n = 2000000;
	reloj.restart();
	for (int i = 0; i < n; i++) {
		m1 = generarMatriz(3);
		m2 = generarMatriz(3);

		cout << "Matriz 1:" << endl;
		imprimirMatriz(m1);
		cout << endl;

		cout << "Matriz 2:" << endl;
		imprimirMatriz(m2);
		cout << endl;

		producto = matrizVacia(3,3);
		
		producto = productoMatrices(m1, m2);

		double det1 = determinanteMatriz(m1);

		double det2 = determinanteMatriz(m2);

		inv1 = invertirMatriz(m1);
		inv2 = invertirMatriz(m2);
	}
	reloj.stop();

	cout << "Tiempo pasado para n=" << n << " :  " << reloj.elapsed() << endl;


return 0;
}
