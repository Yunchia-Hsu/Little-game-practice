
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
            set tandon pos
            set random color
            add enemy to the vector
            remove enemies at the edge of the screen
    */
   this->enemy.setPosition
   (
    //  在０跟視窗寬度間取隨機 －自己本身的寬度
    static_cast<float>(rand()% static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
    0.f
    );
   this->enemy.setFillColor(sf::Color::Green);
   //spawn enemy
   this->enemies.push_back(this->enemy);
    //move the enemies
    for (auto & e : this->enemies)
    {
        e.move(0.f, 6.f);
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
    //update timer for enemy spawining
    if (this->enemies.size() < this->maxEnemies)
    {
        if (this->enemySpawnTimer >= this->enemySpawntimerMax )
        {
           //reset timer
           this->spawnEnemy();
            this->enemySpawnTimer = 0.f;
        }    
        else
            this->enemySpawnTimer += 1.f;
    }
    
    // 更新和移除敵人
    for (size_t i = 0; i < this->enemies.size(); i++)
    {
        // 移動敵人
        this->enemies[i].move(0.f, 6.f);

        // 檢查是否超出螢幕底部
        if (this->enemies[i].getPosition().y > this->window->getSize().y)
        {
            // 移除超出螢幕的敵人
            this->enemies.erase(this->enemies.begin() + i);
            --i; // 因為刪除了一個元素，所以索引要減1
        }
    }


 }

void Game::update()
{
    this->pollEvents();

    //update mouse position  relatice to the screen
    this->updateMousePos();  

    this->updateEnemies();
}

void Game::updateMousePos()
{
    /*
        update mouse position related to window (vector2i)
    */
   this->mousePosWinow = sf::Mouse::getPosition(*this->window);
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

    this->window->clear(sf::Color());
    //drawcgame object 
    this->renderEnemies();
    this->window->display();
}


void Game::initVariables()
{
    this->window = nullptr;
    // init game logic
    this->enemySpawnTimer = 0.f;
    this->enemySpawntimerMax = 100.f;
    this->maxEnemies = 5;
    this->point = 0;
    
}

const bool Game::running() const
{
    return this->window->isOpen();
}

void Game::initenemies()
{
    this->enemy.setPosition(10.f,5.f);
    this->enemy.setSize(sf::Vector2f(50.f, 50.f));
    this->enemy.setFillColor(sf::Color::Cyan);
    this->enemy.setOutlineColor(sf::Color::Green);
    this->enemy.setOutlineThickness(5.f);




}


void Game::initWindow()
{
    this->videoMode.height = 600;
    this->videoMode.width = 800;
    
    this->window = new sf::RenderWindow (this->videoMode, "My First C++ Game", 
        sf::Style::Titlebar | sf::Style :: Close);

    this->window->setFramerateLimit(100);
   
}


//using namespace sf;

int main() 
{

    std::srand(static_cast<unsigned>(time(NULL)));// init arand
    //init game engine
    Game game;

    //game loop        
    while (game.running())
    {   
      
        //update game 
        game.update();

        // redner game   
        game.render();
    }

    return 0;
}

//  g++ -std=c++11 main.cpp -o my_sfml_game -I/usr/local/opt/sfml/include -L/usr/local/opt/sfml/lib -lsfml-graphics -lsfml-window -lsfml-system