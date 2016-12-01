#ifndef CLASE_MONEDA_HPP
#define CLASE_MONEDA_HPP

#include <cassert>
#include <iostream>

class Moneda {
public:
	Moneda() { }

	Moneda(int valor) {
		this->setValor(valor);
	}

	// OBSERVADORES
	int getValor() const { return valor_; }

	// MODIFICADORES
	bool setValor(int valor)
	{
		assert(valor > 0);
		if (valor > 0) {
			valor_ = valor;
			return true;
		} else {
			return false;
		}
	}

	// OPERADORES DE COMPARACIÓN
	// La comparación se realiza en base al valor de la moneda.
	// No se tiene en cuenta la cantidad disponible de la moneda
	bool operator==(const Moneda& m) const
	{
		if (this->getValor() == m.getValor())
			return true;
		else 
			return false;
	}

	bool operator!=(const Moneda& m) const
	{
		return !(*this == m);
	}

	bool operator<(const Moneda& m) const
	{
		if (this->getValor() < m.getValor())
			return true;
		else
			return false;
	}

	bool operator<(int n) const
	{
		if (this->getValor() < n)
			return true;
		else
			return false;
	}

	friend bool operator<(int n, const Moneda& m)
	{
		if (n < m.getValor())
			return true;
		else
			return false;
	}

	bool operator>(const Moneda& m) const
	{
		if (this->getValor() > m.getValor())
			return true;
		else
			return false;
	}

	bool operator<=(const Moneda& m) const
	{
		if (*this > m)
			return false;
		else
			return true;
	}

	bool operator<=(int n) const
	{
		if (n < this->getValor())
			return false;
		else
			return true;
	}

	bool operator>=(const Moneda& m) const
	{
		if (*this < m)
			return false;
		else
			return true;
	}

	friend std::ostream& operator<<(std::ostream& stream, const Moneda& m)
	{
		stream << m.getValor();

		return stream;
	}

private:
	int valor_ = 0;
};

#endif