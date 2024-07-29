#pragma once

#include <GL/glut.h>

/**
 * Partes del modelo
 */
enum parte
{
	basex   ///< Identifica la base del modelo
	, cuerpoinferior   ///< Identifica el cuerpo inferior del modelo
	, cuerposuperior   ///< Identifica el cuerpo superior del modelo
	, brazo   ///< Identifica el brazo del modelo
};

class Flexo
{
private:
	float base_ry;
	float troncoSup_rx;
	float lampara_ry, lampara_rx;
	bool brazoRotaXDireccion;
	bool lampRotaXDireccion, lampRotaYDireccion;

public:
    // Constructores por defecto y destructor
    Flexo();
    ~Flexo();

    // método con las llamadas OpenGL para visualizar la escena
    void visualizar();

    // TODO: Apartado B: Métodos para visualizar cada parte del modelo
    void visualizaBase();
    void visualizaTroncoInf();
    void visualizaTroncoSup();
    void visualizaLampara();
    void visualizaModelo();


    // TODO: Apartado C: añadir aquí los métodos para modificar los grados de libertad del modelo
    void rotarBase(float ang);
    void rotarBrazo(float ang);
    void rotarLamparaX(float ang);
    void rotarLamparaY(float ang);
    void animar();
};

