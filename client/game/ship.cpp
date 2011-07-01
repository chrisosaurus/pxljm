#include "ship.hpp"

Ship::Ship(int offsetX, int offsetY) : x(offsetX), y(offsetY) {
  std::cout << "Ship constructed " << std::endl;
}
