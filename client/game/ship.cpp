#include "ship.hpp"

void Ship::addAcceleration(FVector acc, int dt) {
  // dV += acc * dt; should do the same.
  //float dttt = (float)(dt);
  FVector temp = acc;
  
  temp *= dt;
  dV += temp;
  //dV += acc * dt; // TODO: make this possible
}

void Ship::update(int dt, int fleetX, int fleetY, float p) {
  vel += dV;
  vel *= p;
  FVector temp = vel;
  temp *= dt;
  pos += temp;
  //pos += vel * dt; 
  dV.x = 0;
  dV.y = 0;
  screenX = pos.x + fleetX;
  screenY = pos.y + fleetY;
  
}

Ship::Ship(int offsetX, int offsetY) {
  pos.x = offsetX;
  pos.y = offsetY;
  screenX = 50;
  screenY = 50;
  dV.x=0; dV.y=0;
  vel.x=0; vel.y=0;
  //std::cout << "Ship constructed " << std::endl;
}
