#ifndef CLASE_MENU_HPP
#define CLASE_MENU_HPP

#include <vector>
#include <string>
#include <iostream>
#include <exception>
#include <limits>

namespace cli {

class Menu {
public:
	Menu()
	{
		opciones.insert(std::begin(opciones), "Salir");
	}

	Menu(std::vector<std::string> opt)
	{
		opciones = opt;
		opciones.insert(std::begin(opciones), "Salir");
	}

	Menu(std::initializer_list<std::string> list)
		: opciones(list)
	{
		opciones.insert(std::begin(opciones), "Salir");
	}

	int getOpcion() {
		using namespace std;
		for (size_t i = 0; i < opciones.size(); i++) {
			cout << i << ") " << opciones[i] << "\n";
		}

		int opcion = -1;
		while (opcion == -1) {
			cout << endl << "> ";

			if (!(cin >> opcion)) {
				cerr << "Error. Solo se aceptan números" << endl;
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				opcion = -1;
			}

			if (opcion < 0 || opcion > (int)opciones.size()-1) {
				cerr << "El número debe ser una de las opciones" << endl;
				opcion = -1;
			}
			
		}

		return opcion;
	}
private:
	std::vector<std::string> opciones;
};

} // Fin namespace cli

#endif