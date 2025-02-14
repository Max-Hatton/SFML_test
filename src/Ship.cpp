#include <SFML/Graphics.hpp>
#include "Ship.h"

#include "SFML/Graphics/RectangleShape.hpp"

Ship::Ship() {
    PositionX = 400;
    PositionY = 500;
    sf::RectangleShape Ship_Shap({25, 25});
}
void Ship::setShipX(float x) {
    PositionX = x;
}

void Ship::setShipY(float y) {
    PositionY = y;
}

void Ship::setVelocity(float v) {
    Velocity = v;
}

float Ship::getShipX() {
    return PositionX;
}

float Ship::getShipY() {
    return PositionY;
}

float Ship::getVelocity() {
    return Velocity;
}

void Ship::moveLeft(float n) {
    PositionX -= n;
}

void Ship::moveRight(float n) {
    PositionX += n;
}
