#ifndef CLASE_MENU_HPP
#define CLASE_MENU_HPP

#include <vector>
#include <string>
#include <iostream>
#include <exception>
#include <limits>

class Menu {
public:
	Menu()
	{
		opciones.insert(std::begin(opciones), opt_salida);
	}

	Menu(std::vector<std::string> opt)
	{
		opciones = opt;
		opciones.insert(std::begin(opciones), opt_salida);
	}

	Menu(std::initializer_list<std::string> list)
		: opciones(list)
	{
		opciones.insert(std::begin(opciones), opt_salida);
	}

	int getOpcion() {
		using namespace std;
		cout << endl;
		cout << "Elegir opcion:\n";
		for (size_t i = 0; i < opciones.size(); i++) {
			cout << "\t" << i << ") " << opciones[i] << "\n";
		}
		cout << "> ";

		int opcion = -1;
		while (opcion == -1) {

			if (!(cin >> opcion)) {
				cerr << "Error. Solo se aceptan números" << endl;
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				opcion = -1;
				// También muestra el mensaje de error de abajo
			}

			if (opcion < 0 || opcion > (int)opciones.size()-1) {
				cerr << "El número debe ser una de las opciones" << endl;
				opcion = -1;
				cout << "> "; // Pide nuevo número
			}
			
		}
		cout << endl;
		return opcion;
	}
	
	// Permite decidir si hay o no opción de salida
	void optSalida(bool opt)
	{
		if (opt) {
			if (opciones[0] !=	opt_salida) {
				opciones.insert(std::begin(opciones), opt_salida);
			}
		} else if (opciones[0] == opt_salida) {
			opciones.erase(std::begin(opciones));
		}
	}
private:
	std::vector<std::string> opciones;
	// Opción de configuración de la clase, texto para opción salida
	const std::string opt_salida = "Salir";
};

#endif
