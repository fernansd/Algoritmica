#include <iostream>
#include <string>

#include "Menu.hpp"
#include "cli.hpp"
#include "Conjunto.hpp"
#include "Solucion.hpp"
#include "funciones.hpp"

int main (int argc, char* argv[])
{
	cli::CLIParams cli_opt;
	int argObligados = cli::parseCLI(argc, argv, cli_opt);

	//
	// Variables generales para el programa
	Conjunto<int> conjunto;
	VectorSolucion<int> soluciones;
	int suma = 0;

	if (cli_opt.conjunto == true) {
		cli::parseConjuntoCLI(conjunto, argc, argObligados, argv);

	} else if (obtenerSiNo("¿Desea leer el conjunto de un fichero?")) {
		const std::string nombre = obtenerNombreFichero();
		leerConjuntoFichero(conjunto, nombre);

	} else {
		// Conjunto por defecto
		Conjunto<int> aux {5, 10, 12, 13, 15, 18};
		conjunto = aux;
	}

	std::cout << "\nEl conjunto a usar será:" << std::endl;
	std::cout << conjunto << std::endl;

	if (cli_opt.conjunto == false && argc == 2) {
		int aux = atoi(argv[1]);
		if (aux > 0) {
			suma = aux;
		} else {
			std::cerr << "Error. Valor suma incorrecto" << std::endl;
			cli::mostrarUso(argv[0]);
			exit(-1);
		}
	} else {
		suma = pedirSumaObjetivo("Suma(entero): ");
	}


	soluciones = conjunto.obtenerConjuntoSuma(suma);
	imprimirSolucion(soluciones, conjunto);


	cli::Menu menu_principal {
		"Nuevo conjunto",
		"Nueva suma objetivo",
		"Ver solución de nuevo"
	};

	bool seguir = true;
	while (seguir) {
		switch (menu_principal.getOpcion()) {
			case 1:
			// Nuevo conjunto
				if (obtenerSiNo("¿Desea leer su conjunto de un fichero?")) {
					const std::string nombre = obtenerNombreFichero();
					leerConjuntoFichero(conjunto, nombre);

				} else {
					pedirConjunto(conjunto);
				}
				std::cout << "\nEl conjunto a usar será:" << std::endl;
				std::cout << conjunto << std::endl;
				break;

			case 2:
			// Cambiar suma objetivo
				suma = pedirSumaObjetivo("Suma(entero): ");
				soluciones = conjunto.obtenerConjuntoSuma(suma);
				imprimirSolucion(soluciones, conjunto);
				break;

			case 3:
				imprimirSolucion(soluciones, conjunto);
				break;

			case 0:
			// Salir
				std::cout << "\nFin del programa" << std::endl;
				seguir = false;
		}
	}

return 0;
}