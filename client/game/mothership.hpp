#ifndef MOTHERSHIP_H
#define MOTHERSHIP_H

#include <SFML/Graphics.hpp>
#include "planet.hpp"


class Mothership : public Planet {
    int rotation;

public:
    Mothership(int posx, int posy, int vid, Player *vowner);

    ~Mothership();
    int get_radius() const { return 30; }
    int get_rotation() const { return rotation; }
    void ships_arrival(Player *player, int amount, int current_time);
    void draw(sf::RenderWindow &window, const sf::Color &c) const;
};

#endif
