#ifndef MOTEUR_H
#define MOTEUR_H

#include <SFML/Graphics.hpp>7
#include "Planet.h"
#include <cmath>
#include <iostream>

class Moteur
{
    public:
        Moteur();
        ~Moteur();
        void Run();
    private:
        void Update(float ecoule);
        void uMatrice();
        //
        sf::RenderWindow *m_fenetre;
        Planet *m_Astres[100];
        Planet *m_Soleil;
        Eigen::Vector2d m_potentiels[100][100];
        sf::Clock horloge;
        sf::View *vue;
        float G = 6.67*pow(10,-3);
        float ecoule = 0;
        float facteurTemps = 1;
        Eigen::Matrix2d MatVi = Eigen::Rotation2Dd(3.14159/2).toRotationMatrix();
};


#endif // MOTEUR_H
