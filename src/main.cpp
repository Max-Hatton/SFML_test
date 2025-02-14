#include <optional>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <random>
#include "Ship.h"
#include "list"
#include "iterator"

struct Bullet {
    float x;
    float y;
};

int main() {
    std::list <Bullet> bullets;
    sf::Clock clock;
    sf::Time currentTime;
    sf::Time preTime;
    sf::Time bulletTime = sf::seconds(-0.5f);
    std::mt19937 generator;
    std::uniform_real_distribution<float> distribution(10, 600);
    unsigned windowWidth = 800;
    unsigned windowHeight = 600;
    auto window = sf::RenderWindow(sf::VideoMode({windowWidth, windowHeight}), "CMake SFML Project");
    bool movingLeft = false;
    bool movingRight = false;
    window.setFramerateLimit(165);
    window.setKeyRepeatEnabled(false);
    Ship ship;
    sf::RectangleShape shipShape({25, 25});
    sf::RectangleShape bulletShape({8, 15});
    shipShape.setPosition({ship.getShipX(), ship.getShipY()});
    shipShape.setFillColor(sf::Color::Red);
    shipShape.setOrigin(shipShape.getGeometricCenter());
    bulletShape.setOrigin(bulletShape.getGeometricCenter());
    while (window.isOpen()){
        while (const std::optional event = window.pollEvent()){
            if (event->is<sf::Event::Closed>()){
                window.close();
            }
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()){
                if (keyPressed->code == sf::Keyboard::Key::Escape){
                    window.close();
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)){
                    movingLeft = true;
                }
                if (keyPressed->code == sf::Keyboard::Key::D){
                    movingRight = true;
                }
                if (keyPressed->code == sf::Keyboard::Key::Space){
                    if (currentTime.asSeconds() - bulletTime.asSeconds() >= 0.5){
                        bulletTime = clock.getElapsedTime();
                        bullets.push_back({ship.getShipX(), ship.getShipY()});
                    }
                }
            }
            else if (const auto* keyReleased = event->getIf<sf::Event::KeyReleased>()){
                if (keyReleased->code == sf::Keyboard::Key::A){
                    movingLeft = false;
                }
                if (keyReleased->code == sf::Keyboard::Key::D){
                    movingRight = false;
                }
            }
        }
        preTime = currentTime;
        currentTime = clock.getElapsedTime();
        float deltaTime = currentTime.asSeconds() - preTime.asSeconds();
        for (std::list<Bullet>::iterator it{bullets.begin()}; it != bullets.end(); it++){
            it->y -= 200 * deltaTime;
            if (it->y < 0){
                bullets.erase(it);
            }
        }
            window.clear();
            if (movingLeft){
                ship.moveLeft(ship.getVelocity());
            }
            if (movingRight){
                ship.moveRight(ship.getVelocity());
            }
            shipShape.setPosition({ship.getShipX(), ship.getShipY()});
            for (auto & it : bullets){
                bulletShape.setPosition({it.x, it.y});
                window.draw(bulletShape);
            }
            window.draw(shipShape);
            window.display();
    }
}
