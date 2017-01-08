#ifndef CLI_HPP
#define CLI_HPP

#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>

#include "SistemaMonetario.hpp"

/*!\brief Define los parámetro opcionales de tu programa.

  Redefine esta clase en función de tus necesitados
*/
struct CLIParams
{
  CLIParams ()
    : sistema(false)
    {}
  bool sistema; // Se pasa una lista de monedas por consola
};

/*!\brief Muestra la ayuda del programa.  
  Redefinir en función de los parámetros utilizados realmente.
  \arg[in] programe es el nombre del programa en la cli.
*/
static void
mostrarUso (const char * progname) throw ()
{
  std::cout << "Este programa sirve para dar el cambio ante una"
  				" cantidad de dinero y unas monedas y billetes concretos" << std::endl;
  std::cout << "Uso: " << progname << " [-h] {[-c arg1 arg2 ... argn] | [tam]}" << std::endl;
  std::cout << "Donde: " << std::endl;
  std::cout << "[dinero] es el tamaño del conjunto a generar, sólo si -c no está activo"
  			<< std::endl;
  std::cout << "-h\tMuestra esta ayuda." << std::endl;
  std::cout << "-s\tPermite introducir los valores del sistema monetario."
            << " Solo permite números positivos" << std::endl;
}

/*!\brief Parsea la linea de comandos.
  \arg[in] argc es el número de argumentos en la línea.
  \arg[in] argv son los argumentos de la línea.
  \arg[out] params son los parámetros opcionales parseados.
  \return El índice del primer argumento no opcional de la línea.
  \warning Esta función no retorna si hay algún error en la cli.
*/
static int
parseCLI (int argc, char* const* argv, CLIParams& params) throw ()
{
  // Esta es una forma habitual de recoger argumentos con getopt
  // se usa una iteracion y cada elemento se pasa por un switch-case
  int opcion;
  while ((opcion = getopt (argc, argv, "hs::")) != -1)
  {
    switch (opcion)
    {
      
      case 'h':
		  mostrarUso(argv[0]);
		  exit (EXIT_SUCCESS);
		  break;
  
      case 's':
		  params.sistema = true;
		  break;

      case '?': // en caso de error getopt devuelve el caracter ?
  		  if (isprint (optopt))
  			std::cerr << "Error: Opción desconocida \'" << optopt
  			  << "\'" << std::endl;
  		  else
  			std::cerr << "Error: Caracter de opcion desconocido \'x" << std::hex << optopt
  			  << "\'" << std::endl;
  		  mostrarUso(argv[0]);    
  		  exit (EXIT_FAILURE);
  
  	  // en cualquier otro caso lo consideramos error grave y salimos
      default:
  		  std::cerr << "Error: línea de comandos errónea." << std::endl;
  		  mostrarUso(argv[0]);
  		  exit(EXIT_FAILURE); 
    }  // case
    
  }// while
  return optind;
}

void parseSistemaCLI(SistemaMonetario& s, int argc, int argObl, char* const *argv)
{
  int n_param = argc-argObl;

  if (n_param < 1) {
    std::cerr << "Número de argumentos erróneo" << std::endl;
    std::cout << n_param << std::endl;
    mostrarUso(argv[0]);
    exit(-1);

  } else {

    for (int i = 0; i < n_param; i++) {
      int num = atoi(argv[argObl+i]);
      if (num < 1) {
        std::cerr << "Error. El valor para los elementos del sistema"
                     " debe ser mayor o igual a 1" << std::endl;
        mostrarUso(argv[0]);
        exit(-1);
      }

      s.push(num);
    }
  }
}

#endif
