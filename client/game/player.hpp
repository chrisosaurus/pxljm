#ifndef PLAYER_H
#define PLAYER_H
class Mothership;
class Player{
    const int UID;
    Mothership *moship;
public:
    Player(int uid) : UID(uid), moship(0) {}
    int get_uid() const { return UID; }
    Mothership *get_moship() const { return moship; }
    void set_moship(Mothership *m) { moship = m; }
};

extern Player *local_player;

#endif
