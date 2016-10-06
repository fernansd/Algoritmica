#include "funciones.hpp"
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <iomanip>

using std::cout;
using std::endl;


/********
	Funciones auxiliares de matrices
********/
Matriz generarMatriz(int tam) {
	Matriz matriz;
	
	for (int i = 0; i < tam; i++) {
		Fila fila;
		for (int j = 0; j < tam; j++) {
		
			double elem;
			
			elem = 10 - rand() % 21; // Genera parte entera
			elem = elem + (1 / rand() % 10000); // Genera parte decimal
		
			fila.push_back(elem);
		}

		matriz.push_back(fila);
	}
	
	return matriz;
}

Matriz matrizVacia(int fil, int col) {
	Matriz m;
	Fila f;
	
	// Generamos una fila
	for (int i = 0; i < col; i++) {
		f.push_back(0.0);
	}
	
	// Creamos el número de filas necesarias
	for (int i = 0; i < fil; i++) {
		m.push_back(f);
	}
	
	return m;
}

void imprimirMatriz(Matriz &m) {
	for (size_t i = 0; i < m.size(); i++) {
		
		for (size_t j = 0; j < m[i].size(); j++) {
			
			cout << std::setw(10) << m[i][j] << " ";
		}
		cout << endl;
	}
}

/**********
	Operaciones del menú del programa
**********/

Matriz productoMatrices(Matriz &m1, Matriz &m2) {

	Matriz producto = matrizVacia(m1.size(), m1.size());

	for(size_t i=0; i < m1.size(); ++i) {
		for(size_t j=0; j < m2.size(); ++j) {
			for(size_t z=0; z < m1.size(); ++z) {
				producto[i][j] += m1[i][z] * m2[z][j];
			}
		}
	}
	return producto;
}

int determinanteMatriz(Matriz &m) {

	int tam = (int)m.size();
    if (tam == 2)
    {
        return (m[0][0]*m[1][1] - m[0][1]*m[1][0]);
    }
    else
    {
        int k = 0;
        double num = 0;
        int multiplicador;
		Matriz adj = matrizVacia(tam-1, tam-1);
 
        for (int l = 0; l < tam; l++) // Desarrollo por filas
        {
            for (int j = 1; j < tam; j++) // Creo una nueva matriz adjunta
            {
                for (int i = 0; i < tam; i++)
                {
                    if (i != l)
                    {
                        adj[k][j-1] = m[i][j];
                        k++;
                    }
                }
                k = 0;
            }
 
            if ( l % 2 != 0)
                multiplicador = -1;
            else
                multiplicador = 1;
                
            num += (m[l][0]*determinanteMatriz(adj)*multiplicador);
        }
        return num;
    }
}

Matriz invertirMatriz(Matriz &m) {
	Matriz inversa = m;
	int n = m.size();

	for (int i = 0; i < n; i++) {        //Pivotisation
        for (int k = i + 1; k < n; k++) {

            if (inversa[i][i] < inversa[k][i]) {
                for (int j = 0; j <= n; j++) {

                    double temp = inversa[i][j];
                    inversa[i][j] = inversa[k][j];
                    inversa[k][j] = temp;
                }
            }
        }
    }

    for (int i = 0; i < n-1; i++)            //loop to perform the gauss elimination
        for (int k = i + 1; k < n; k++)
            {
                double t = inversa[k][i] / inversa[i][i];
                for (int j = 0; j <= n; j++) {
                    inversa[k][j] = inversa[k][j] - t * inversa[i][j];    //make the elements below the pivot elements equal to zero or elimnate the variables
                }
            }
	return inversa;
}

double generarFibonacci(int n) {

	return 2.0;
}
