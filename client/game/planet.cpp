#include "planet.hpp"

Planet::Planet(int vx, int vy, int vradius, int vid) : x(vx), y(vx), radius(50), id(vid) { }

int Planet::get_x() const { return x; }
int Planet::get_y() const { return y; }


