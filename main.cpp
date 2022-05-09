#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string>

int main() {
    // Window setup
    sf::RenderWindow mainWindow(sf::VideoMode(640, 480), "This is main window", sf::Style::Titlebar | sf::Style::Close);
    sf::Event ev;

    int spaceClicks = -1;
    int gameState = 0;
    int col = 100;

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
                    if (ev.key.code == sf::Keyboard::Space) {
                        if (spaceClicks == -1) {
                            gameState = 1;
                            spaceClicks = +1;
                            break;
                        } else {
                            gameState = 2;
                            if (col + 10 > 255) {
                                col = 90;
                            }
                            col += 10;
                            break;
                        }
                    }
            }
        }

        // Update

        // Render
        switch (gameState) {
            case 0:
                mainWindow.clear(sf::Color::Blue);
                break;
            case 1:
                mainWindow.clear(sf::Color::Green);
                break;
            default:
                mainWindow.clear(sf::Color(255, 255, col, 255));
                break;
        }

        mainWindow.display();
    }

    return 0;
}