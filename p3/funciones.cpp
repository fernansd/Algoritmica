#include <random>
#include <algorithm>

#include "funciones.hpp"


template<typename T>
int obtenerMaxMin(Conjunto<T>& c, T& min, T& max, int i, int j)
{
	// Las comparaciones que se cuentan son las incluidas en el algoritmo
	// teòrico, en realidad se usan más comparaciones debido a requisitos
	// de la implementación
	int comparaciones = 0;
	
	// La primera vez que un usuario llama a la función no necesita especificar
	// el tamaño del conjunto, de ahí que se asigne el tamaño si j tiene
	// el valor por defecto del parámetro
	if (j == -1) {
		j = c.size();
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
