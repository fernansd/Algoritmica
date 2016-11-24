#include <iostream>

#include "funciones.hpp"

using namespace std;

#include <vector>

int main () {

	vector<double> v = {10, 10, 11, 15, 14, 12, 10, 9};
	double media = 0;
	for (size_t i = 0; i < v.size(); i++) {
		media += v[i];
	}
	media = media / v.size();

	double var = 0;
	for (size_t i = 0; i < v.size(); i++) {
		var += (v[i] - media) *2;
	}
	

	cout << "Varianza: " << var << endl << "Media: " << media << endl;

	// Var: sumatorio(x^2/n) - mediaX^2

return 0;
}
