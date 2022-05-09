#include <SFML/Graphics.hpp>
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
int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    sf::Clock clock;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}
