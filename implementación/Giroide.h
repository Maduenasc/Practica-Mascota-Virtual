#ifndef PR2A_GIROIDE_H
#define PR2A_GIROIDE_H

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else

#include <GL/glut.h>
#include <fstream>
#include <iostream>
#include <string>
#include <ctime>
#endif // defined(__APPLE__) && defined(__MACH__)

class Giroide {
    private:


        //Stats
        int saciedad;
        int energia;
        int limpieza;
        time_t ultimoTick;

        //Variables para controlar el movimiento del modelo
        bool activarAnimacion;			//Para activar animacion completa
        float angHombros;
        bool  auxHombros;
        float angBrazos;
        bool  auxBrazos;
        float angCuerpoEnX;
        bool  auxCuerpoEnX;
        float angCuerpoEnY;
        bool auxCuerpoEnY;

    public:
        // Constructores por defecto y destructor
        Giroide();
        Giroide(int saciedad, int energia, int limpieza);
        ~Giroide();

        //Getters
        int getSaciedad() {
            return saciedad;
        };
        
        int getEnergia() {
            return energia;
        };

        int getLimpieza() {
            return limpieza;
        };

        time_t getUltimoTick() {
            return ultimoTick;
        };

        void setUltimoTick(time_t _ultimoTick) {
            ultimoTick = _ultimoTick;
        };

        //Métodos para visualizar cada parte del modelo
        void dibujarGiroide();
        void dibujarBase();
        void dibujarTronco();
        void dibujarOjos();
        void dibujarBoca();
        void dibujarBrazos();

        //Funciones que actualizan las variables que hacen que se mueva el modelo
        void girarHombros(float angAumentar);
        void girarBrazo(float anfAumentar);
        void moverCuerpo(float angAumentar);
        void girarCuerpo(float angAumentar);
        void animacionCompleta();				//Función que realiza todas las animaciones a la vez
        void activarDesactivarAnimacion();		//Función que activa o desactiva el flag de animación completa

        //Funciones que actualizan los stats de la mascota
        void comer();               //Llamar a esta funcion para aumentar la saciedad en 33
        void dormir();              //Llamar a esta funcion para aumentar la energia al 100
        void limpiar();             //Llamar a esta funcion para aumentar la limpieza al 100
        void pasarTiempo(int n_ticks);         //Llamar a esta funcion cuando se quiera decrementar los stats por paso del tiempo
};


#endif //PR2A_GIROIDE_H
