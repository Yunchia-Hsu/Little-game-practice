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
#include <sstream>

/*
    classs that acts as the game engine
*/
class Game 
{
    protected:
        sf::RenderWindow *window;
        sf::Event event;
        sf::VideoMode videoMode;
        
        //resources
        sf::Font font;

        //text
        sf::Text uiText;

        //game logic
        float enemySpawnTimer;
        float enemySpawntimerMax;
        int maxEnemies;
        unsigned points;
        bool mouseHeld;
        int health;
        bool endgame;

        //game objects
        std::vector < sf::RectangleShape> enemies;
        sf::RectangleShape enemy;

        //mouse position
        sf::Vector2i mousePosWinow;
        sf::Vector2f mousePosView;

        void initenemies();
        void initVariables();
        void initWindow();
        void initFonts();
         void initText();
    public:
        //constructors / destructors
        Game();
        virtual ~Game();

        //Functions
        void spawnEnemy();

        void update();
        void updateEnemies();
        void updateText();

        void render();
        void renderEnemies();
        void renderText(sf::RenderTarget &target);//you can render to designated place

        void pollEvents();
        void updateMousePos();
       

        //accessors
        const bool running() const;
        const bool getEndgame() const;

};











#endif