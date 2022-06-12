#include "header.hpp"

textures_t texture;
bird_t bird;
game_t game;

int main() {
    // Window setup
    sf::RenderWindow mainWindow(sf::VideoMode(800, 600), "This is main window", sf::Style::Titlebar | sf::Style::Close);
    mainWindow.setFramerateLimit(30);
    sf::Event ev;

    // Load textures
    texture.background.loadFromFile("./textures/back.png");
    texture.pipe.loadFromFile("./textures/pipe.png");
    texture.endGame.loadFromFile("./textures/end.png");
    texture.character.loadFromFile("./textures/bird.png");

    // SetUp bird
    bird.sprite.setPosition(250, 300);
    bird.sprite.setScale(2, 2);

    // SetUp game instance
    game.font.loadFromFile("./fonts/COMIC.TTF");
    game.textStart.setString("Press S to start");
    game.textStart.setFont(game.font);
    game.textStart.setFillColor(sf::Color::Blue);
    game.textStart.setCharacterSize(50);
    game.textStart.setPosition(500, 250);
    game.textStart.setOrigin(game.textStart.getLocalBounds().width / 2, 0);
    game.textScore.setFont(game.font);
    game.textScore.setFillColor(sf::Color::White);
    game.textScore.setCharacterSize(50);
    game.textScore.move(50, 0);
    game.background[0].setTexture(texture.background);
    game.background[1].setTexture(texture.background);
    game.background[2].setTexture(texture.background);
    game.background[0].setScale(1.15, 1.17);
    game.background[1].setScale(1.15, 1.17);
    game.background[2].setScale(1.15, 1.17);
    game.background[1].setPosition(300, 0);
    game.background[2].setPosition(600, 0);

    // Pipes vector
    std::vector<sf::Sprite> pipes;

    // App loop
    while (mainWindow.isOpen()) {
        // Current score loop
        game.textScore.setString(std::to_string(game.score));

        // Character update
        float birdY = bird.sprite.getPosition().y;
        float birdX = bird.sprite.getPosition().x;
        float birdWidth = 34 * bird.sprite.getScale().x;
        float birdHeight = 24 * bird.sprite.getScale().y;

        // Character texture
        bird.sprite.setTexture(texture.character);

        // Character boundaries
        if (game.curentGameState == going) {
            if (birdY > 600) {
                bird.vSpeed = 0;
                game.curentGameState = end;
            } else if (birdY < 0) {
                bird.sprite.setPosition(250, 0);
                bird.vSpeed = 0;
            }
        }

        // Generate Pipe
        if (game.curentGameState == going && game.frames % 100 == 0) {
            int d = rand() % 300;

            sf::Sprite upperPipe;
            upperPipe.setTexture(texture.pipe);
            upperPipe.setPosition(1000, d);
            upperPipe.setScale(2, -2);

            sf::Sprite lowerPipe;
            lowerPipe.setTexture(texture.pipe);
            lowerPipe.setPosition(1000, d + 200);
            lowerPipe.setScale(2, 2);

            pipes.push_back(lowerPipe);
            pipes.push_back(upperPipe);
        }

        // Score Count
        for (std::vector<sf::Sprite>::iterator j = pipes.begin(); j != pipes.end(); j++) {
            if (game.curentGameState == going && (*j).getPosition().x == 250) {
                game.score++;
                break;
            }
        }

        // Moving pipes
        if (game.curentGameState == going) {
            for (std::vector<sf::Sprite>::iterator j = pipes.begin(); j != pipes.end(); j++) {
                (*j).move(-3, 0);
            }
        }

        // Collision check
        if (game.curentGameState == going) {
            for (std::vector<sf::Sprite>::iterator j = pipes.begin(); j != pipes.end(); j++) {
                float pipeX, pipeY, pipeWidth, pipeHeight;
                if ((*j).getScale().y > 0) {
                    pipeX = (*j).getPosition().x;
                    pipeY = (*j).getPosition().y;
                    pipeWidth = 52 * (*j).getScale().x;
                    pipeHeight = 320 * (*j).getScale().y;
                } else {
                    pipeWidth = 52 * (*j).getScale().x;
                    pipeHeight = -320 * (*j).getScale().y;
                    pipeX = (*j).getPosition().x;
                    pipeY = (*j).getPosition().y - pipeHeight;
                }
                if (collisionCheck(birdX, birdY, birdWidth, birdHeight, pipeX, pipeY, pipeWidth, pipeHeight)) {
                    game.curentGameState == end;
                }
            }
        }

        // Event capture
        while (mainWindow.pollEvent(ev)) {
            switch (ev.type) {
                case sf::Event::Closed:
                    mainWindow.close();
                    break;
                case sf::Event::KeyPressed:
                    if (ev.key.code == sf::Keyboard::Escape) {
                        mainWindow.close();
                        break;
                    } else if (ev.key.code == sf::Keyboard::Space) {
                        if (game.curentGameState == going) {
                            bird.vSpeed = -15;
                        }
                    } else if (ev.key.code == sf::Keyboard::S && game.curentGameState == end) {
                        bird.sprite.setPosition(250, 300);
                        game.score = 0;
                        pipes.clear();
                        game.curentGameState = start;
                    }
            }
        }

        // Update frame
        mainWindow.clear();
        mainWindow.draw(bird.sprite);

        for (std::vector<sf::Sprite>::iterator j = pipes.begin(); j != pipes.end(); j++) {
            mainWindow.draw(*j);
        }

        mainWindow.draw(game.background[0]);
        mainWindow.draw(game.background[1]);
        mainWindow.draw(game.background[2]);

        mainWindow.draw(game.textScore);

        if (game.curentGameState == end) {
            mainWindow.draw(game.endGame);
        }

        // Render
        mainWindow.display();
    }
    return 0;
}