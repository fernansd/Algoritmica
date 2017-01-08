#include "funciones.hpp"

int main () {
	int n,k;
	
	cout << "Parámetros para el cálculo de número combinatorio\n"
	cout << "\tN: ";
	cin >> n;
	cout << "\tK: ";
	cin >> k;

	// Permite al usuario interaccionar con el programa hasta
	// que elija la opción de salir
	bool continuar_menu = true;
	do {
		switch(menu()) {
			case 0:
				continuar_menu = false;
				break;
		}
	} while (continuar_menu);
	
	cout << "Combinatorio de n sobre k:\n";
	cout << "Algoritmo recursivo: " << combinatorioRecursivo(n,k) << endl;
	Tabla t(n, Fila(k,-1));
	cout << "Algoritmo con tabla: " << combinatorioTabla(n,k,t) << endl;
	cout << "Algoritmo iterativo: " << combinatorioIterativo(n,k) << endl;

return 0;
}
