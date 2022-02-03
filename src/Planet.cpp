#include "Planet.h"

Planet::Planet(float masse,Eigen::Vector2d vitesse,Eigen::Vector2d position,sf::Color color)
{
    m_masse = masse;
    m_vitesse = vitesse;
    m_position = position;
    m_cercle = new sf::CircleShape(10);
    m_cercle->setPosition(m_position(0),m_position(1));
    m_cercle->setFillColor(color);
}

Eigen::Vector2d Planet::getAcceleration()
{
    return m_acceleration;
}
Eigen::Vector2d Planet::getVitesse()
{
    return m_vitesse;
}
void Planet::setVitesse(Eigen::Vector2d vitesse)
{
    m_vitesse = vitesse;
}
void Planet::setAcceleration(Eigen::Vector2d acceleration)
{
    m_acceleration = acceleration;
}
void Planet::setPosition(Eigen::Vector2d position)
{
    m_position = position;
    m_cercle->setPosition(position(0),position(1));
}
Eigen::Vector2d Planet::getPosition()
{
    return m_position;
}
float Planet::getMasse()
{
    return m_masse;
}
void Planet::draw(sf::RenderTarget &target, sf::RenderStates state) const
{
    target.draw(*m_cercle,state);
}
