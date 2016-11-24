#include <algorithm> //Para usar algoritmos de la clase stl. Necesario para usar el método sort.
#include <vector> //Para usar la clase vector de la stl
#include <iostream>

#include "generarpersona.hpp"
#include "persona.hpp"

using namespace std;

//En este ejemplo se mostrarán dos formas de ordenar un vector usando la stl.
//VER EJEMPLO EN: http://www.menudoproblema.es/blog/entries/2010/12/05/functores-y-ordenacion-mediante-sort-en-la-stl/

//La primera de ellas ordena usando la opcion por defecto de la funcion sort.
//En ella se usa el < sobrecargado y se ordena ascendentemente.

//En la segunda se define un Functor (Function Object) que es el que se pasará a la funcion sort para ordenar.
//Un functor es un objeto que puede ser invocado como una funcion.

//Definimos el functor para poder ordenar usando la segunda forma.
struct MenorPersona
{
	bool operator()(Persona x, Persona y)
	{
		return x.dni() < y.dni();
	}
};	

int main()
{
	vector <Persona> p, p1; //Vector de la STL para introducir personas
	vector <Persona>::iterator it; //Iterador para recorrer el vector de la stl
	Persona aux;
	int numeroPersonas;
	
	cout << "Numero de personas a introducir: ";
	cin >> numeroPersonas;

	//Primera forma.
	
	//Introducimos las personas en el vector de la stl usando push_back();
	
	cout << "PRIMER METODO \n";
	for(int i = 1; i <= numeroPersonas; i++)
	{
		aux = generarDatosPersonales(); //Se genera una persona aleatoriamente
		p.push_back(aux);
	}
	
	//Ordenamos el vector, usando la opcion por defecto que es ordenar ascendente usando el operador < definido en la clase.
	sort(p.begin(), p.end());
	
	//Mostramos vector ordenado.
	for(it = p.begin(); it != p.end(); it++)
	{
		(*it).mostrarPersona();
	}
	
	
	//Segunda forma.
	
	cout << "SEGUNDO METODO \n";
	//Definimos el objeto functor
	MenorPersona comparador;
	
	//Introducimos las personas en el vector de la stl usando push_back();
	for(int i = 1; i <= numeroPersonas; i++)
	{
		aux = generarDatosPersonales(); //Se genera una persona aleatoriamente
		p1.push_back(aux);
	}
	
	//Ordenamos el vector, usando el functor como funcion para comparar.
	//La ventaja con respecto a la anterior es que podemos usar cualquier campo para comparar
	//definiendo un functor para cada campo.
	sort(p1.begin(), p1.end(), comparador);
	
	//Mostramos vector ordenado.
	for(it = p1.begin(); it != p1.end(); it++)
	{
		(*it).mostrarPersona();
	}
	
	return 0;
}


	
	
	
	
	
	
	
	
