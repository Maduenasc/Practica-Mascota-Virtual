#include <cstdlib>
#include <stdio.h>

#include "igvEscena3D.h"
#include "igvTextura.h"

// Métodos constructores -----------------------------------

// Métodos públicos ----------------------------------------

/**
 * Método con las llamadas OpenGL para visualizar la escena
 * @param escena Identificador del tipo de escena a dibujar
 * @pre Se asume que el valor del parámetro es correcto
 */
void igvEscena3D::visualizar ( int escena )
{  // borra la ventana y el Z-buffer
   glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );


   //Si el giroide no está "cansado" se enciende una luz en toda la sala, si la energia baja por debajo de un cierto margen (30), en su lugar se
   //enciende una luz focal en el flexo, simulando que es de noche y necesita dormir.
   if(giroide.getEnergia() > 30) {
       glDisable(GL_LIGHT1);
   //Luces
    GLfloat light0[] = { 10, 8, 9, 1 };
   //GLfloat light0[] = { 0, 0, 0, 1 }; // point light source
   glLightfv ( GL_LIGHT0, GL_POSITION, light0 );
   glEnable ( GL_LIGHT0 );
   } else {

   glDisable(GL_LIGHT0);
   igvPunto3D posicion(-3, 1.75, -3);
   igvColor ambiental(0.0, 0.0, 0.0, 1.0);
   igvColor difuso(1.0, 1.0, 1.0, 1.0);
   igvColor especular(1.0, 1.0, 1.0, 1.0);

   igvPunto3D pos(-2.5, 2, -3);
   igvPunto3D dir(0, -1, 0);
   igvFuenteLuz foco(GL_LIGHT1, pos, ambiental, difuso, especular, 1.0, 0.0, 0.0, dir, 91, 0);
   foco.aplicar();
}
   glPushMatrix (); // guarda la matriz de modelado

   Flexo _flexo;

       dibujarHabitacion(_flexo);

       glPushMatrix();
            glTranslatef(0, 0.2, 0);
            glScalef(0.3, 0.3, 0.3);
            glRotatef(-90, 0, 1, 0);
            giroide.dibujarGiroide();
       glPopMatrix();

   glPopMatrix (); // restaura la matriz de modelado
   std::string saciedad = "Saciedad: " +  std::to_string(giroide.getSaciedad());
   glColor3f(1, 0, 0);
   escribirPorPantalla(saciedad, saciedad.size(), 100, 550);
   std::string energia = "Energia: " + std::to_string(giroide.getEnergia());
   glColor3f(1, 0, 0);
   escribirPorPantalla(energia, energia.size(), 300, 550);
   std::string limpieza = "Limpieza: " + std::to_string(giroide.getLimpieza());
   glColor3f(1, 0, 0);
   escribirPorPantalla(limpieza, limpieza.size(), 500, 550);

   if (time(NULL) > giroide.getUltimoTick() + 10) {
       giroide.pasarTiempo(1);
       giroide.setUltimoTick(time(NULL));
       // You can also do other things here like trigger a sound effect etc.
   }

   dibujarSuciedad();
   glutSwapBuffers (); // se utiliza, en vez de glFlush(), para evitar el parpadeo
}

void igvEscena3D::escribirPorPantalla(const std::string& texto, int tam, int x, int y) {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, 800, 0, 600, -5, 5);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glColor3f(1, 0, 0);
    glRasterPos2i(x, y);
    for (const char c : texto) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, (int)c);
    }
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

}

void igvEscena3D::dibujarHabitacion(Flexo _flexo){

    glPushMatrix();
        glScalef(0.5, 0.5, 0.5);
        dibujarParedesYSuelo();

        glPushMatrix();
            glTranslatef(-3, 0, -3);
            glScalef(0.5, 0.5, 0.5);
            dibujarMesa();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(-3, 1.75, -3);
            glScalef(0.5, 0.5, 0.5);
            _flexo.visualizaModelo();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(4, 0, 4);
            glScalef(0.35, 0.4, 0.3);
            dibujarSilla();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0, 0.3, 0);
            glScalef(0.5, 0.5, 0.5);
            dibujarAlfombra();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(1, 2.8, -4.5);
            glScalef(1, 1, 1);
            dibujarVentana();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(-4.5, 2.8, 1);
            glRotatef(90, 0, 1, 0);
            dibujarCuadro();
        glPopMatrix();

    glPopMatrix();
}

void igvEscena3D::dibujarParedesYSuelo(){
    //Suelo
    glPushMatrix();
        GLfloat suelo[] = { 0.4, 0.1, 0.2, 1 };
        glMaterialfv(GL_FRONT, GL_EMISSION, suelo);
        glTranslatef(0, 0, 0);
        glScalef(10, 0.5, 10);
        glutSolidCube(1);
    glPopMatrix();

    //Paredes
    glPushMatrix();
    GLfloat pared[] = { 0.4, 0.2, 0.1, 1 };
    glMaterialfv(GL_FRONT, GL_EMISSION, pared);
        glTranslatef(0, 2.3, -5);
        glScalef(10, 5.14, 0.6);
        glutSolidCube(1);
    glPopMatrix();
    //glPushMatrix();
        //glTranslatef(0, 0, 5);
        //glScalef(10, 10, 0.5);
        //glutSolidCube(1);
    //glPopMatrix();
    glPushMatrix();
        glTranslatef(-5, 2.3, 0);
        glScalef(0.6, 5.14, 10);
        glutSolidCube(1);
    glPopMatrix();
    //glPushMatrix();
        //glTranslatef(5, 0, 0);
        //glScalef(0.5, 10, 10);
        //glutSolidCube(1);
    //glPopMatrix();
}

void igvEscena3D::dibujarMesa(){

    //Tablero
    glPushMatrix();
    GLfloat mesa[] = { 0.3, 0.2, 0.1, 1 };
    glMaterialfv(GL_FRONT, GL_EMISSION, mesa);
        glTranslatef(0, 3, 0);
        glScalef(5, 0.5, 5);
        glutSolidCube(1);
    glPopMatrix();

    //Pata 1
    glPushMatrix();
        glTranslatef(2, 1.5, 2);
        glScalef(0.5, 3.5, 0.5);
        glutSolidCube(1);
    glPopMatrix();

    //Pata 2
    glPushMatrix();
        glTranslatef(-2, 1.5, -2);
        glScalef(0.5, 3.5, 0.5);
        glutSolidCube(1);
    glPopMatrix();

    //Pata 3
    glPushMatrix();
        glTranslatef(2, 1.5, -2);
        glScalef(0.5, 3.5, 0.5);
        glutSolidCube(1);
    glPopMatrix();

    //Pata 4
    glPushMatrix();
        glTranslatef(-2, 1.5, 2);
        glScalef(0.5, 3.5, 0.5);
        glutSolidCube(1);
    glPopMatrix();

}

void igvEscena3D::dibujarSilla(){

    //Dibujamos una mesa como base de la silla (en esencia es lo mismo, reutilizamos código)
    glPushMatrix();
        dibujarMesa();
    glPopMatrix();

    //Respaldo de la silla
    glPushMatrix();
        glTranslatef(2.5, 5.5, 0);
        glScalef(0.5, 5, 5);
        glutSolidCube(1);
    glPopMatrix();
}

void igvEscena3D::dibujarVentana(){

    //Parte trasera
    glPushMatrix();
    GLfloat cielo[] = { 0.2, 0.2, 1, 1 };
    glMaterialfv(GL_FRONT, GL_EMISSION, cielo);
        glTranslatef(0, 0, 0);
        glRotatef(0, 0, 0, 0);
        glScalef(4, 3, 0.2);
        glutSolidCube(1);
    glPopMatrix();

    //Marco de la ventana
    glPushMatrix();
    GLfloat marco_ventana[] = { 0.2, 0.2, 0.2, 1 };
    glMaterialfv(GL_FRONT, GL_EMISSION, marco_ventana);
        glTranslatef(0, 0, 0.1);
        glRotatef(0, 0, 0, 0);
        glScalef(0.3, 3, 0.3);
        glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0, 0, 0.1);
        glRotatef(0, 0, 0, 0);
        glScalef(4, 0.3, 0.4);
        glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(1.9, 0, 0.1);
        glRotatef(0, 0, 0, 0);
        glScalef(0.3, 3, 0.4);
        glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(-1.9, 0, 0.1);
        glRotatef(0, 0, 0, 0);
        glScalef(0.3, 3, 0.4);
        glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0, 1.4, 0.1);
        glRotatef(0, 0, 0, 0);
        glScalef(4, 0.3, 0.4);
        glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0, -1.4, 0.1);
        glRotatef(0, 0, 0, 0);
        glScalef(4, 0.3, 0.4);
        glutSolidCube(1);
    glPopMatrix();
}

void igvEscena3D::dibujarAlfombra(){
    glPushMatrix();
    GLfloat alfombra[] = { 1, 0, 0, 1 };
    glMaterialfv(GL_FRONT, GL_EMISSION, alfombra);
        glTranslatef(0, 0, 0);
        glScalef(10, 0.1, 10);
        glutSolidCube(1);
    glPopMatrix();
}
void igvEscena3D::pintar_quad ()
{  	float ini_x = 0.0;
    float ini_z = 0.0;
    float fin_x = 5.0;
    float fin_z = 5.0;
    float tam_x = (fin_x - ini_x);
    float tam_z = (fin_z - ini_z);
    float divisionX = 1;
    float divisionZ = 1;
    float sumaX = 0;
    float sumaZ = 0;

    glNormal3f(0, 1, 0);
    glBegin(GL_QUADS);
    for (float i = ini_x; i < fin_x; i += tam_x)
    {
        sumaX += divisionX;
        sumaZ = 0;
        for (float j = ini_z; j < fin_z; j += tam_z)
        {
            glTexCoord2f(sumaX, sumaZ);
            glVertex3f(i, 0.0, j);

            glTexCoord2f(sumaX, sumaZ + divisionZ);
            glVertex3f(i, 0.0, j + tam_z);

            glTexCoord2f(sumaX + divisionX, sumaZ + divisionZ);
            glVertex3f(i + tam_x, 0.0, j + tam_z);

            glTexCoord2f(sumaX + divisionX, sumaZ);
            glVertex3f(i + tam_x, 0.0, j);

            sumaZ += divisionZ;
        }
    }
    glEnd();
}

void igvEscena3D::dibujarCuadro(){

    /*char fichero[] = "./imagen_cuadro.bmp";
    igvTextura textura(fichero);
    textura.aplicar();

        float dimX = 4;
        float dimY = 3;
        float dimZ = 0.2;
        float x = 0;
        float y= 0;
        float z=0;
        //QUAD PARA DIBUJAR LOS CUADROS SOBRE LOS MARCOS
        glPushMatrix();
            glBegin(GL_QUADS);
            glTexCoord3f(x + dimX / 2, y + dimY / 2, z + dimZ / 2 + 0.001);
            glVertex3f(x + dimX / 2, y + dimY / 2, z + dimZ / 2 + 0.001);		//ARRIBA DER

            glTexCoord3f(x + dimX / 2, y - dimY / 2, z + dimZ / 2 + 0.001);
            glVertex3f(x + dimX / 2, y - dimY / 2, z + dimZ / 2 + 0.001);		//ARRIBA IZQ

            glTexCoord3f(x - dimX / 2, y - dimY / 2, z + dimZ / 2 + 0.001);
            glVertex3f(x - dimX / 2, y - dimY / 2, z + dimZ / 2 + 0.001);		//ABAJO IZQ

            glTexCoord3f(x - dimX / 2, y + dimY / 2, z + dimZ / 2 + 0.001);
            glVertex3f(x - dimX / 2, y + dimY / 2, z + dimZ / 2 + 0.001);		//ABAJO DER
            glEnd();
        glPopMatrix();
    */

    //Marco del cuadro
    glPushMatrix();
        glTranslatef(1.9, 0, 0.2);
        glRotatef(0, 0, 0, 0);
        glScalef(0.2, 3, 0.2);
        glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(-1.9, 0, 0.2);
        glRotatef(0, 0, 0, 0);
        glScalef(0.2, 3, 0.2);
        glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0, 1.4, 0.2);
        glRotatef(0, 0, 0, 0);
        glScalef(4, 0.2, 0.2);
        glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0, -1.4, 0.2);
        glRotatef(0, 0, 0, 0);
        glScalef(4, 0.2, 0.2);
        glutSolidCube(1);
    glPopMatrix();
}

void igvEscena3D::actualizaGiroide(int indice) {
    switch (indice) {
    case 1: // alimentar
        giroide.comer();
        break;
    case 2: // descansar
        giroide.dormir();
        break;
    case 3: // limpiar
        giroide.limpiar();
        break;
    case 4: // reducir stats
        giroide.pasarTiempo(1);
    }

}

//Esta funcion se encarga de dibujar por pantalla grafos de escena para representar suciedad cuando la limpieza de la mascota virtual es baja
void igvEscena3D::dibujarSuciedad() {

    GLfloat marron[] = { 0.3608, 0.2, 0.0392, 1 };
    glMaterialfv(GL_FRONT, GL_EMISSION, marron);

    if (giroide.getLimpieza() < 70) {

        glPushMatrix();
        glTranslatef(2.5, 0.5, 1);
        glPushMatrix();
        glTranslatef(0, 0, 0);
        glScalef(0.5, 0.2, 0.5);
        glutSolidCube(1);
        glPopMatrix();
        glPushMatrix();
        glTranslatef(0, 0.18, 0);
        glScalef(0.25, 0.1, 0.25);
        glutSolidCube(1);
        glPopMatrix();
        glPushMatrix();
        glTranslatef(0, 0.28, 0);
        glScalef(0.1, 0.05, 0.1);
        glutSolidCube(1);
        glPopMatrix();
        glPopMatrix();
    }
    if (giroide.getLimpieza() < 50) {

        glPushMatrix();
        glTranslatef(0, 0.5, 2);

        glPushMatrix();
        glTranslatef(0, 0, 0);
        glScalef(0.5, 0.2, 0.5);
        glutSolidCube(1);
        glPopMatrix();
        glPushMatrix();
        glTranslatef(0, 0.18, 0);
        glScalef(0.25, 0.1, 0.25);
        glutSolidCube(1);
        glPopMatrix();
        glPushMatrix();
        glTranslatef(0, 0.28, 0);
        glScalef(0.1, 0.05, 0.1);
        glutSolidCube(1);
        glPopMatrix();
        glPopMatrix();
    }
    if (giroide.getLimpieza() < 20) {
        glPushMatrix();
        glTranslatef(0, 0.5, -1);
        glPushMatrix();
        glTranslatef(0, 0, 0);
        glScalef(0.5, 0.2, 0.5);
        glutSolidCube(1);
        glPopMatrix();
        glPushMatrix();
        glTranslatef(0, 0.18, 0);
        glScalef(0.25, 0.1, 0.25);
        glutSolidCube(1);
        glPopMatrix();
        glPushMatrix();
        glTranslatef(0, 0.28, 0);
        glScalef(0.1, 0.05, 0.1);
        glutSolidCube(1);
        glPopMatrix();
        glPopMatrix();
    }

}
