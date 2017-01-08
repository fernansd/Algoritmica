#ifndef FUNCIONES_HPP
#define FUNCIONES_HPP

#include <vector>
#include <string>

#include "Moneda.hpp"
#include "SistemaMonetario.hpp"
#include "Solucion.hpp"


struct Cantidad {
    Moneda moneda;
    int cantidad = 0;

    Cantidad() { }
    Cantidad(int val)
        : moneda(val) { }
    Cantidad(int val, int cantidad)
        : moneda(val), cantidad(cantidad) { }
};

typedef std::vector<Cantidad> Cambio;

Solucion obtenerCambio(long dinero, SistemaMonetario& v);


//
// FUNCIONES AUXILIARES

std::string obtenerNombreFichero();

void leerSistemaFichero(SistemaMonetario& s, const std::string& nombre);

void pedirSistema(SistemaMonetario& s);

bool obtenerSiNo(const std::string mensaje);

bool fijarBillete(SistemaMonetario& s);

void imprimirCambio(const Solucion& sol);

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