#include <iostream>
#include "funciones.hpp"
#include "Tiempo.hpp" // Clase para medir el tiempo que pasa

using std::cout;
using std::cin;
using std::endl;

int main () {
	srand(time(NULL));
	Clock reloj;
	reloj.start();
	//
	// Inicio del programa
	//
	
	cout << "Introduce el DNI: ";
	string dni;
	cin.getline(dni);
	
	// Comprueba si no es un dígito
	while (!std::isdigit(dni[7])) {
		cout << "Error de formato" << endl;
		cout << "Debe ser 8 dígitos y una letra" << endl;
		
		cout << "Introduce el DNI: ";
		cin.getline(dni);
	}
	
	int option = std::stoi(dni[7]);
	if (option % 3 == 0) {
		Matriz m1, m2;
	} else if (option % 3 == 1) {
	
	} else if (option % 3 == 2) {
	
	} else {
		cout << "Error: Fallo en la selección de opción" << endl;
	}
	
	//
	// Fin del programa
	//
	reloj.stop();
	cout << endl << "Tiempo ejecución: " << reloj.elapsed() << endl;
return 0;
}
