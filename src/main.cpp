#include <optional>
#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    float shapePositionX = 400;
    float shapePositionY = 300;
    float shapeSize = 50;
    sf::RectangleShape shape({shapeSize, shapeSize});
    sf::Vector2f origin = shape.getOrigin();
    std::cout << origin.x << " " << origin.y << std::endl;
    shape.setOrigin({25, 25});
    origin = shape.getOrigin();
    std::cout << origin.x << " " << origin.y << std::endl;
    shape.setFillColor(sf::Color(100, 250, 50));
    unsigned windowWidth = 800;
    unsigned windowHeight = 600;
    auto window = sf::RenderWindow(sf::VideoMode({windowWidth, windowHeight}), "CMake SFML Project");
    window.setFramerateLimit(60);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
            else if (const auto* keyPress = event->getIf<sf::Event::KeyPressed>()) {
                if (keyPress->code == sf::Keyboard::Key::Escape) {
                    window.close();
                }
                else if (keyPress->code == sf::Keyboard::Key::R) {
                    windowWidth += 100;
                    windowHeight += 100;
                    window.setSize({windowWidth, windowHeight});
                }
                else if (keyPress->code == sf::Keyboard::Key::W) {
                    shapePositionY -= 10;
                }
                else if (keyPress->code == sf::Keyboard::Key::S) {
                    shapePositionY += 10;
                }
                else if (keyPress->code == sf::Keyboard::Key::A) {
                    shapePositionX -= 10;
                }
                else if (keyPress->code == sf::Keyboard::Key::D) {
                    shapePositionX += 10;
                }
                else if (keyPress->code == sf::Keyboard::Key::Q) {
                    if (shapeSize > 10) {
                        shapeSize -= 10;
                        shape.setSize({shapeSize, shapeSize});
                        shapePositionX += 5;
                        shapePositionY += 5;
                    }
                }
                else if (keyPress->code == sf::Keyboard::Key::E) {
                    if (shapeSize < 1000) {
                        shapeSize += 10;
                        shape.setSize({shapeSize, shapeSize});
                        shapePositionX -= 5`;
                        shapePositionY -= 5;
                    }
                }
            }
        }

        window.clear();
        window.draw(shape);
        shape.setPosition({shapePositionX, shapePositionY});
        window.display();
    }
}
