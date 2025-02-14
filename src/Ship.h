#ifndef SHIP_H
#define SHIP_H



class Ship {
private:
    float PositionX{0};
    float PositionY{0};
    float Velocity{2};
public:
    Ship();
    float getShipX();
    float getShipY();
    float getVelocity();
    void setShipX(float x);
    void setShipY(float y);
    void setVelocity(float v);
    void moveLeft(float n);
    void moveRight(float n);
};



#endif //SHIP_H
