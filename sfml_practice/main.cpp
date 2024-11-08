
#include "game_class.hpp"


Game::Game()
{
    this->initVariables();
    this->initWindow();
    this->initenemies();

}

Game::~Game()
{
    delete this->window;
}

void Game::spawnEnemy()
{
    /*
        spawns enemies and sets their colors and positions
            set random pos
            set random color
            add enemy to the vector
            remove enemies at the edge of the screen
    */
   this->enemy.setPosition
   (//  在０跟視窗寬度間取隨機 －自己本身的寬度
    static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
    0.f);
   this->enemy.setFillColor(sf::Color(176, 167, 194));
   //spawn enemy
   this->enemies.push_back(this->enemy);
    //move the enemies
    for (auto & e : this->enemies)
    {
        e.move(0.f, 7.f);
    }

    //remove enemies at the edge of the screen

}


//accessors

void Game::pollEvents()
{
    // event polling 
      while (this->window->pollEvent(this->event))
        {
            switch(this->event.type)
            {
                case sf::Event::Closed:
                    this->window->close();
                    break;
                case sf::Event::KeyPressed:
                    if (this->event.key.code == sf::Keyboard::Escape)
                        this->window->close();
                        break;    
            }
        }  
}


 void  Game::updateEnemies()
 {
    /*
        return void 
        update spawn time and spawn enemy
        when the totall enemy nymber is less than setup
    */
    //update timer for enemy spawning
    if (this->enemies.size() < this->maxEnemies)
    {
        if (this->enemySpawnTimer >= this->enemySpawntimerMax )
        {
           //reset timer
           this->spawnEnemy();
            this->enemySpawnTimer = 0.f;
        }    
        else
            this->enemySpawnTimer += 10.f;
    }
    //move and update enemies
    for (int i = 0; i < this->enemies.size(); i++)
    {
        bool deleted = false;

        this->enemies[i].move(0.f, 1.f); 
       
        if (this->enemies[i].getPosition().y > this->window->getSize().y)
        {
            //deleted = true;
            this->enemies.erase(this->enemies.begin() + i);
            this->health -= 1;
        }

    }
//check if clicked upon
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))  
    {
        if (this->mouseHeld == false)
        {
            this->mouseHeld == true;
            bool deleted = false;
            for (int i = 0; i < this->enemies.size() && deleted == false; i++)
            {
                if (this->enemies[i].getGlobalBounds().contains(this->mousePosView))
                {
                    //delete the enemy
                    deleted = true;

                    this->enemies.erase(this->enemies.begin() + i);
                    //gain points
                    this->points += 1.f;
                }
            }
        }
        else 
            this->mouseHeld == false;
        

        
    }
    
       
 }

void Game::update()
{
    this->pollEvents();
    if (this->endgame == false) 
    {
         //update mouse position  related to the screen
        this->updateMousePos();  
        //relatice to the window
          
        this->updateEnemies();
    }
   
   //end game condition
   if (this->health <= 0)
   {
        this->endgame = true;
   }

   

   
}
const bool Game::getEndgame() const
{
    return (this->endgame);
}

void Game::updateMousePos()
{
    /*
        update mouse positions related to game window (vector2i)
    */
   this->mousePosWinow = sf::Mouse::getPosition(*this->window);
   this->mousePosView = this->window->mapPixelToCoords(this->mousePosWinow);
}

void Game::renderEnemies()
{
    //redering all enemies
    for (auto & e : this->enemies)
    {
        this->window->draw(e);
    }
}

void Game::render()
{
    /*
    return void 
    render all objects
        -clear old frame
        -render objects
        -display frame in window
    */

    this->window->clear(sf::Color(	237, 232, 208));
    //drawcgame object 
    this->window->draw(this->enemy);
    this->renderEnemies();
    this->window->display();
}


void Game::initVariables()
{
    this->window = nullptr;
    // init game logic
    
    this->enemySpawntimerMax = 100.f;
    this->enemySpawnTimer = this->enemySpawntimerMax;
    this->maxEnemies = 10;
    this->points = 0;
    this->mouseHeld = false;
    this->health = 10;
    this->endgame = false;
    
}

const bool Game::running() const
{
    return this->window->isOpen();
}

void Game::initenemies()
{
    this->enemy.setPosition(10.f,5.f);
    this->enemy.setSize(sf::Vector2f(50.f, 50.f));
    this->enemy.setScale(sf::Vector2f(0.5f, 0.5f));
    this->enemy.setFillColor(sf::Color(181 , 163, 77));
    this->enemy.setOutlineColor(sf::Color(208, 237, 213));
    this->enemy.setOutlineThickness(5.f);




}


void Game::initWindow()
{
    this->videoMode.height = 600;
    this->videoMode.width = 800;
    
    this->window = new sf::RenderWindow (this->videoMode, "My First C++ Game", 
        sf::Style::Titlebar | sf::Style :: Close);

    this->window->setFramerateLimit(60);
   
}


//using namespace sf;

int main() 
{

    std::srand(static_cast<unsigned>(time(NULL)));// init arand
    //init game engine
    Game game;

    //game loop        
    while (game.running() && !game.getEndgame())
    {   
      
        //update game 
        game.update();

        // redner game   
        game.render();
    }

    return 0;
}

//  g++ -std=c++11 main.cpp -o my_sfml_game -I/usr/local/opt/sfml/include -L/usr/local/opt/sfml/lib -lsfml-graphics -lsfml-window -lsfml-system