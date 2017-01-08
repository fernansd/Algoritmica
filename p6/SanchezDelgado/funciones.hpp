#ifndef FUNCIONES_HPP
#define FUNCIONES_HPP

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include "Solucion.hpp"
#include "Conjunto.hpp"
#include "Solucion.hpp"


template<typename T>
void sumaSubconjuntos(long s, long r, int k, int suma, const Conjunto<T>& c,
	Solucion<T> x, VectorSolucion<T>& sol)
{
	x.push_back(c[k]);
	if (x.getSuma() == suma) {
		sol.push_back(x);
	} else {
		if (x.getSuma() + c[k+1] <= suma) {
			sumaSubconjuntos(x.getSuma(), r-c[k], k+1, suma, c, x, sol);
		}
	}

	if ((s + r - c[k] >= suma) && (s + c[k+1] <= suma)) {
		x.pop_back();
		sumaSubconjuntos(s, r-c[k], k+1, suma, c, x, sol);
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

template<typename T>
void imprimirSolucion(const VectorSolucion<T>& v, const Conjunto<T>& c)
{
	using namespace std;

	if (v.empty()) {
		cout << "No se han encontrado soluciones" << endl;
		return;
	}

	if (obtenerSiNo("¿Desea ver el conjunto origen?")) {

		cout << "El conjunto es:" << endl;
		cout << c;
		cout << endl;
	}

	cout << "Los subconjuntos que suman " << v[0].getSuma() << " son:" << endl;

	for (size_t i = 0; i < v.size(); i++) {
		cout << v[i] << '\n';
	}
	cout << endl;
}

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

template<typename T>
void leerConjuntoFichero(Conjunto<T>& c, const std::string nombre_fichero)
{
	// El formato del fichero es: un elemento del conjunto en cada línea
	// No se esperan líneas vacías
	std::ifstream archivo(nombre_fichero);
	int valor;
	std::vector<T> aux;
	c.clear();

	while (archivo >> valor) {
		aux.push_back(valor);
	}

	c.cambiarConjunto(aux);
}

template<typename T>
void pedirConjunto(Conjunto<T>& c)
{
	c.clear();

	using namespace std;
	cout << "Introducir 0 para parar" << endl;

	int elem = -1;
	while (elem != 0) {
		cout << "> "; // Pide número
		if (!(cin >> elem)) {
			cerr << "Error. Solo se aceptan enteros" << endl;
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
			c.push_back(elem);
		}
	}
}

int pedirSumaObjetivo(const std::string mensaje = "> ") {
		using namespace std;

		int num = -1;
		while (num == -1) {
			cout << endl << mensaje;

			if (!(cin >> num)) {
				cerr << "Error. Solo se aceptan números" << endl;
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				num = -1;
			}

			if (num < 0) {
				cerr << "El número debe ser una de las opciones" << endl;
				num = -1;
			}
			
		}

		return num;
}

#endif