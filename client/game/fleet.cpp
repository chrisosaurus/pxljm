#include <iostream>
#include "ship.hpp"
#include "fleet.hpp"

Fleet::Fleet(int quantity, Planet &origin, Planet &destination, int launchTime)
 : ships(quantity), orig(origin), dist(target), startTime(launchTime), radius(50) {

  for (int i=0; i<ships.size(); ++i) {
    ships.push_back(new Ship(orig.x+rand%(2*radius)-radius, orig.y+rand%(2*radius)-radius));
  }
  std::cout << "Fleet constructed. " << std::endl;
}
