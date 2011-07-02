#ifndef MOTHERSHIP_H
#define MOTHERSHIP_H

#include <SFML/Graphics.hpp>

class Planet;

class Mothership : public Planet {
    int rotation;

public:
    Mothership(int posx, int posy, int vid);

    ~Mothership();

    int get_rotation() const { return rotation; }

    void draw(sf::RenderWindow &window, const sf::Color &c) const;
};

#endif
