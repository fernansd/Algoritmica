#include <iostream>
#include <vector>
#include <string>

#include "Moneda.hpp"
#include "SistemaMonetario.hpp"
#include "funciones.hpp"
#include "cli.hpp"
#include "Menu.hpp"

int main (int argc, char* argv[]) {
	using namespace std;

	CLIParams params;
	
	int argObligados = parseCLI(argc, argv, params);

	SistemaMonetario sistema;

	// Si no se pasa un sistema por consola se proporciona un por defecto
	if (params.sistema == true) {
		parseSistemaCLI(sistema, argc, argObligados, argv);	

	} else if (obtenerSiNo("¿Desea leer su sistema monetario de un fichero?")) {
			const string nombre = obtenerNombreFichero();
			leerSistemaFichero(sistema, nombre);

	} else {
		SistemaMonetario s {1,2,5,10,20,50,100,200,500,1000,2000,5000,
							10000,20000,50000};
		s.setMenorBillete(500);
		sistema = s;
	}



	if (sistema.getMenorBillete() == 0) {
		cout << "El actual sistema monetario es:" << endl;
		cout << sistema;
		fijarBillete(sistema);
	}
	cout << "\nEl sistema monetario a usar será:" << endl;
	cout << sistema << endl;

	long dinero;
	if (params.sistema == false && argc == 2) {
		int num = atoi(argv[1]);
		if (num > 0) {
			dinero = num;
		} else {
			cerr << "Error. Valor dinero incorrecto" << endl;
			mostrarUso(argv[0]);
			exit(-1);
		}
	} else {
		cout << "Dinero(centimos): ";
		cin >> dinero;
	}
	
	Solucion solucion = obtenerCambio(dinero, sistema);
	imprimirCambio(solucion);

	Menu menu_principal {
		"Nuevo sistema monetario",
		"Obtener cambio"
	};
	bool seguir = true;
	while (seguir) {
		switch(menu_principal.getOpcion()) {
			case 1:
			// Nuevo sistema
				if (obtenerSiNo("¿Desea leer su sistema monetario de un fichero?")) {
					const string nombre = obtenerNombreFichero();
					leerSistemaFichero(sistema, nombre);

				} else {
					pedirSistema(sistema);
				}
				if (sistema.getMenorBillete() == 0) {
					cout << "El actual sistema monetario es:" << endl;
					cout << sistema;
					fijarBillete(sistema);
				}
				cout << "\nEl sistema monetario a usar será:" << endl;
				cout << sistema << endl;
				break;
				
			case 2:
			// Obtener cambio
				cout << "Dinero(centimos): ";
				cin >> dinero;
				solucion = obtenerCambio(dinero, sistema);
				imprimirCambio(solucion);
				cout << endl;
				break;

			case 0:
			//Salir
				cout << "\nFin del programa." << endl;
				seguir = false;
		}
	}

	return 0;
}