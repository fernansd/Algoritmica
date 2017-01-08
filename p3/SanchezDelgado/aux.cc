template<typename T>
bool conjuntoOrdenado(Conjunto<T>& c, bool creciente)
{
	// Se considera el vector ordenado si no hay al menos dos elementos
	if (c.size() == 0 || c.size() == 1) return true;
	
	// Por defecto se considera ordenado
	// Se cambiará a false en caso de que no se cumpla la condición de orden
	bool ordenado = true;
	for (size_t i = 1; i < c.size(); i++) {
	
		// Por defector creciente = true
		if (creciente) {
			if (c[i-1] > c[i]) {
				ordenado = false;
				break;
			}
		} else {
			if (c[i-1] < c[i]) {
				ordenado = false;
				break;
			}
		}
	}
	return ordenado;
}
