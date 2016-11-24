#include "funciones.hpp"

int main () {
	int n,k;
	
	cout << "N: ";
	cin >> n;
	cout << "K: ";
	cin >> k;
	
	cout << "Combinatorio n sobre k: " << combinatorio(n,k) << endl;
	Tabla t(n, Fila(k,-1));
	cout << "Combinatorio con tabla: " << combinatorioTabla(n,k,t) << endl;

return 0;
}
