#include "funciones.hpp"

// Menú
int menu() {
	// Parámetros para comprobación de errores
	const int primer_num = 0;
	const int ultimo_num = 3;

	int opcion = -1;
	while (opción == -1) {
		cout << "Elige una opcioón del menú:\n"
			 << "\t1) Combinatorio recursivo\n"
			 << "\t2) Combinatorio recursivo con tabla\n"
			 << "\t3) Combinatorio iterativo\n"
			 << "\t0) Salir\n" << endl;
		cout << "\t> ";
		cin >> opcion;

		if (opcion < primer_num || opcion > ultimo_num) {
			opcion = -1;
			cout << "Error. Introduzca una opción válida." << endl;
		}
	}

	return opcion;
}

// Opción 1: combinatorio
long combinatorioRecursivo(int n, int k) {
	if (k == 0 || n == k) return 1;
	if (k == 1 || k == n-1) return n;
	
	return combinatorioRecursivo(n-1, k) + combinatorioRecursivo(n-1, k-1);
}

long combinatorioTabla(int n, int k, Tabla& t) {
	if (k == 0 || n == k) return 1;
	if (k == 1 || k == n-1) return n;
	// Si la tabla no tiene el tamaño adecuado
	if ((size_t)n > t.size() || (size_t)k > t[0].size()) 
		return -1;
	
	t[n-1][k-1] = combinatorioTabla(n-1, k, t) + combinatorioTabla(n-1, k-1, t);
	return t[n-1][k-1];
}

long combinatorioIterativo(int n, int k) {
	long double factorial_n, factorial_k, factorial_nk;

	factorial_n = 1;
	for (int i = 2; i <= n; i++) {
		factorial_n = factorial_n * i;
	}

	factorial_k = 1;
	for (int i = 2; i <= k; i++) {
		factorial_k = factorial_k * i;
	}

	// Factorial de n-m
	factorial_nk = 1;
	for (int i = 2; i <= (n-k); i++) {
		factorial_nk = factorial_nk * i;
	}

	return factorial_n / factorial_k / factorial_nk;
}
