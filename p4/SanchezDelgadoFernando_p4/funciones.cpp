#include "funciones.hpp"

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

Cambio obtenerCambio(int dinero, SistemaMonetario& s) {
	std::vector<Cantidad> v;

	// Recorremos todos las monedas almacenadas en el sistema
	// de mayor a menor valor
	for (auto it = s.rbegin(); it != s.rend(); it++) {
		Cantidad c;
		c.moneda = it->getValor();

		// Cogemos de cada moneda tanto como podamos
		while (c.moneda <= dinero) {
			c.cantidad++;
			dinero -= c.moneda.getValor();
		}

		if (c.cantidad > 0) {
			v.push_back(c);
		}

		// Si nos quedamos sin dinero dejamos de coger monedas
		if (dinero <= 0)
			break;

	}

	// En el caso de que el sistema monetario no permita dar un cambio
	// completo, se devuelve un cambio vacío
	if (dinero != 0) {
		return Cambio();
	}

	return v;
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

bool obtenerSiNo(const std::string mensaje)
{
  std::string leido;
  std::cout << mensaje << "(s/n): ";
  std::cin >> leido;

  while(leido[0] != 's' && leido[0] != 'n') {
    std::cout << "Error. Introduzca la letra s para si y la n para no" << std::endl;
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

void imprimirCambio(Cambio& c, int dinero)
{
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
	std::cout << "Valores:  " << std::setw(ancho) << c[0].moneda;
	for (size_t i = 1; i < c.size(); i++) {
		std::cout << sep << std::setw(ancho) << c[i].moneda;
	}
	std::cout << std::endl;

	// Cantidad de moneda
	std::cout << "Cantidad: " << std::setw(ancho) << c[0].cantidad;
	for (size_t i = 1; i < c.size(); i++) {
		std::cout << sep << std::setw(ancho) << c[i].cantidad;
	}
	std::cout << std::endl;
}