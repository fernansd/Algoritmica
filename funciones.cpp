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
			
			elem = 9 - rand() % 19; // Genera parte entera entre -9 y 9
			elem = elem + (1 / rand() % 10000); // Genera parte decimal
		
			fila.push_back(elem);
		}

		matriz.push_back(fila);
	}
	
	return matriz;
}

Matriz matrizVacia(int fil, int col) {
	
	// Crea la matriz
	Matriz m(fil, Fila(col, 0.0));
	/*
	// Creamos el número de filas necesarias
	for (int i = 0; i < fil; i++) {
		
		m.push_back(f);
	
	}
	*/
	
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

int generarFibonacci(int n) {
	if (n == 0)
		return 0;
		
	if (n == 1)
		return 1;
		
	return generarFibonacci(n-1) + generarFibonacci(n-2);
}





//
// Otras operaciones matriciales
//
int determinanteMatriz(Matriz &m) {

	int tam = m.size();
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
	
	int n = m.size();
	Matriz inversa = m;
	Fila fila_vacia(n, 0.0);
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			inversa[i].push_back(0.0);
		}
	}

	for(int i = 0; i < n; i++)
	{
		for(int j = n; j < 2*n; j++)
		{
			if(i == j-n)
				inversa[i][j]=1;
			else
				inversa[i][j]=0;
		}
	}
	for(int i = 0; i < n; i++)
	{
		double t = inversa[i][i];
		for(int j = i; j < 2*n; j++)
			inversa[i][j] = inversa[i][j]/t;
		
		for(int j = 0; j < n; j++)
		{
			if(i != j)
			{
				t = inversa[j][i];
				for(int k = 0; k < 2*n; k++)
					inversa[j][k] = inversa[j][k] - t*inversa[i][k];
			}
		}
	}
	
	for (int i = 0; i < n; i++) {
		inversa[i].erase(inversa[i].begin(), inversa[i].begin()+n);
	}
	
	return inversa;
}
