#include <iostream>
#include <exception>
#include <cstdlib>
#include <cstring>

#include "funciones.hpp"
#include "cli.hpp" // Opciones por línea de comandos

using std::cout;
using std::endl;
using std::cin;

int main (int argc, char** argv) {
try {
	CLIParams params;
	
	int argObligados = parseCLI(argc, argv, params);

	// Control de errores
	if ((params.conjunto == true) && (argc-argObligados < 1)) {
		std::cout << "Número de argumentos erróneo" << std::endl;
		cout << argc-argObligados;
		mostrarUso(argv[0]);
		exit(-1);
	}
	
	Conjunto<int> c;
	int tam;
	
	bool seguir = false; // Variable de control para el flujo del programa	
	int min, max;
	do {
		
		// Está activa la opción -c
		if (params.conjunto && (seguir == false)) {
			parseConjuntoCLI(c, argc, argObligados, argv);
			tam = c.size();
		} else {
			// Permite usar un argumento para el tamaño del conjunto cuando
			// no está activa la opción -c
			if (argc > 1 && (seguir == false)) {
				tam = atoi(argv[1]);
			} else {
				cout << "Número de elementos del conjunto: ";
				cin >> tam;
			}	
			generarConjuntoEnteros(c, tam);
		}
		
		int comparaciones = obtenerMaxMin(c, min, max);
	
	
		if (obtenerSiNo("¿Desea ver el conjunto?")) {
			cout << "El conjunto es: " << endl;
			for (int x : c) {
				cout << x << " ";
			}
			cout << endl;
		}
	

		cout << "Mínimo: " << min << "  Máximo: " << max << endl;
		cout << "Número de comparaciones realizadas: " << comparaciones << endl;
	
		// Comprueba que los elementos escogidos son los correctos
		cout << "Test de validación: " 
			 << (validarMinMax(c, min, max) ? "pasa" : "falla") << endl;
		
		seguir = obtenerSiNo("¿Desea generar otro conjunto?");
		
		cout << endl;
	} while(seguir == true);
	
	if (obtenerSiNo("¿Desea grabar el último conjunto en disco?")) {
		std::string nombre;
		cout << "Introduzca el nombre: ";
		cin >> nombre;
		grabarConjunto(c, nombre, min, max);
	}
	
} catch(std::exception& e) {
	cout << "Excepción: " << e.what() << endl;
}
return 0;
}// Fin main
