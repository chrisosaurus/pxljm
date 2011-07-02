#ifndef CLIENTGAME_H
#define CLIENTGAME_H
#include <vector>


class Client;
class Planet;
class Player;
class Fleet;

class ClientGame {
    std::vector<Planet *> planets;

    std::vector<Player *> players;

    std::vector<Fleet *> fleets;

    Client *net;
public:
    ClientGame(const char *ip, int port = 45672);
    
    ~ClientGame();
    
    /**
     * Send a fleet of the specified amount from the source planet, heading towards a destination planet.
     */
    void launch_fleet(Planet &src, Planet &dest);
    
    /**
     * Find a planet based on id
     */
    Planet *planet_from_id(int id);
    
    /**
     * Find the closest planet to a specified location.
     * If limit is specified, do not return a Planet further away than the squareroot of this.
     */
    Planet *find_nearest_planet(int x, int y, int limit = 0);
};

#endif
