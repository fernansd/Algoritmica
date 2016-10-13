#include <iostream>
#include <fstream>
#include <cmath>

#include "funciones.hpp"
#include "Tiempo.hpp" // Clase para medir el tiempo que pasa

using std::cout;
using std::cin;
using std::endl;
using std::string;

int main () {
	srand(time(NULL));

	//
	// Inicio del programa
	//
	
	// Parámetros automatizados
	int mat_min = 100, mat_max = 400, mat_paso = 10;
	int fib_min = 20, fib_max = 40, fib_paso = 1;
	
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
	
	// Crea matrices para hacer Cramer
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
		
		for (size_t j = 0; j < m4.size(); j++) {
			aux_m4[j] = m4[j][i];
		}
		
		coef_m4[i] = (double)determinanteMatriz(m4) / det_m4;
		
		// Restaura matriz a su estado anterior
		for (size_t j = 0; j < m4.size(); j++) {
			m4[j][i] = aux_m4[j];
		}
	
		if (i < coef_m3.size()) {
			for (size_t j = 0; j < m3.size(); j++) {
				aux_m3[j] = m3[j][i];
			}
			
			coef_m3[i] = (double)determinanteMatriz(m3) / det_m3;
			
			// Restaura matriz a su estado anterior
			for (size_t j = 0; j < m3.size(); j++) {
				m3[j][i] = aux_m3[j];
			}
		}
	}
	
	// Vuelca datos matrices a fichero
	std::ofstream archivo("datos-mat.txt", std::ios::out /*| std::ios::app*/);
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
	
	// Sumatorios para fibonacci
	long double sum_x1 = 0, sum_x2 = 0,
				sum_y = 0, sum_xy = 0;
	long double n_fib = tiempos_fib.size();
	for (size_t i = 0; i < tiempos_fib.size(); i++) {
		sum_x1 += tiempos_fib[i].real;
		sum_x2 += pow(tiempos_fib[i].real, 2);
		
		sum_y += pow(tiempos_fib[i].tam, 2);
		sum_xy += pow(tiempos_fib[i].tam, 2) * tiempos_fib[i].real;
		
	}
	// Coeficientes de estimación de tiempos para fibonacci
	long double fib_a0, fib_a1;
	
	// Matriz base para cramer
	Matriz cramer_fib(2, Fila(2, 0.0));
	cramer_fib[0][0] = n_fib;
	cramer_fib[1][0] = sum_x1;
	cramer_fib[0][1] = sum_x1;
	cramer_fib[1][1] = sum_x2;
	
	long double det_fib = determinanteMatriz(cramer_fib);
	cramer_fib[0][0] = sum_y;
	cramer_fib[1][0] = sum_xy;
	fib_a0 = (double)determinanteMatriz(cramer_fib) / det_fib;
	
	cramer_fib[0][0] = sum_y;
	cramer_fib[1][0] = sum_xy;
	cramer_fib[0][1] = sum_x1;
	cramer_fib[1][1] = sum_x2;
	fib_a1 = (double)determinanteMatriz(cramer_fib) / det_fib;
	
	// Genera tiempos estimados y guarda datos en fichero
	std::ofstream archivo_fib("datos-fib.txt", std::ios::out /*| std::ios::app*/);
	if (!archivo_fib.is_open()) {
		cout << "Error: No se pudo abrir el archivo de escritura" << endl;
	}
	for (size_t i = 0; i < tiempos_fib.size(); i++) {
		
		tiempos_fib[i].est = fib_a0 + fib_a1*pow(2,tiempos_fib[i].tam);
			
		
		archivo_fib << tiempos_fib[i].tam << " " << tiempos_fib[i].real << " "
				<< tiempos_fib[i].est << endl;
	}
	
	archivo_fib.close();
	
	// Calculo medias
	long double media_mat_real = 0;
	long double media_mat_est = 0;
	for (size_t i = 0; i < tiempos_mat.size(); i++) {
		media_mat_real += tiempos_mat[i].real;
		media_mat_est += tiempos_mat[i].est;
	}
	media_mat_real = media_mat_real / tiempos_mat.size();
	media_mat_est = media_mat_est / tiempos_mat.size();
	
	long double media_fib_real = 0;
	long double media_fib_est = 0;
	for (size_t i = 0; i < tiempos_mat.size(); i++) {
		media_fib_real += tiempos_fib[i].real;
		media_fib_est += tiempos_fib[i].est;
	}
	media_fib_real = media_fib_real / tiempos_fib.size();
	media_fib_est = media_fib_est / tiempos_fib.size();
	
	// Calculo varianzas
	long double var_mat_real = 0;
	long double var_mat_est = 0;
	for (size_t i = 0; i < tiempos_mat.size(); i++) {
		var_mat_real += pow(tiempos_mat[i].real - media_mat_real, 2);
		var_mat_est += pow(tiempos_mat[i].est - media_mat_est, 2);
	}
	var_mat_real = var_mat_real / tiempos_mat.size();
	var_mat_est = var_mat_est / tiempos_mat.size();
	
	long double var_fib_real = 0;
	long double var_fib_est = 0;
	for (size_t i = 0; i < tiempos_fib.size(); i++) {
		var_fib_real += pow(tiempos_fib[i].real - media_fib_real, 2);
		var_fib_est += pow(tiempos_fib[i].est - media_fib_est, 2);
	}
	var_fib_real = var_fib_real / tiempos_fib.size();
	var_fib_est = var_fib_est / tiempos_fib.size();
	
	// Coeficientes de determinación
	cout << endl;
	cout << "Coeficiente de determinación matrices: " << var_mat_est/var_mat_real << endl;
	cout << "Coeficiente de terminación fibonacci: " << var_fib_est/var_fib_real << endl;
	
	
	
	// Permite al usuario pedir estimaciones pra ciertos valores de ejemplar
	//
	cout << endl << "Tiempos estimados personalizados:" << endl;
	
	string ejemplar;
	
	cout << "Producto matrices" << endl;
	for(;;) {
		cout << "Introduce tamaño de ejemplar(0 para terminar):";
		cin >> ejemplar;
		int n = std::stoi(ejemplar);
		
		if (n == 0) break;
		
		long double est = 0;
		for (size_t j = 0; j < coef_m3.size(); j++) {
			est += pow(n, j) * coef_m3[j];
		}
		cout << "Estimación: " << est << endl;
	}
	cout << "Fibonacci" << endl;
	for(;;) {
		cout << "Introduce tamaño de ejemplar(0 para terminar):";
		cin >> ejemplar;
		int n = std::stoi(ejemplar);
		
		if (n == 0) break;
		
		cout << "Estimación: " << fib_a0 + fib_a1*pow(2,n) 
			 << endl;
		
		
	}	
	
	//
	// Fin del programa
	//
return 0;
}
