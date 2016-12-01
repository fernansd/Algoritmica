#ifndef FUNCIONES_HPP
#define FUNCIONES_HPP

#include <vector>
#include <string>

#include "Moneda.hpp"
#include "SistemaMonetario.hpp"


struct Cantidad {
	Moneda moneda;
	int cantidad = 0;

	Cantidad() { }
	Cantidad(int val)
		: moneda(val) { }
    Cantidad(int val, int cant)
        : moneda(val), cantidad(cant) { }
};

typedef std::vector<Cantidad> Cambio;

Cambio obtenerCambio(long cantidad, SistemaMonetario& s);


//
// FUNCIONES AUXILIARES

std::string obtenerNombreFichero();

void leerSistemaFichero(SistemaMonetario& s, const std::string& nombre);

bool obtenerSiNo(const std::string mensaje);

bool fijarBillete(SistemaMonetario& s);

void imprimirCambio(Cambio& c, long dinero);

template <class T>
int numDigits(T num)
{
    int digits = 0;
    if (num < 0)
    	digits = 1;

    while (num) {
        num = num/10;
        digits++;
    }
    return digits;
}

#endif