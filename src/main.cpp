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
struct Enemy {
    float x;
    float y;
};


int main() {
    std::list <Enemy> enemies;
    std::list <Bullet> bullets;
    sf::Clock clock;
    sf::Time currentTime;
    sf::Time preTime;
    sf::Time bulletTime = sf::seconds(-0.5f);
    sf::Time enemyTime = sf::seconds(0);
    std::mt19937 generator;
    std::uniform_real_distribution<float> distribution(25, 775);
    unsigned windowWidth = 800;
    unsigned windowHeight = 600;
    auto window = sf::RenderWindow(sf::VideoMode({windowWidth, windowHeight}), "CMake SFML Project");
    bool movingLeft = false;
    bool movingRight = false;
    window.setFramerateLimit(165);
    window.setKeyRepeatEnabled(false);
    Ship ship;
    sf::Vector2<float> bulletRecPos;
    sf::Vector2<float> enemyRecPos;
    sf::FloatRect bulletRec({bulletRecPos}, {8,15});
    sf::FloatRect enemyRec({enemyRecPos},{25,25});
    sf::RectangleShape shipShape({25, 25});
    sf::RectangleShape bulletShape({8, 15});
    sf::RectangleShape enemyShape({25, 25});
    shipShape.setPosition({ship.getShipX(), ship.getShipY()});
    shipShape.setFillColor(sf::Color::Red);
    enemyShape.setFillColor(sf::Color::Green);
    shipShape.setOrigin(shipShape.getGeometricCenter());
    bulletShape.setOrigin(bulletShape.getGeometricCenter());
    enemyShape.setOrigin(enemyShape.getGeometricCenter());
    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
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
        if (currentTime - enemyTime >= sf::seconds(5.0f)) {
            enemies.push_back({distribution(generator), 50});
            enemyTime = clock.getElapsedTime();
        }
        for (auto & it : bullets){
            it.y -= 200 * deltaTime;
        }
        for (auto & it : bullets) {
            for (std::list<Enemy>::iterator et{enemies.begin()}; et != enemies.end(); et++) {
                bulletRec.position = {it.x,it.y};
                enemyRec.position = {et->x,et->y};
                if (bulletRec.findIntersection(enemyRec)){
                    enemies.erase(et);
                }
            }
        }





        window.clear();
        for (auto & it : enemies){
            it.y += 100 * deltaTime;
            enemyShape.setPosition({it.x, it.y});
            window.draw(enemyShape);
        }
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
