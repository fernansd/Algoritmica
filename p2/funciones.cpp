#include "funciones.hpp"

// Menú
int menu() {
	return 0;
}

// Opción 1: combinatorio
int combinatorio(int n, int k) {
	if (k == 0 || n == k) return 1;
	if (k == 1 || k == n-1) return n;
	
	return combinatorio(n-1, k) + combinatorio(n-1, k-1);
}

int combinatorioTabla(int n, int k, Tabla& t) {
	if (k == 0 || n == k) return 1;
	if (k == 1 || k == n-1) return n;
	// Si la tabla no tiene el tamaño adecuado
	if ((size_t)n > t.size() || (size_t)k > t[0].size()) return -1;
	
	t[n][k] = combinatorio(n-1, k) + combinatorio(n-1, k-1);
	return t[n][k];
}

int combinatorioIterativo(int n, int k) {
	return 0+n+k;
}

// Opción 2: Hanoi
int hanoi(int n) {
	return 0+n;
}
