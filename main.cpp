#include <iostream>
#include <fstream>
#include <cmath>

#include "funciones.hpp"
#include "Tiempo.hpp" // Clase para medir el tiempo que pasa

using std::cout;
using std::cin;
using std::endl;

int main () {
	srand(time(NULL));

	//
	// Inicio del programa
	//
	
	// Parámetros automatizados
	int mat_min = 100, mat_max = 500, mat_paso = 10;
	int fib_min = 20, fib_max = 45, fib_paso = 1;
	
	/* !!! Descomentar para obtener los parámetros a mano y comentar abajo
	string aux;
	
	cout << "Parámetros ejemplar para operación matricial " << endl;
	
	cout << "Tamaño mínimo: ";
	cin.getline(aux);
	mat_min = std::stoi(aux);
	
	cout << "Tamaño máximo: ";
	cin.getline(aux);
	mat_max = std::stoi(aux);
	
	cout << "Incremento de tamaño: ";
	cin.getline(aux);
	mat_paso = std::stoi(aux);
	
	
	cout << "Parámetros ejemplar para fibonacci " << endl;
	
	cout << "Tamaño mínimo: ";
	cin.getline(aux);
	fib_min = std::stoi(aux);
	
	cout << "Tamaño máximo: ";
	cin.getline(aux);
	fib_max = std::stoi(aux);
	
	cout << "Incremento de tamaño: ";
	cin.getline(aux);
	fib_paso = std::stoi(aux);
	*/
	
	/*
	 *	Obtención de tiempos
	 */
	Clock reloj;
	
	// Tiempo matrices
	std::vector<Tiempos> tiempos_mat;
	for (int i = mat_min; i <= mat_max; i += mat_paso) {
		// Incializaciones
		Matriz m1, m2;
		m1 = generarMatriz(i);
		m2 = generarMatriz(i);
		
		
		// Comienza a medir tiempo de algoritmo
		Clock reloj2;
		reloj.restart();
		
		productoMatrices(m1, m2);
		
		// Termina el tiempo medido
		reloj.stop();
		cout << "Ejemplar: " << i << " Tiempo: " << reloj.elapsed() << endl;
		Tiempos t;
		t.tam = i;
		t.real = reloj.elapsed();
		tiempos_mat.push_back(t);
	}
	cout << endl;
	// Tiempos fibonacci
	std::vector<Tiempos> tiempos_fib;
	for (int i = fib_min; i <= fib_max; i += fib_paso) {
		reloj.restart();
		
		generarFibonacci(i);
		
		// Termina el tiempo medido
		reloj.stop();
		cout << "Ejemplar: " << i << " Tiempo: " << reloj.elapsed() << endl;
		Tiempos t;
		t.tam = i;
		t.real = reloj.elapsed();
		tiempos_fib.push_back(t);
	}
	reloj.start();
	
	/*
	 *	Obtención de ecuaciones
	 */
	// Sumatorios de tiempos matriciales
	std::vector<long double> sums_x(9, 0.0);
	std::vector<long double> sums_xy(5, 0.0);
	sums_x[0] = tiempos_mat.size();
	for (size_t i = 0; i < tiempos_mat.size(); i++) {
		for (size_t j = 1; j < sums_x.size(); j++) {
			
			sums_x[j] += pow(tiempos_mat[i].real, j);
			
			if ( j <= sums_xy.size()) {
				sums_xy[j-1] += pow(tiempos_mat[i].real, j-1) * tiempos_mat[i].tam;
			}
		}
	}
	cout << "acabados sumatorios" << endl;
	
	std::vector<long double> coef_m3(4);
	std::vector<long double> coef_m4(5);
	Matriz m3 = matrizVacia(4,4);
	Matriz m4 = matrizVacia(5,5);
	long double det_m3, det_m4;
	for (size_t i = 0; i < coef_m4.size(); i++) {
		for (size_t j = 0; j < coef_m4.size(); j++) {
			m4[i][j] = sums_x[j+i];
			if (i < coef_m3.size() && j < coef_m3.size()) {
				m3[i][j] = sums_x[j+i];
			}
		}
	}
	det_m3 = determinanteMatriz(m3);
	det_m4 = determinanteMatriz(m4);
	
	// Coeficiente matrices
	std::vector<long double> aux_m3(m3.size());
	std::vector<long double> aux_m4(m4.size());
	for (size_t i = 0; i < coef_m4.size(); i++) {
		
		for (size_t j = 0; j < coef_m4.size(); j++) {
			aux_m4[j] = m4[j][i];
		}
		
		coef_m4[i] = determinanteMatriz(m4) / det_m4;
		
		// Restaura matriz a su estado anterior
		for (size_t j = 0; j < coef_m4.size(); j++) {
			m4[j][i] = aux_m4[j];
		}
	
		if (i < coef_m3.size()) {
			for (size_t j = 0; j < coef_m3.size(); j++) {
				aux_m3[j] = m3[j][i];
			}
			
			coef_m3[i] = determinanteMatriz(m3) / det_m3;
			
			// Restaura matriz a su estado anterior
			for (size_t j = 0; j < coef_m3.size(); j++) {
				m3[j][i] = aux_m3[j];
			}
		}
	}
	
	// Vuelca datos matrices a fichero
	std::ofstream archivo("Datos.txt", std::ios::out | std::ios::app);
	if (!archivo.is_open()) {
		cout << "Error: No se pudo abrir el archivo de escritura" << endl;
	}
	
	for (size_t i = 0; i < tiempos_mat.size(); i++) {
		
		tiempos_mat[i].est = 0;
		for (size_t j = 0; j < coef_m3.size(); j++) {
			tiempos_mat[i].est += pow(tiempos_mat[i].tam, j) * coef_m3[j];
		}
		
		archivo << tiempos_mat[i].tam << " " << tiempos_mat[i].real << " "
				<< tiempos_mat[i].est << endl;
	}
	
	archivo.close();
	//
	// Fin del programa
	//
return 0;
}
