#ifndef INTERFACING_H
#define INTERFACING_H
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
class Client;

class Interfacing{
    sf::RenderWindow window;
    ClientGame& game;
    Player *me; // pointer to the player I am
    sf::Clock clock; // for game time
    sf::Color colour_from_uid(int uid);
    sf::Sprite bg;
    sf::Image bgimage;
    void draw_string(const std::string &val, int x, int y);
  public:
    // this is a constructor, herpa derpety derp
    Interfacing(ClientGame& ga, Player *p);


    void draw(std::vector<Planet*> &planets, std::vector<Fleet*> &fleets);

    // main loop
    void main();

    void die();
};

#endif
