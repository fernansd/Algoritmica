#ifndef CLASE_SOLUCION_HPP
#define CLASE_SOLUCION_HPP

#include "SistemaMonetario.hpp"

struct Cantidad;
typedef std::vector<Cantidad> Cambio;

class Solucion {
public:
	Solucion() { }

	Solucion(int dinero, const Cambio& c, const SistemaMonetario& s)
	: cambio_(c), sistema_(s), dinero_(dinero) { }

	const Cambio& getCambio() const { return cambio_; }
	const SistemaMonetario& getSistema() const { return sistema_; }
	int getDinero() const { return dinero_; }

	void setCambio(const Cambio& c) { cambio_ = c; }
	void setSistema(const SistemaMonetario& s) { sistema_ = s; }
	void setDinero(int dinero) { dinero_ = dinero; }

private:
	Cambio cambio_;
	SistemaMonetario sistema_;
	int dinero_;
};
#endif
