#ifndef __IGVESCENA3D
#define __IGVESCENA3D

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#endif   // defined(__APPLE__) && defined(__MACH__)

#include "Giroide.h"
#include "Flexo.h"
#include "igvColor.h"
#include "igvPunto3D.h"
#include "igvFuenteLuz.h"
#include <string>
#include <ctime>

/**
 * Los objetos de esta clase representan escenas 3D para su visualización
 */
class igvEscena3D
{
    public:
      const int EscenaA = 1;   ///< Identificador interno de la escena A
      const int EscenaB = 2;   ///< Identificador interno de la escena B
      const int EscenaC = 3;   ///< Identificador interno de la escena C

      const char *Accion_n1 = "Alimentar";   ///< Etiqueta de la escena A
      const char *Accion_n2 = "Dormir";   ///< Etiqueta de la escena B
      const char* Accion_n3 = "Limpiar";   ///< Etiqueta de la escena C

      // Constructores por defecto y destructor
      /// Constructor por defecto
      igvEscena3D() = default;
      /// Destructor
      ~igvEscena3D() = default;

      // Métodos
      // método con las llamadas OpenGL para visualizar la escena
      void visualizar ( int escena );

      void actualizaGiroide(int indice);
      Giroide giroide = Giroide();
    private:
        // Atributos

        DWORD ultimoTick = GetTickCount();

        // métodos para dibujar el entorno
        void dibujarHabitacion(Flexo _flexo);
        void dibujarParedesYSuelo();
        void dibujarMesa();
        void dibujarSilla();
        void dibujarVentana();
        void dibujarAlfombra();
        void dibujarCuadro();
        void escribirPorPantalla(const std::string& texto, int tam, int x, int y);
        void dibujarSuciedad();

        void pintar_quad();
};

#endif   // __IGVESCENA3D
