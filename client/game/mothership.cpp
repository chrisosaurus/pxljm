#include "mothership.hpp"

Mothership::Mothership(int posx, int posy, int vid, Player *vowner)
    : Planet(posx, posy, 100, vid), rotation(0) {
    owner = vowner;
}

Mothership::~Mothership() {}

void Mothership::draw(sf::RenderWindow &window, const sf::Color &c) const {
    sf::Shape moship;

    moship.AddPoint(get_x()+20, get_y(), c, c);
    moship.AddPoint(get_x()-20, get_y()-20, c, c);
    moship.AddPoint(get_x()-20, get_y()+20, c, c);
    moship.EnableFill(true);
    moship.Rotate(get_rotation());
    window.Draw(moship);
}
