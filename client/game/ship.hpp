#ifndef SHIP_H
#define SHIP_H

#include <iostream>
#include "fvector.hpp"

#define LIGHTSPEED 9


class Ship {
private:
  FVector dV;
  FVector vel;
public:
  // only to be accessed by Fleet
  FVector pos;

  // to be accessed by draw
  int screenX;
  int screenY;
  float rot;  // in radians

  Ship(int offsetX, int offsetY);
  
  void addAcceleration(FVector acc, int dt);
  
  void update(int dt, int fleetX, int fleetY, float p);
};

#endif
