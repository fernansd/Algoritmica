#ifndef CLASE_CONJUNTO_HPP
#define CLASE_CONJUNTO_HPP

#include <vector>
#include <algorithm>
#include <set>
#include <numeric>
#include <iostream>

#include "Solucion.hpp"
#include "funciones.hpp"

// Se recomienda solo para tipos que representen enteros
template<typename T>
class Conjunto {
public:
	Conjunto() { }

	Conjunto(std::set<T>& s) : data_(s)	{ }

	Conjunto(std::vector<T>& v)
	{
		data_.insert(v.begin(), v.end());
	}

	Conjunto(std::initializer_list<T> lista) : data_(lista) { }

	bool exists(T& val)
	{
		return !(std::find(data_.begin(), data_.end(), val) != data_.end());
	}

	void clear() { data_.clear(); }

	void push_back(T& elem)
	{
		data_.insert(elem);
	}

	const T& operator[](size_t pos) const
	{
		auto it = data_.begin();
		while (pos--) {
			it++;
		}

		return *it;
	}

	void cambiarConjunto(std::vector<T>& v)
	{
		data_.clear();
		data_.insert(v.begin(), v.end());	
	}

	VectorSolucion<T> obtenerConjuntoSuma(T& valor_suma) const;

	template<typename U>
	friend std::ostream& operator<<(std::ostream& stream, const Conjunto<U>& s);

private:
	std::set<T> data_;

}; // Fin clase

template<typename T>
VectorSolucion<T> Conjunto<T>::obtenerConjuntoSuma(T& valor_suma) const
{
	VectorSolucion<T> soluciones;
	Solucion<T> x;
	long r = std::accumulate(std::begin(this->data_), std::end(this->data_), 0);

	sumaSubconjuntos(0, r, 0, valor_suma, 
		*this,	x, soluciones);

	return soluciones;
}

template<typename U>
std::ostream& operator<<(std::ostream& stream, const Conjunto<U>& s)
{
	for (auto elem : s.data_) {
		stream << elem << " ";
	}

	return stream;
}
#endif