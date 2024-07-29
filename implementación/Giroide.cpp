#include "Giroide.h"
#include <cstdlib>
#include <stdio.h>
#include <stdio.h>


// Métodos constructores
/**
 * Constructor por defecto
 * 
 * Los stats se leen y almacenan en un fichero para que estos tengan permanencia entre ejecuciones del programa
 */
 Giroide::Giroide(){
    //Inicializamos los stats de la mascota
     std::ifstream stats("giroide_stats.txt");
     std::string linea;
     stats >> linea;
     this->saciedad = atoi(linea.c_str());
     //printf("%i", linea.c_str());
     stats >> linea;
     this->energia = atoi(linea.c_str());
     //printf("%i", linea.c_str());
     stats >> linea;
     this->limpieza = atoi(linea.c_str());
     //printf("%i", linea.c_str());
     stats >> linea;
     this->ultimoTick = atoi(linea.c_str());
     //printf("%i", linea.c_str());

     if(time(NULL) - ultimoTick >= 10) {
         int n_ticks = (time(NULL) - ultimoTick) / 10;
         pasarTiempo(n_ticks);
         ultimoTick = time(NULL);

     }

    //Inicializamos los atributos para el control de los grados de libertad del modelo
    activarAnimacion = true;
    angHombros = 0;
    auxHombros = false;
    angCuerpoEnX = 0;
    auxCuerpoEnX = false;
    angCuerpoEnY = 0;
    auxCuerpoEnY = false;
 }

Giroide::Giroide (int saciedad, int energia, int limpieza)
{
    //Inicializamos los stats de la mascota
    this->saciedad = saciedad;
    this->energia = energia;
    this->limpieza = limpieza;

    //Inicializamos los atributos para el control de los grados de libertad del modelo
    activarAnimacion = true;
    angHombros = 0;
    auxHombros = false;
    angCuerpoEnX = 0;
    auxCuerpoEnX = false;
    angCuerpoEnY = 0;
    auxCuerpoEnY = false;

}

/**
 * Destructor
 */
Giroide::~Giroide ()
{
}

//Reduce los stats del giroide segun el tiempo. Si el programa se inicia de 0, se calcula los ticks que han ocurrido mientras el programa estaba apagado
//y se reducen los stats del giroide en consecuencia
void Giroide::pasarTiempo(int n_ticks){
    (this->saciedad - 5*n_ticks) <= 1 ? this->saciedad = 1 : this->saciedad -= 5 * n_ticks;
    (this->energia - 7 * n_ticks) <= 1 ? this->energia = 1 : this->energia -= 7 * n_ticks;
    (this->limpieza - 3 * n_ticks) <= 1 ? this->limpieza = 1 : this->limpieza -= 3 * n_ticks;

    std::ofstream w_stats("giroide_stats.txt");
    w_stats << this->saciedad << "\n" << this->energia << "\n" << this->limpieza << "\n" << time(NULL);
    w_stats.close();
}

//Incrementa la saciedad del giroide, que controla la velocidad de su animacion
void Giroide::comer() {
    std::ofstream w_stats("giroide_stats.txt");

    if(this->saciedad + 33 >= 100){
        this->saciedad = 100;
    }else{
        this->saciedad += 33;
    }
    w_stats << this->saciedad << "\n" << this->energia << "\n" << this->limpieza << "\n" << time(NULL);

    w_stats.close();
}

//Incrementa la energia del giroide, que controla la iluminacion de la sala
void Giroide::dormir() {
    std::ofstream w_stats("giroide_stats.txt");
    this->energia = 100;

    w_stats << this->saciedad << "\n" << this->energia << "\n" << this->limpieza << "\n" << time(NULL);
    w_stats.close();
}

void Giroide::limpiar() {
    std::ofstream w_stats("giroide_stats.txt");
    this->limpieza = 100;

    w_stats << this->saciedad << "\n" << this->energia << "\n" << this->limpieza << "\n" << time(NULL);
    w_stats.close();
}

//FUNCIÓN QUE DIBUJA EL GIROIDE, DONDE SE APRECIA LA ESTRUCTURA DE ARBOL
void Giroide::dibujarGiroide() {


    GLfloat cuerpo[] = { 0.72, 0.45, 0.20, 1 };
    GLfloat ojosBoca[] = { 0, 0, 0, 1 };
    GLfloat base[] = { 1, 0.25, 0, 1 };


    glPushMatrix();

    glMaterialfv(GL_FRONT, GL_EMISSION, base);
    dibujarBase();
    glPushMatrix();

    glMaterialfv(GL_FRONT, GL_EMISSION, cuerpo);
    glRotatef(angCuerpoEnY, 0, 1, 0);
    glRotatef(angCuerpoEnX, 1, 0, 0);
    dibujarTronco();
    glPushMatrix();

    dibujarBrazos();

    glPopMatrix();
    glPushMatrix();

    glMaterialfv(GL_FRONT, GL_EMISSION, ojosBoca);
    dibujarOjos();

    glPopMatrix();
    glPushMatrix();

    glMaterialfv(GL_FRONT, GL_EMISSION, ojosBoca);
    dibujarBoca();

    glPopMatrix();
    glPopMatrix();

    glPopMatrix();
}

//FUNCIÓN QUE DIBUJA LA BASE DE LA ESTRUCTURA
void Giroide::dibujarBase() {
    //Base cúbica
    glScalef(1.1, 0.20, 1.1);
    glutSolidCube(2);
}

//FUNCIÓN QUE DIBUJA TODAS LAS PARTES DEL TRONCO, Y EL GORRO
void Giroide::dibujarTronco() {

    //Tronco como tal
    GLUquadricObj* quadratic;
    quadratic = gluNewQuadric();
    glRotatef(-90, 1, 0, 0);
    glScalef(1, 1, 5);
    gluCylinder(quadratic, 1, 1, 2, 30, 5);

    //GORRO
    glPushMatrix();
    GLfloat gorro[] = { 1, 0.6, 0, 1 };
    glMaterialfv(GL_FRONT, GL_EMISSION, gorro);
    quadratic = gluNewQuadric();
    glTranslatef(0, 0, 2.3);
    glScalef(1.1, 1.1, 0.7);
    gluCylinder(quadratic, 1.1, 0.1, 2, 30, 5);

    //DETALLES DEL GORRO
    glPushMatrix();
    GLfloat gorro2[] = { 0, 1, 0, 1 };
    glMaterialfv(GL_FRONT, GL_EMISSION, gorro2);
    glTranslatef(0, 0, 0.2);
    glScalef(1, 1, 0.2);
    gluCylinder(quadratic, 1.1, 0.11, 3, 30, 1);
    glPopMatrix();
    glPushMatrix();
    GLfloat gorro3[] = { 1, 0.6, 0, 1 };
    glMaterialfv(GL_FRONT, GL_EMISSION, gorro3);
    quadratic = gluNewQuadric();
    glTranslatef(0, 0, 0.5);
    gluSphere(quadratic, 1, 50, 50);
    glPopMatrix();
    glPopMatrix();

    //Tapa esférica arriba
    GLfloat cuerpo[] = { 0.72, 0.45, 0.20, 1 };
    glMaterialfv(GL_FRONT, GL_EMISSION, cuerpo);
    quadratic = gluNewQuadric();
    glTranslatef(0, 0, 2);
    gluSphere(quadratic, 1, 50, 50);

}

//FUNCIÓN QUE DIBUJA LOS OJOS
void Giroide::dibujarOjos() {

    //Ojos
    //Ojo izq
    glTranslatef(0.8, 0.3, -0.3);
    glutSolidCube(0.35);
    //Ojo der
    glTranslatef(0, -0.6, 0);
    glutSolidCube(0.35);
}

//FUNCIÓN QUE DIBUJA LA BOCA
void Giroide::dibujarBoca() {

    //Boca
    glTranslatef(0.85, 0, -1);
    glScalef(1, 2, 0.5);
    glutSolidCube(0.35);
}

//FUNCIÓN QUE DIBUJA LOS HOMBROS Y LOS BRAZOS DEL MODELO
void Giroide::dibujarBrazos() {

    //Brazo izquierdo
    glPushMatrix();
    //Brazo izq parte 1
    glTranslatef(0, -1.5, -0.5);
    glScalef(0.3, 1, 0.3);
    glRotatef(-angHombros, 0, 1, 0);
    glutSolidCube(1);

    glPushMatrix();
    //Brazo izq parte 2
    glRotatef(-angBrazos, 1, 0, 0);
    glTranslatef(0, -0.5, -1.5);
    glScalef(1, 0.3, 4);
    glutSolidCube(1);
    glPopMatrix();
    glPopMatrix();


    //Brazo derecho
    glPushMatrix();
    //Brazo der parte 1
    glTranslatef(0, 1.5, -0.5);
    glScalef(0.3, 1, 0.3);
    glRotatef(angHombros, 0, 1, 0);
    glutSolidCube(1);

    glPushMatrix();
    //Brazo der parte 2
    glRotatef(-angBrazos, 1, 0, 0);
    glTranslatef(0, 0.5, 1.5);
    glScalef(1, 0.3, 4);
    glutSolidCube(1);
    glPopMatrix();
    glPopMatrix();
}


//FUNCIÓN PARA GIRAR LOS HOMBROS HASTA 180 GRADOS Y DESPUÉS GIRARLOS EN DIRECCIÓN CONTRARIA 180 GRADOS (se autocontrola cuando llega al límite)
void Giroide::girarHombros(float angAumentar) {

    //El angMax deberia ser 180 pero con 190 parece más fluido
    float angMax = 190;

    if (angHombros < angMax && auxHombros) {

        angHombros += angAumentar;

        if (angHombros >= angMax) {
            auxHombros = !auxHombros;
        }
    }
    else{

        angHombros -= angAumentar;

        //La condición debería ser <= 0 pero con -20 parece más fluido
        if (angHombros <= -20) {
            auxHombros = !auxHombros;
        }
    }
}

//FUNCIÓN PARA GIRAR LOS BRAZOS HASTA 20 GRADOS Y DESPUÉS GIRARLOS EN DIRECCIÓN (se autocontrola cuando llega al límite)
void Giroide::girarBrazo(float angAumentar) {

    float angMax = 20;

    if (angBrazos < angMax && auxBrazos) {

        angBrazos += angAumentar;

        if (angBrazos >= angMax) {
            auxBrazos = !auxBrazos;
        }
    }
    else {

        angBrazos -= angAumentar;

        if (angBrazos <= 0) {
            auxBrazos = !auxBrazos;
        }
    }
}

//FUNCIÓN PARA LADEAR EL CUERPO HACIA LOS LADOS, HASTA UN CIERTO LÍMITE
void Giroide::moverCuerpo(float angAumentar) {

    float angMax = 3.5;

    if (angCuerpoEnX < angMax && auxCuerpoEnX) {

        angCuerpoEnX += angAumentar;

        if (angCuerpoEnX >= angMax) {
            auxCuerpoEnX = !auxCuerpoEnX;
        }
    }
    else {

        angCuerpoEnX -= angAumentar;

        if (angCuerpoEnX <= -angMax) {

            auxCuerpoEnX = !auxCuerpoEnX;
        }
    }
}

//FUNCIÓN PARA ROTAR EL CUERPO SOBRE SÍ MISMO EN EL EJE VERTICAL
void Giroide::girarCuerpo(float angAumentar) {

    angCuerpoEnY += angAumentar;
}

//FUNCIÓN QUE COMPRUEBA SI SE HA PULSADO LA TECLA PARA ANIMAR EL MODELO COMPLETO
void Giroide::animacionCompleta() {

    //Si la tecla se pulsó, se anima automáticamente el modelo
    if (activarAnimacion) {
        Sleep(3);

        //Sin modificador de velocidad de mientras solucionamos lo de abajo
        //girarHombros(8);
        //girarCuerpo(1);
        //girarBrazo(2);
        //moverCuerpo(0.2);

        //NO FUNCIONA TODAVIA. Porque no se leen bien los stats del .txt y asigna valores = 0
        girarHombros(8 * (float)((float)this->saciedad/100));
        girarCuerpo(1 * (float)((float)this->saciedad/100));
        girarBrazo(2 * (float)((float)this->saciedad/100));
        moverCuerpo(0.2 * (float)((float)this->saciedad/100));
    }
}

//ACTIVA O DESACTIVA EL FLAG DE ANIMACIÓN COMPLETA
void Giroide::activarDesactivarAnimacion() {

    activarAnimacion ? activarAnimacion = false : activarAnimacion = true;
}
