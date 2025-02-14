#include <optional>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <random>

int main() {
    std::mt19937 generator;
    std::uniform_real_distribution<float> distribution(10, 600);
    float shapePositionX = 0;
    float shapePositionY = 0;
    float shapeSize = 50;
    float foodSize = 10;
    float foodPositionX = 500;
    float foodPositionY = 500;
    sf::RectangleShape shape({shapeSize, shapeSize});
    sf::RectangleShape food({foodSize, foodSize});
    shape.setOrigin(shape.getGeometricCenter());
    food.setOrigin(food.getGeometricCenter());
    sf::Vector2f origin = shape.getOrigin();
    std::cout << origin.x << " " << origin.y << std::endl;
    std::cout << origin.x << " " << origin.y << std::endl;
    shape.setFillColor(sf::Color(100, 250, 50));
    food.setFillColor(sf::Color(250, 100, 50));
    unsigned windowWidth = 800;
    unsigned windowHeight = 600;
    auto window = sf::RenderWindow(sf::VideoMode({windowWidth, windowHeight}), "CMake SFML Project");
    window.setFramerateLimit(165);
    window.setKeyRepeatEnabled(false);
    bool isShapeMovingUp = false;
    bool isShapeMovingDown = false;
    bool isShapeMovingLeft = false;
    bool isShapeMovingRight = false;
    float shapeSpeed = 1;
    food.setPosition({foodPositionX, foodPositionY});
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
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
                    isShapeMovingUp = true;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
                    isShapeMovingDown = true;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
                    isShapeMovingLeft = true;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
                    isShapeMovingRight = true;
                }
            }
            else if (const auto* keyRelease = event->getIf<sf::Event::KeyReleased>()) {
                if (keyRelease->code == sf::Keyboard::Key::W) {
                    isShapeMovingUp = false;
                }
                if (keyRelease->code == sf::Keyboard::Key::S) {
                    isShapeMovingDown = false;
                }
                if (keyRelease->code == sf::Keyboard::Key::A) {
                    isShapeMovingLeft = false;
                }
                if (keyRelease->code == sf::Keyboard::Key::D) {
                    isShapeMovingRight = false;
                }
            }
        }
        if (isShapeMovingUp && isShapeMovingLeft) {
            shapePositionX -= shapeSpeed/2;
            shapePositionY -= shapeSpeed/2;
        }
        else if (isShapeMovingUp && isShapeMovingRight) {
            shapePositionX += shapeSpeed/2;
            shapePositionY -= shapeSpeed/2;
        }
        else if (isShapeMovingDown && isShapeMovingLeft) {
            shapePositionX -= shapeSpeed/2;
            shapePositionY += shapeSpeed/2;
        }
        else if (isShapeMovingDown && isShapeMovingRight) {
            shapePositionX += shapeSpeed/2;
            shapePositionY += shapeSpeed/2;
        }
        else if (isShapeMovingUp) {
            shapePositionY -= shapeSpeed;
        }
        else if (isShapeMovingLeft) {
            shapePositionX -= shapeSpeed;
        }
        else if (isShapeMovingRight) {
            shapePositionX += shapeSpeed;
        }
        else if (isShapeMovingDown) {
            shapePositionY += shapeSpeed;
        }
        //std::cout << shape.getOrigin().x + (shapeSize/2);
        if (std::sqrt(std::pow(shapePositionX - foodPositionX, 2) + std::pow(shapePositionY - foodPositionY, 2)) <= shapeSize/2 + foodSize/2) {
            shapeSize += 10;
            foodPositionX = distribution(generator);
            foodPositionY = distribution(generator);
            shape.setSize({shapeSize, shapeSize});
            food.setPosition({foodPositionX, foodPositionY});
            shape.setOrigin(shape.getGeometricCenter());

        }


        window.clear();
        window.draw(food);
        window.draw(shape);
        shape.setPosition({shapePositionX, shapePositionY});
        window.display();
    }
}
