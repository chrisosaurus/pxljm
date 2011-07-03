#include <algorithm>
#include <functional>

#include "game.hpp"

#include "../interfacing/interfacing.hpp"
#include "../networking/client.hpp"
#include "fleet.hpp"
#include "planet.hpp"
#include "player.hpp"


ClientGame::ClientGame(const char *ip, int port) : net(new NetworkingClient(ip, port))  {}

ClientGame::~ClientGame() {}

void ClientGame::set_game(){
    net->init(this);
    net->join();
}

void ClientGame::die() {
    net->send_fleet(0);
}

void ClientGame::launch_fleet(Planet &src, Planet &dest, int timestamp) {
    if (!src.get_player() || src.get_player()->check_dead())
        return;
    Fleet *f = src.launch_fleet(dest, timestamp);
    if (&f->owner == local_player)
        net->send_fleet(f);
    fleets.push_back(f);
    std::multimap<int, std::pair<int, int> >::iterator it = history.insert(history.empty() ? history.begin() : --history.end(), std::make_pair(timestamp, std::make_pair(src.get_id(), dest.get_id()))); /* Should almost always be at the end (Race conditions otherwise, whee) */
    if (it == --history.end())
        return; /* New end - no history propogation required. */
    /* FIXME - Out of sync, recompute as needed to fix potential issues (yay, race conditions) */
}

void ClientGame::launch_fleet(int pid1, int pid2, int timestamp){
    launch_fleet(*planet_from_id(pid1), *planet_from_id(pid2), timestamp);
}

void ClientGame::remove_fleet(Fleet *f, int timestamp) {
    if (!f->owner.check_dead())
        f->dest.ships_arrival(&f->owner, int(f->ships.size()), timestamp);
    /* This should really use a set */
    std::vector<Fleet *>::iterator it = std::find(fleets.begin(), fleets.end(), f);
    if (it != fleets.end())
        fleets.erase(it);
}

void ClientGame::add_planet(Planet *p) {
    planets.push_back(p);
}

void ClientGame::add_player(Player *p) {
    players.push_back(p);
}

struct pid : std::binary_function <Planet *, int, bool> {
    bool operator () (const Planet * const p, int id) const {
        return p->get_id() == id;
    }
};

Planet *ClientGame::planet_from_id(int id) {
    std::vector<Planet *>::iterator p = std::find_if(planets.begin(), planets.end(), std::bind2nd(pid(), id));
    return p == planets.end() ? 0 : *p;
}

struct SData {
    int x, y, limit;
    SData(int vx, int vy, int vlimit) : x(vx), y(vy), limit(vlimit) {}
};

Planet *ClientGame::find_nearest_planet(int x, int y, int limit) {
    int min_d2, d2, dx, dy;
    Planet *p = 0;
    for (std::vector<Planet *>::iterator it = planets.begin(), it_end = planets.end(); it != it_end; ++it) {
        dx = std::max(std::abs((*it)->get_x() - x) - (*it)->get_radius(), 0);
        dy = std::max(std::abs((*it)->get_y() - y) - (*it)->get_radius(), 0);
        d2 = dx*dx + dy*dy;
        if ((!p || d2 < min_d2) && (!limit || d2 < limit)) {
            p = *it;
            min_d2 = d2;
        }
    }
    return p;
}

bool eid (const Player * const p) {
    return !p->check_dead();
}

void ClientGame::logic(Interfacing &i) {
    net->receive_packet();
    if (std::count_if(players.begin(), players.end(), eid) == 1)
        i.end_game((*std::find_if(players.begin(), players.end(), eid))->get_uid());
    i.draw(planets, fleets);
}
