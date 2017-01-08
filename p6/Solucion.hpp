#ifndef CLASE_SOLUCION_HPP
#define CLASE_SOLUCION_HPP

#include <algorithm>
#include <iostream>
#include <vector>

template <typename T>
class Conjunto;
/*
 * Clase que guarda los valores de solución a la suma de subconjuntos
 */
template <typename T>
class Solucion {
public:
	Solucion() { }

	Solucion(std::vector<T>& valores) : sol_(valores) 
	{
		suma_ = std::accumulate(sol_);
	}

	size_t size() const { return sol_.size(); }

	const T& getElem(size_t pos) const { return sol_[pos]; }

	int getSuma() const { return suma_; }

	void insert(const T& elem)
	{
		sol_.push_back(elem);
		suma_ = suma_ + elem;
	}

	T operator[](size_t pos) const
	{
		return sol_[pos];
	}

	void push_back(const T& elem)
	{
		suma_ += elem;
		sol_.push_back(elem);
	}

	void pop_back()
	{
		suma_ -= sol_.back();
		sol_.pop_back();
	}

	template<typename U>
	friend std::ostream& operator<<(std::ostream& stream, const Solucion<U>& s);

private:
	std::vector<T> sol_;
	int suma_ = 0;
}; // Fin clase Solucion

template<typename T>
std::ostream& operator<<(std::ostream& stream, const Solucion<T>& s)
{
	for (size_t i = 0; i < s.size(); i++) {
		std::cout << s.getElem(i) << " ";
	}
	return stream;
}

template<typename T>
using VectorSolucion = std::vector<Solucion<T>>;

#endif