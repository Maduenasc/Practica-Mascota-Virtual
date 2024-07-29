#include "igvTextura.h"

#include <vector>
#include <stdexcept>
#include "bmp.h"

// Métodos constructores y destructor

/**
 * Constructor parametrizado. Carga una textura de archivo
 * @param fichero
 */
igvTextura::igvTextura ( char *fichero)
{
    GLubyte *imagen;

    imagen = loadBMPRaw(fichero, alto, ancho, true);


      // TODO: Apartado F: Añadir aquí el código para cargar como textura OpenGL la imagen */
      //	- Generar el identificador de textura y asignarlo al atributo idTextura (glGenTextures)
        glGenTextures(1, &idTextura);
      //	- Enlazar el identificador creado a GL_TEXTURE_2D (glBindTexture)
       glBindTexture(GL_TEXTURE_2D, idTextura);
      //  - Especificar la textura, asignádole como textura el array imagen (glTexImage2D)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, ancho, alto, 0, GL_RGB, GL_UNSIGNED_BYTE, imagen);
      //  - Modo de aplicación de la textura (glTexEnvf)
       glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
      //	- Parámetros de la textura: repetición y filtros (glTexParameteri)
       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

}

/**
 * Destructor. Elimina la textura OpenGL relacionada
 */
igvTextura::~igvTextura ()
{  glDeleteTextures ( 1, &idTextura );
}

/**
 * Activa la textura OpenGL relacionada
 */
void igvTextura::aplicar ()
{  glBindTexture ( GL_TEXTURE_2D, idTextura );
}

/**
 * Cambia el identificador de la textura OpenGL relacionada
 * @param id Nuevo identificador de texturas
 * @pre Se asume que el parámetro es válido
 * @post El identificador de la textura OpenGL cambia
 */
void igvTextura::setIdTextura ( unsigned int id )
{  this->idTextura = id;
}

/**
 * Consulta del identificador de la textura OpenGL
 * @return El identificador de la textura OpenGL relacionada
 */
unsigned int igvTextura::getIdTextura ()
{  return this->idTextura;
}
