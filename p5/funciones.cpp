#include "funciones.hpp"

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <limits>



Solucion obtenerCambio(long dinero, SistemaMonetario& v) {
	Cambio cambio;

	std::vector<std::vector<long>> c(v.size(), std::vector<long>(dinero+1));

	for (size_t i = 0; i < v.size(); i++) {
		c[i][0] = 0;
	}

	// La variable i es un pivote para recorrer las monedas disponibles
	for (size_t i = 0; i < c.size(); i++) {
		// La variable j es un pivote que contiene el dinero que falta por cambiar
		for (size_t j = 0; j < c[i].size(); j++)  {
			
			if (i == 0 && j < v[i]) {
				c[i][j] = std::numeric_limits<long>::infinity();

			} else {
				if (i == 0) {
					c[i][j] = 1 + c[i][j-v[0].getValor()];
				
				} else {
					// La moneda seleccionada es ḿas grande que el dinero actual
					if (j < v[i]) {
						c[i][j] = c[i-1][j];
					
					} else {
						c[i][j] = std::min(c[i-1][j], 1 + c[i][j-v[i].getValor()]);
					}
				}
			}
		}
	}

	// Ahora obtenemos la cantidad de cada moneda necesaria desde la tabla
	int i = v.size()-1;
	int j = c[0].size()-1;
	
	// Cuando j = 0, el valor de las monedas cogidas iguala el del dinero objetivo
	while (j > 0) {
		if (i == 0) {
			if (cambio.back().moneda != v[i]) {
				cambio.push_back(Cantidad(v[i].getValor(), 1));

			} else {
				cambio.back().cantidad++;
			}
			// Resta el valor de la moneda cogida al dinero que falta por cambiar
			j = j - v[i].getValor();

		} else if (c[i][j] == c[i-1][j]) {
			i--;

		} else {
			if (cambio.size() == 0 || cambio.back().moneda != v[i]) {
				cambio.push_back(Cantidad(v[i].getValor(), 1));

			} else {
				cambio.back().cantidad++;
			}
			j = j - v[i].getValor();
		}
	}

	return Solucion(dinero, cambio, v);
}

//
// FUNCIONES AUXILIARES

std::string obtenerNombreFichero()
{
	std::cout << "0 cancela la introducción\n";

	std::string nombre;
	while (true) {
		std::cout << "Nombre fichero: ";
		std::cin >> nombre;

		if (nombre == "0")
			return "";

		std::ifstream archivo(nombre);

		if (archivo.is_open()) {
			break;
		} else {
			std::cerr << "Error. El archivo no existe." << std::endl;
		}
	}
	std::cout << std::endl;

	return nombre;
}

void leerSistemaFichero(SistemaMonetario& s, const std::string& nombre)
{
	// El formato del fichero es número de billete en la primera línea
	// Y luego un valor monetario en el resto de líneas, sin líneas vacías
	std::ifstream archivo(nombre);
	int valor, billete;
	s.clear();

	archivo >> billete;
	while (archivo >> valor) {
		s.push(valor);
	}
	if (!s.exists(billete)) {
		std::cerr << "Error de formato. El billete leído no se encuentra"
					 " entre los valores monetarios" << std::endl;
		exit(-1);
	} else {
		s.setMenorBillete(billete);
	}
}

void pedirSistema(SistemaMonetario& s)
{
	s.limpiar();

	using namespace std;
	cout << "Introducir 0 para parar" << endl;

	int elem = -1;
	while (elem != 0) {
		cout << "> "; // Pide número
		if (!(cin >> elem)) {
			cerr << "Error. Solo se aceptan números" << endl;
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			elem = -1;
			// También muestra el mensaje de error de abajo
		}

		if (elem == 0) continue;

		if (elem < 0) {
			cerr << "El número debe ser positivo" << endl;
			elem = -1;
		} else {
			s.push(Moneda(elem));
		}
	}
}

bool obtenerSiNo(const std::string mensaje)
{
	// Limpia cin de entradas anteriores
	if(std::cin.fail()) {
		std::cin.clear();
		std::cin.ignore();
    }
	std::string leido;
	std::cout << mensaje << "(s/n): ";
	std::cin >> leido;
	// Limpia cin si hay algún fallo en la lectura
	if(std::cin.fail()) {
		std::cin.clear();
		std::cin.ignore();
    }

	while(leido[0] != 's' && leido[0] != 'n') {
		std::cout << "Error. Introduzca la letra s para si y la n para no" << std::endl;
		std::cout << "> ";
		std::cin >> leido;
	}

	if (leido[0] == 's')
		return true;
	else
		return false;
}

bool fijarBillete(SistemaMonetario& s)
{
	if (obtenerSiNo("¿Desea fijar un valor para los billetes?")) {
		bool seguir = true;
		int num;

		do {
			std::cout << "Introduzca el menor billete: ";
			std::cin >> num;

			if (num > 0 && s.exists(num)) {
				seguir = false;
			} else {
				std::cout << "El valor debe estar entre los del conjunto" << std::endl;
			}
		} while(seguir);

		s.setMenorBillete(num);

	} else {
		return false;
	}

	return true;
}

void imprimirCambio(const Solucion& sol)
{
	const Cambio& c = sol.getCambio();
	int dinero = sol.getDinero();

	std::cout << "El cambio para " << dinero << " es:" << std::endl;

	int mayor_elem = 0;

	// Obtiene el elemento más ancho para imprimir con el ancho correcto
	for (auto& elem : c) {
		if (!(elem.moneda < mayor_elem)) {
			mayor_elem = elem.moneda.getValor();

		}
		if (elem.cantidad > mayor_elem) {
			mayor_elem = elem.cantidad;
		}
	}

	const std::string sep = " | ";
	const int ancho = std::to_string(mayor_elem).length();

	// Imprime el cambio en formato tabulado
	//
	using std::ios;
	// Valores de moneda
	std::cout << "Valores:   " << std::setw(ancho) << c[0].moneda;
	for (size_t i = 1; i < c.size(); i++) {
		std::cout << sep << std::setw(ancho) << c[i].moneda;
	}
	std::cout << std::endl;

	// Cantidad de moneda
	std::cout << "Cantidad:  " << std::setw(ancho) << c[0].cantidad;
	for (size_t i = 1; i < c.size(); i++) {
		std::cout << sep << std::setw(ancho) << c[i].cantidad;
	}
	std::cout << std::endl;
}