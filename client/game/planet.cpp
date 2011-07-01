#include "planet.hpp"

Planet::Planet(int X, int Y, int Radius) : x(X), y(Y), radius(Radius) { }

int Planet::get_x() const { return x; }
int Planet::get_y() const { return y; }


