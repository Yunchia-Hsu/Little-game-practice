#ifndef GAME_H
# define GAME_H

#include <vector>
#include <ctime>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

/*
    classs that acts as the game engine
*/
class Game 
{
    protected:
        sf::RenderWindow *window;
        sf::Event event;
        sf::VideoMode videoMode;
        
        //game logic
        float enemySpawnTimer;
        float enemySpawntimerMax;
        int maxEnemies;
        int point;

        //game objects
        std::vector < sf::RectangleShape> enemies;
        sf::RectangleShape enemy;
        //mouse position
        sf::Vector2i mousePosWinow;

        void initenemies();
        void initVariables();
        void initWindow();
    public:
        //constructors / destructors
        Game();
        virtual ~Game();

        //Functions
        void spawnEnemy();

        void update();
        void updateEnemies();

        void render();
        void renderEnemies();
        
        void pollEvents();
        void updateMousePos();
       

        //accessors
        const bool running() const;


};











#endif