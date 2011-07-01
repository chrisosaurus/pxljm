#ifndef PLAYER_H
#define PLAYER_H
class Mothership;
class Player{
  int UID;
  Mothership *moship;
  public:
    Player(int uid, Mothership *mother) : UID(uid) {moship = mother; }
    int get_uid() { return UID; }
    Mothership* get_moship() { return moship; }
};
#endif
