class Mothership {
    const int x;
    const int y;

    int rotation;
public:
    Mothership(int posx, int posy);

    ~Mothership();

    int get_x() const { return x; }

    int get_y() const { return y; }

    int get_rotation() const { return rotation; }
};
    
