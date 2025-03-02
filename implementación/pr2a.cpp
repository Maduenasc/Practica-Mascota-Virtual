#include <cstdlib>

#include "igvInterfaz.h"

int main (int argc, char** argv)
{  // inicializa la ventana de visualizaci�n
   igvInterfaz::getInstancia().configura_entorno ( argc, argv
                                                   , 700,700 // tama�o de la ventana
                                                   , 100,100 // posici�n de la ventana
                                                   , "Mascota Virtual" // t�tulo de la ventana
   );

   // establece las funciones callback para la gesti�n de los eventos
   igvInterfaz::getInstancia().inicializa_callbacks();

   // inicia el bucle de visualizaci�n de OpenGL
   igvInterfaz::getInstancia().inicia_bucle_visualizacion();

   return(0);
}
