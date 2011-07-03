#ifndef PLAYER_H
#define PLAYER_H
class Mothership;
class Player{
    const int UID;
    Mothership *moship;
    bool dead;
public:
    Player(int uid) : UID(uid), dead(false), moship(0) {}
    int get_uid() const { return UID; }
    Mothership *get_moship() const { return moship; }
    void set_moship(Mothership *m) { moship = m; }
    void mark_dead() { dead = true; }
    bool check_dead() const { return dead; }
};

extern Player *local_player;

#endif
