#include <iostream>
#include <stdlib.h>
#include <math.h>
#include "fvector.hpp"
#include "ship.hpp"
#include "fleet.hpp"
#include "planet.hpp"
#include "mothership.hpp"
#include "player.hpp"

#define FLEET_SPEED 0.05  // 50 pixels per 1000ms

Fleet::Fleet(int quantity, Planet &origin, Planet &destination, int launchTime, Player &sender)
 : ships(quantity), orig(origin), dest(destination), startTime(launchTime), owner(sender), radius(50), screenX(origin.get_x()), screenY(origin.get_y()) {

  endTime = startTime + hypot(dest.get_x()-orig.get_x(), dest.get_y()-orig.get_y()) / FLEET_SPEED;  // dt = dx/v

  for (int i=0; i<ships.size(); ++i) {
    ships.push_back(new Ship(orig.get_x()+rand()%(2*radius)-radius, orig.get_y()+rand()%(2*radius)-radius));
  }
  std::cout << "Fleet constructed. Owner: player " << owner.get_uid() << std::endl;
}


int Fleet::get_x(int t) { 
  float p = (float)(t-startTime)/(float)(endTime-startTime);  // p: percent there
  return (int)(orig.get_x()*(1-p) + dest.get_x()* p);
}

int Fleet::get_y(int t) { 
  float p = (float)(t-startTime)/(float)(endTime-startTime);  // p: percent there
  return (int)(orig.get_y()*(1-p) + dest.get_y()* p);
}


int Fleet::update(int viewerX, int viewerY, int gameTime, int frameTime) {
  float dist = hypot( // the distance to the "time immume" fleet
    get_x(gameTime) - owner.get_moship()->get_x(),
    get_y(gameTime) - owner.get_moship()->get_y()
  ); 
  int t = gameTime - (int)(dist/LIGHTSPEED);  // the time of the viewed fleet
  screenX = get_x(t);
  screenY = get_y(t);
  
  float p = (float)(t-startTime)/(float)(endTime-startTime);  // p: percent there
  if (p<0.f) return -1;
  if (p>1.f) return +1;
  
  for (int i=0; i<ships.size(); ++i) {
    ships[i]->update(frameTime, screenX, screenY);
  }
  
  return 0;
}
