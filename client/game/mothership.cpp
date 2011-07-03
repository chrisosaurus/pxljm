#include "mothership.hpp"
#include "player.hpp"
Mothership::Mothership(int posx, int posy, int vid, Player *vowner)
    : Planet(posx, posy, 100, vid), rotation(0) {
    owner = vowner;
}

Mothership::~Mothership() {}

void Mothership::ships_arrival(Player *player, int amount, int current_time) {
    Player *o = owner;
    Planet::ships_arrival(player, player == o ? amount : (3 * amount) >> 2, current_time);
    if (o != owner && o->get_moship() == this)
        o->mark_dead();
}

void Mothership::draw(sf::RenderWindow &window, const sf::Color &c) const {
    sf::Shape moship;

    moship.AddPoint(get_x()+20, get_y(), c, c);
    moship.AddPoint(get_x()-20, get_y()-20, c, c);
    moship.AddPoint(get_x()-20, get_y()+20, c, c);
    moship.EnableFill(true);
    moship.Rotate(get_rotation());
    window.Draw(moship);
}
