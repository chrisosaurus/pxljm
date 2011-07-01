class Client;

class Interfacing{
    sf::RenderWindow window;
    ClientGame game;
  public:
    // this is a constructor, herpa derpety derp
    Interfacing(ClientGame& ga);

    // draw everything (planets, moships, fleets) TODO change MotherShip to Player
    void draw(const std::vector<Planet> &planets, const std::vector<Mothership> &moships, const std::vector<Fleet> &fleets);

    // we won't be using this much, maybe it will be private
    void draw_string(const std::string &val, int x, int y);

    // main loop
    void main();
};
