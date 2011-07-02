#include "ship.hpp"

void Ship::addAcceleration(FVector acc, int dt) {
  // dV += acc * dt; should do the same.
  float dttt = (float)(dt);
  FVector temp = acc;
  
  temp *= dt;
  dV += temp;
  //dV += acc * dt; // TODO: make this possible
}

void Ship::update(int dt, int fleetX, int fleetY) {
  vel += dV;
  vel /= 1.1;
  FVector temp = vel;
  temp *= dt;
  pos += temp;
  //pos += vel * dt; 
  dV.x = 0;
  dV.y = 0;
  screenX = pos.x + fleetX;
  screenY = pos.y + fleetY;
}

Ship::Ship(int offsetX, int offsetY) : x(offsetX), y(offsetY) {
  pos.x = x;
  pos.y = y;
  std::cout << "Ship constructed " << std::endl;
}
