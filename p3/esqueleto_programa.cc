#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <exception>

//Includes para OpenCV, Descomentar según los módulo utilizados.
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp> 
//#include <opencv2/imgproc/imgproc.hpp>
//#include <opencv2/calib3d/calib3d.hpp>


int main (int argc, char* const* argv)
{
  int retCode=EXIT_SUCCESS;
  
  try {    
    CLIParams params;

    int argObligados = parseCLI(argc, argv, params);

    std::cout << "Los parámetros opcioneales son:" << std::endl;
    std::cout << "-v\t" << ((params.verbose)?"True":"False") << std::endl;
    std::cout << "-i\t" << params.entero << std::endl;
    std::cout << "-f\t" << params.flotante << std::endl;
    std::cout << "-c\t" << '\"' << params.cadena << '\"' << std::endl;

    std::cout << "Hay " << argc-argObligados << " parámetros obligados que son: " << std::endl;

    for (int i = argObligados; i<argc; ++i)
      std::cout << '\"' << argv[i] << '\"' << std::endl;


    /*Ahora toca que tu rellenes con lo que hay que hacer ...*/

    
  }
  catch (std::exception& e)
  {
    std::cerr << "Capturada excepcion: " << e.what() << std::endl;
    retCode = EXIT_FAILURE;
  }
  return retCode;
}
