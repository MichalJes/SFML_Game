#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class CustomRectangleShape : public sf::RectangleShape {
public:
    CustomRectangleShape(const sf::Vector2f &size, const sf::Vector2f &position,
                         const sf::RenderWindow &window)
        : sf::RectangleShape(size), window_(window) {
        setPosition(position);
    };

void setSpeed(int x, int y, int rotation) {
        speed_x_ = x;
        speed_y_ = y;
        speed_rotation_ = rotation;
}

void animate(const sf::Time &elapsed) {
        handleEvents();

        auto bounding_box = getGlobalBounds();
        if (bounding_box.left < 0) {
            speed_x_ = std::abs(speed_x_);
        }
        else if (bounding_box.left + bounding_box.width > bounds_.left + bounds_.width) {
            speed_x_ = -std::abs(speed_x_);
        }
        if (bounding_box.top < 0) {
            speed_y_ = std::abs(speed_y_);
        }
        else if (bounding_box.top + bounding_box.height > bounds_.top + bounds_.height) {
            speed_y_ = -std::abs(speed_y_);
        }

        auto seconds = elapsed.asSeconds();
        move(speed_x_ * seconds, speed_y_ * seconds);
        rotate(speed_rotation_ * seconds);
}

void handleEvents() {
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            auto bounding_box = getGlobalBounds();
            auto position = sf::Mouse::getPosition(window_);
            if (bounding_box.contains(position.x, position.y)) {
                speed_x_ = 0;
                speed_y_ = 0;
            }
        }
}

void setBounds(const sf::IntRect &bounds) {
        bounds_ = bounds;
}

void setBounds(int left, int width, int top, int height) {
        bounds_ = sf::IntRect(left, top, width, height);
}

private:
    const sf::RenderWindow &window_;
    int speed_x_ = 0;
    int speed_y_ = 0;
    int speed_rotation_ = 0;
    sf::IntRect bounds_;
};

int main() {
    // stworzenie okna
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");

    // tworzymy prostokąt wg kreatora z klasy
    CustomRectangleShape rectangle(sf::Vector2f(120.0, 60.0),
                                   sf::Vector2f(300.0, 300.0),
                                   window);
    rectangle.setFillColor(sf::Color(100, 50, 250));
    //ustawienie prędskosci
    rectangle.setSpeed(100, 100, 10);

    rectangle.setBounds(0, window.getSize().x, 0, window.getSize().y);

    sf::Clock clock;//zegar przed petla

    // run the program as long as the window is open
    while (window.isOpen()) {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event)) {
            // "close requested" event: we close the window and kohać dziekana
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // clear the window with black color
        window.clear(sf::Color::Black);

        sf::Time elapsed = clock.restart();

        rectangle.animate(elapsed);

        // draw everything here...
        window.draw(rectangle);

        // end the current frame
        window.display();
    }

    return 0;
}
