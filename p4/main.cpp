#include <iostream>
#include <vector>
#include <string>

#include "Moneda.hpp"
#include "SistemaMonetario.hpp"
#include "funciones.hpp"
#include "cli.hpp"

int main (int argc, char* argv[]) {
	using namespace std;

	CLIParams params;
	
	int argObligados = parseCLI(argc, argv, params);

	SistemaMonetario sistema;

	// Si no se pasa un sistema por consola se proporciona un por defecto
	if (params.sistema == true) {
		parseSistemaCLI(sistema, argc, argObligados, argv);	
	} else {
		SistemaMonetario s {1,2,5,10,20,50,100,200,500,1000,2000,5000,
							10000,20000,50000};
		s.setMenorBillete(500);
		sistema = s;
	}

	if (obtenerSiNo("¿Desea leer su sistema monetario de un fichero?")) {
		const string nombre = obtenerNombreFichero();
		leerSistemaFichero(sistema, nombre);
	}

	cout << "El actual sistema monetario es:" << endl;
	cout << sistema;
	if (sistema.getMenorBillete() == 0)
		fijarBillete(sistema);
	cout << "\nEl sistema monetario a usar será:" << endl;
	cout << sistema << endl;

	int dinero;
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
	
	Cambio cambio = obtenerCambio(dinero, sistema);
	imprimirCambio(cambio, dinero);

	cout << endl;
	while (obtenerSiNo("¿Desea obtener cambio para otro valor?")) {
		cout << "Dinero(centimos): ";
		cin >> dinero;

		cambio = obtenerCambio(dinero, sistema);
		imprimirCambio(cambio, dinero);
		cout << endl;
	}

	cout << "\nFin del programa." << endl;

	return 0;
}