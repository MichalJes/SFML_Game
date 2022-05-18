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
    texture.background.loadFromFile("");
    texture.pipe.loadFromFile("");
    texture.endGame.loadFromFile("");
    texture.character.loadFromFile("");

    // SetUp bird
    bird.sprite.setPosition(200,200);
    bird.sprite.setScale(2,2);

    // SetUp game instance
    game.font.loadFromFile("./fonts/COMIC.TTF");
    game.textStart.setString("Press S to start");
    game.textStart.setFont(game.font);
    game.textStart.setFillColor(sf::Color::Blue);
	game.textStart.setCharacterSize(50);
    game.textStart.setPosition(500, 250);
    game.textScore.setFont(game.font);
    game.textScore.setFillColor(sf::Color::White);
    game.textScore.setCharacterSize(50);
    game.background[0].setTexture(texture.background);
    game.background[1].setTexture(texture.background);
    game.background[2].setTexture(texture.background);
    game.background[0].setScale(1.15, 1.17);
    game.background[1].setScale(1.15, 1.17);
    game.background[2].setScale(1.15, 1.17);
    game.background[1].setPosition(300,0);
    game.background[2].setPosition(600,0);

    // App loop
    while (mainWindow.isOpen()) {
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
                    }
            }
        }

        // Update

        // Render

        mainWindow.display();
    }

    return 0;
}