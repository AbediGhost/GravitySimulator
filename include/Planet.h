#ifndef PLANET_H
#define PLANET_H

#include <SFML/Graphics.hpp>
#include <Eigen/Dense>
#include <cmath>

class Planet : public sf::Drawable
{
    public:
        Planet(float masse,Eigen::Vector2d vitesse,Eigen::Vector2d position,sf::Color color);
        virtual void draw(sf::RenderTarget &target, sf::RenderStates state) const;
        void setVitesse(Eigen::Vector2d vitesse);
        Eigen::Vector2d getVitesse();
        void setAcceleration(Eigen::Vector2d acceleration);
        Eigen::Vector2d getAcceleration();
        void setPosition(Eigen::Vector2d position);
        Eigen::Vector2d getPosition();
        float getMasse();
        sf::CircleShape* getCircle();
    private:
        Eigen::Vector2d m_vitesse;
        Eigen::Vector2d m_acceleration;
        Eigen::Vector2d m_position;
        sf::CircleShape *m_cercle;
        float m_masse;

};

#endif // PLANET_H
