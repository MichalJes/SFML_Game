#include <iostream>
#include <string>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>


enum gameState { start,
                 going,
                 end };

typedef struct textures_s {
    sf::Texture pipe;
    sf::Texture background;
    sf::Texture character;
    sf::Texture endGame;
} textures_t;

typedef struct bird_s {
    double vSpeed = 0;
    sf::Sprite sprite;
} bird_t;

typedef struct game_s {
    gameState curentGameState = start;
    sf::Font font;
    sf::Text textScore;
    sf::Text textStart;
    int score = 0;
    int frames = 0;
    sf::Sprite endGame;
    sf::Sprite background[3];
} game_t;
