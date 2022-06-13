#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>

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
    int score = 0;
    int frames = 0;
    gameState curentGameState = start;
    sf::Sprite endGame;
    sf::Sprite background[3];
    sf::Text textScore;
    sf::Text textStart;
    sf::Font font;
} game_t;

bool collisionCheck(float xCord1, float yCord1, float width1, float height1, float xCord2, float yCord2, float width2, float height2) {
    if (xCord1 + width1 > xCord2 && xCord2 + width2 > xCord1 && yCord1 + height1 > yCord2 && yCord2 + height2 > yCord1) {
        return true;
    }
    return false;
}