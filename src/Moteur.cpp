#include "Moteur.h"

Moteur::Moteur()
{
    m_fenetre = new sf::RenderWindow(sf::VideoMode(1600,900),"InterSemestre");
    m_fenetre->setFramerateLimit(60);
    m_Soleil = new Planet(333000,Eigen::Vector2d(0,0),Eigen::Vector2d(800,450),sf::Color::Yellow);
    vue = new sf::View(sf::Vector2f(800,450),sf::Vector2f(1600,900));
    //
    m_Astres[0] = m_Soleil;
    int quadrillage = 0;
    for(int i=1;i<100;i++)
    {
        if(quadrillage == 20)
            quadrillage = 0;
        m_Astres[i] = new Planet(1,Eigen::Vector2d(0,0),Eigen::Vector2d(int(i/20)*390,quadrillage*50),sf::Color::White);
        quadrillage++;
    }
    for(int i=1;i<100;i++)
    {
        Eigen::Vector2d V = (-m_Astres[0]->getPosition()+m_Astres[i]->getPosition())/((-m_Astres[0]->getPosition()+m_Astres[i]->getPosition()).norm());
        V = MatVi*V;
        V = V*2;
        m_Astres[i]->setVitesse(V);
    }
    for(int i=0;i<100;i++)
    {
        for(int j=0;j<100;j++)
        {
            m_potentiels[i][j] = Eigen::Vector2d(0,0);
        }
    }
    horloge.restart();
}
void Moteur::Run()
{
    while(m_fenetre->isOpen())
    {
        sf::Event event;
        while(m_fenetre->pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                m_fenetre->close();
            if(event.type = sf::Event::KeyPressed)
            {
                switch(event.key.code)
                {
                case sf::Keyboard::Up :
                    vue->zoom(0.9);
                    break;
                case sf::Keyboard::Down:
                    vue->zoom(1.1);
                    break;
                case sf::Keyboard::Right:
                    facteurTemps*=2;
                    break;
                case sf::Keyboard::Left:
                    facteurTemps/=2;
                    break;
                }
            }
        }
        ecoule = horloge.restart().asSeconds();
        Update(ecoule*facteurTemps);
        horloge.restart();
        vue->setCenter(m_Astres[0]->getPosition()(0),m_Astres[0]->getPosition()(1));
        m_fenetre->setView(*vue);
        m_fenetre->clear(sf::Color::Black);
        std::cout<<m_Astres[0]->getPosition()<<std::endl;
        for(int i=0;i<100;i++)
            m_fenetre->draw(*m_Astres[i]);
        m_fenetre->display();
    }
}
Moteur::~Moteur()
{
    delete m_fenetre;
    m_fenetre = 0;
}
void Moteur::Update(float ecoule)
{
    /*for(int i=0;i<100;i++)
    {
        for(int j=i+1;j<100;j++)
        {
            if((m_Astres[i]->getPosition()-m_Astres[j]->getPosition()).norm() < 21)
            {
                Eigen::Matrix2d M = Eigen::Rotation2Dd(3.14159/6).toRotationMatrix();
                m_Astres[i]->setVitesse(M*(-m_Astres[i]->getVitesse())/m_Astres[i]->getMasse());
                m_Astres[j]->setVitesse((M*(-m_Astres[j]->getVitesse()))/m_Astres[j]->getMasse());
            }
        }
    }*/
    for(int i=0;i<100;i++)
    {
        for(int j=0;j<100;j++)
        {
            if(i==j)
                continue;
            else
                 m_potentiels[i][j] = -G*m_Astres[j]->getMasse()*(-m_Astres[j]->getPosition()+m_Astres[i]->getPosition())/pow((-m_Astres[j]->getPosition()+m_Astres[i]->getPosition()).norm(),3);
            //Potentiel gravitationnel exerce par l'astre J au point ou I est
        }
    }
    for(int i=0;i<100;i++)
    {
        Eigen::Vector2d acceleration(0,0);
        Eigen::Vector2d vitesse(0,0);
        Eigen::Vector2d position(0,0);
        for(int j=0;j<100;j++)
        {
            if(i==j)
                continue;
            acceleration += m_potentiels[i][j];
        }
        vitesse = ecoule*acceleration + m_Astres[i]->getVitesse();
        position = (pow(ecoule,2)/2)*acceleration + (ecoule) * m_Astres[i]->getVitesse() + m_Astres[i]->getPosition();
        m_Astres[i]->setPosition(position);
        m_Astres[i]->setVitesse(vitesse);
        m_Astres[i]->setAcceleration(acceleration);
    }
}
