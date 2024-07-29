#include "Flexo.h"

Flexo::Flexo()
{   base_ry = 0;
    troncoSup_rx = 0;
    lampara_rx = 270;
    lampara_ry = 0;
    brazoRotaXDireccion, lampRotaXDireccion, lampRotaYDireccion = false;
}

/**
 * Destructor
 */
Flexo::~Flexo()
{
}

void Flexo::visualizaBase() {
    GLfloat verde[] = { 0,1,0,1.0 };
    glMaterialfv(GL_FRONT, GL_EMISSION, verde);
    glRotatef(base_ry, 0, 1, 0);
    glPushMatrix();
    glScalef(2.25, 0.5, 2.25);
    glutSolidCube(1);
    glPopMatrix();

}

void Flexo::visualizaTroncoInf() {
    GLfloat azul[] = { 0,0,1,1.0 };
    GLUquadricObj* cilindro = gluNewQuadric();
    GLUquadricObj* disco = gluNewQuadric();
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_EMISSION, azul);
    glTranslatef(0, 3.1, 0);
    glRotatef(-90, 1, 0, 0);
    gluDisk(disco, 0, 0.3, 32, 32);
    glPopMatrix();
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_EMISSION, azul);
    glTranslatef(0, 0.25, 0);
    glRotatef(-90, 1, 0, 0);
    gluCylinder(cilindro, 0.3, 0.3, 2.85, 32, 32);
    glPopMatrix();
    gluDeleteQuadric(cilindro);
    gluDeleteQuadric(disco);
}

void Flexo::visualizaTroncoSup() {
    GLfloat rojo[] = { 1,0,0,1.0 };
    GLUquadricObj* cilindro = gluNewQuadric();
    GLUquadricObj* disco = gluNewQuadric();
    glMaterialfv(GL_FRONT, GL_EMISSION, rojo);
    glTranslatef(0, 2.5, 0);
    glRotatef(troncoSup_rx, 1, 0, 0);
    gluCylinder(cilindro, 0.3, 0.3, 3.5, 32, 32);
    gluDisk(disco, 0, 0.3, 32, 32);
    gluDeleteQuadric(cilindro);
    gluDeleteQuadric(disco);
}

void Flexo::visualizaLampara() {
    GLfloat naranja[] = { 1, 0.35, 0, 1 };
    glMaterialfv(GL_FRONT, GL_EMISSION, naranja);
    glTranslatef(0, -0.5, 3.75);
    glRotatef(lampara_ry, 0, 1, 0);
    glRotatef(lampara_rx, 1, 0, 0);
    glutSolidCone(1, 1.5, 32, 32);
}


void Flexo::visualizaModelo() {
    glPushMatrix();
    //Base
    visualizaBase();
    glPushMatrix();
    //Brazo m�vil
    visualizaTroncoSup();
    glPushMatrix();
    //Lampara
    visualizaLampara();
    glPopMatrix();
    glPopMatrix();
    //Tronco
    visualizaTroncoInf();
    glPopMatrix();

}

////// Apartado C: a�adir aqu� los m�todos para modificar los grados de libertad del modelo
void Flexo::rotarBase(float ang) {
    base_ry += ang;
}

void Flexo::rotarBrazo(float ang) {
    if (troncoSup_rx + ang <= 25 && troncoSup_rx + ang >= -35) {
        troncoSup_rx += ang;
    }
}

void Flexo::rotarLamparaX(float ang) {
    if (lampara_rx + ang >= 220 && lampara_rx + ang <= 280) {
        lampara_rx += ang;
    }
}

void Flexo::rotarLamparaY(float ang) {
    if (lampara_ry + ang >= -35 && lampara_ry + ang <= 35) {
        lampara_ry += ang;
    }
}

void Flexo::animar() {
    if (troncoSup_rx + 1 > 25 || troncoSup_rx - 1 < -35) {
        brazoRotaXDireccion = !brazoRotaXDireccion;
    }
    if (lampara_rx - 1 < 220 || lampara_rx + 1 > 280) {
        lampRotaXDireccion = !lampRotaXDireccion;
    }
    if (lampara_ry - 1 < -35 && lampara_ry + 1 > 35) {
        lampRotaYDireccion = !lampRotaYDireccion;
    }

    rotarBase(1);

    if (brazoRotaXDireccion) {
        rotarBrazo(1);
    }
    else {
        rotarBrazo(-1);
    }

    if (lampRotaXDireccion) {
        rotarLamparaX(1);
    }
    else {
        rotarLamparaX(-1);
    }

    if (lampRotaYDireccion) {
        rotarLamparaY(1);
    }
    else {
        rotarLamparaY(-1);
    }

}


/**
 * M�todo con las llamadas OpenGL para visualizar la escena
 */
void Flexo::visualizar()
{  // crear luces
    GLfloat luz0[4] = { 5.0, 5.0, 5.0, 1 }; // luz puntual
    glLightfv(GL_LIGHT0, GL_POSITION, luz0); // la luz se coloca aqu� si permanece fija y no se mueve con la escena
    glEnable(GL_LIGHT0);

    // crear el modelo
    glPushMatrix(); // guarda la matriz de modelado

    //glLightfv(GL_LIGHT0,GL_POSITION,luz0); // la luz se coloca aqu� si se mueve junto con la escena (tambi�n habr�a que desactivar la de arriba).



    // TODO: Apartado B: aqu� hay que a�adir la visualizaci�n del �rbol del modelo utilizando la pila de matrices de OpenGL
    //       se recomienda crear una m�todo auxiliar que encapsule el c�digo para la visualizaci�n
    //       del modelo, dejando aqu� s�lo la llamada a ese m�todo, as� como distintas funciones una para cada
    //       parte del modelo.
    visualizaModelo();


    glPopMatrix(); // restaura la matriz de modelado
}