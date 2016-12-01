#ifndef CLASE_SISTEMA_MONETARIO_HPP
#define CLASE_SISTEMA_MONETARIO_HPP

#include <cassert>
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

#include "Moneda.hpp"

struct Cantidad;

class SistemaMonetario : public std::set<Moneda> {
public:
	SistemaMonetario() { }
	SistemaMonetario(std::vector<Moneda>& v)
	{
		this->insert(v.begin(), v.end());
	}

	SistemaMonetario(std::initializer_list<Moneda> list)
		: std::set<Moneda>(list) { }

	// Inserta una moneda al sistema
	void push(const Moneda& m) {
		this->insert(m);
	}

	// Quita una moneda del sistema y la devuelve
	Moneda pop(int valor) {
		Moneda m(valor);
		this->erase(m);
		return m;
	}

	// Comprueba si existe una moneda determinada
	bool exists(const Moneda& m) const {
		// Cuando find devuelve end, es que no ha encontrado el elemento
		return !(this->find(m) == this->end());
	}

	bool exists(int valor) const {
		Moneda m(valor);
		return this->exists(m);
	}

	bool setMenorBillete(int valor)
	{
		if (this->exists(valor)) {
			menor_billete_ = valor;
			return true;
		} else {
			return false;
		}
	}

	int getMenorBillete() { return menor_billete_; }


	
	Moneda& operator[](size_t i)
	{
		auto it = this->begin();
		while (i--) {
			it++;
		}

		return const_cast<Moneda&> (*it);
	}

	friend std::ostream& operator<<(std::ostream& stream, const SistemaMonetario& s)
	{
		if (s.menor_billete_ <= 0) {
			// No se ha fijado un valor de billete
			for (auto it = s.begin(); it != s.end(); it++) {
				stream << *it << " ";
			}
		} else {
			auto it = s.begin();

			stream << "Monedas:";
			while (it != s.end() && (*it < s.menor_billete_)) {
				stream << " " << *it;

				it++;
			}
			stream << std::endl;

			stream << "Billetes:";
			while (it != s.end()) {
				stream << " " << *it;

				it++;
			}
		}
		stream << std::endl;

		return stream;
	}

	friend std::vector<Cantidad> obtenerCambio(int cantidad, SistemaMonetario& s);

private:
	int menor_billete_ = 0;
};
#endif