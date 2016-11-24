#ifndef FUNCIONES_HPP
#define FUNCIONES_HPP

#include <random>
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>

template<typename T>
using Conjunto = std::vector<T>;

template<typename T>
int obtenerMaxMin(Conjunto<T>& c, T& min, T& max, int i = 0, int j = -1)
{
	// Las comparaciones que se cuentan son las incluidas en el algoritmo
	// teòrico, en realidad se usan más comparaciones debido a requisitos
	// de la implementación
	int comparaciones = 0;
	
	// La primera vez que un usuario llama a la función no necesita especificar
	// el tamaño del conjunto, de ahí que se asigne el tamaño si j tiene
	// el valor por defecto del parámetro
	if (j == -1) {
		j = c.size()-1;
	}
	
	comparaciones++;
	if (i == j) {
		min = c[i];
		max = c[i];
	} else {
	
		comparaciones++;
		if (i == j-1) {
		
			comparaciones++;
			if (c[i] < c[j]) {
				max = c[j];
				min = c[i];
			} else {
				max = c[i];
				min = c[j];
			}
			
		} else {
			int mitad = (i+j) / 2;
			T aux_min, aux_max;
			
			comparaciones += obtenerMaxMin(c, min, max, i, mitad);
			comparaciones += obtenerMaxMin(c, aux_min, aux_max, mitad+1, j);
			
			min = std::min(min, aux_min);
			max = std::max(max, aux_max);
		}
	}	

	return comparaciones;
}

template<typename T>
bool validarMinMax(Conjunto<T>& c, T& min, T& max)
{
	// Devuelve un pair
	auto resultado = std::minmax_element(c.begin(), c.end());
	
	if ((min == *resultado.first) && (max == *resultado.second)) {
		return true;
	}
	
	std::cout << "Min: " << *resultado.first << " Max: " << *resultado.second << std::endl;
	
	return false;
}

void generarConjuntoEnteros(Conjunto<int> &c, int tam)
{
	// Obtiene un número para dar al generador
	std::random_device r_num;
    // Crea el generador con semilla el número anterior
    std::default_random_engine gen(r_num());
    // Define el rango para operar
    std::uniform_int_distribution<> rango(1, 10000);

    // Cambia el tamaño del vector al pedido
    c.resize(tam);

    // Rellena el vector con números aleatorios
    for (int i = 0; i < tam; i++) {
    	c[i] = rango(gen);
    }
}

template<typename T>
bool grabarConjunto(Conjunto<T>& c, const std::string nombre, T& min, T& max)
{
	std::fstream archivo(nombre, std::ios::out);
	if (!archivo.is_open()) {
		std::cerr << "No se ha podido grabar el fichero" << std::endl;
		return false;
	}
	
	archivo << min << " " << max << std::endl;
	for (size_t i = 0; i < c.size(); i++) {
		archivo << c[i] << std::endl;
	}
	
	return true;
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

#endif
