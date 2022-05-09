#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>



class Game {
   private:
    void initVariables();

    void initWindow();

   public:
    Game();
    virtual ~Game();
    void update();
    void render();
};