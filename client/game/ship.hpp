#ifndef SHIP_H
#define SHIP_H
#include <iostream>

#define LIGHTSPEED 9001

class Ship {
public:

  // only to be accessed by Fleet
  int x;
  int y;

  // to be accessed by draw
  int screenX;
  int screenY;
  float rot;  // in radians

  Ship(int offsetX, int offsetY);
};

#endif
