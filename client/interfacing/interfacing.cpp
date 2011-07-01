#include <SFML/Graphics.hpp>
#include <interfacing.hpp>

#define pi 3.14

Interfacing::Interfacing(ClientGame& ga)
  : window(sf::VideoMode(1024, 600), "awesome title of doom", sf::Style::Close), game(ga) {
}

// TODO we prob won't be using a vector<Mothership> but a vector<Player> and then a pointer through them
void Interfacing::draw(const std::vector<Planet> &planets, const std::vector<Mothership> &moships, const std::vector<Fleet> &fleets){
  window.Clear();

  // draw ships first
  for( int i=0; i<ships.size(); ++i){
    sf::Shape ship;
    // TODO adjust colour based on player
    sf::Color c = sf::Color::Red;
    ship.AddPoint(ships[i].screenX+1, ships[i].screenY,   c, c);
    ship.AddPoint(ships[i].screenX-1, ships[i].screenY-1, c, c);
    ship.AddPoint(ships[i].screenX-1, ships[i].screenY+1, c, c);
    ship.EnableFill(false);
    ship.Rotate(ships[i].rot * PI/180); // oh god, it burns! also: PI is exactly 3
    window.Draw(ship);
  }

  for( int i=0; i<planets.size(); ++i){
    sf::Color c = sf::Color::Blue; // TODO define per player
    sf::Shape planet = sf::Shape::Circle(planets[i].get_x(), planets[i].get_y(), planets[i].get_radius(), c, 0, c); // TODO handle highlighting later
    window.Draw(planet);
    // TODO draw planets here
  }

  // TODO watch this space, moship will prob become player
  for( int i=0; i<moships.size(); ++i){
    sf::Color c = sf::Color::Green; // TODO define per player and/or make a better moship
    sf::Shape moship;
    moship.AddPoint(moship[i].get_x()+2, moship[i].get_y(), c, c);
    moship.AddPoint(moship[i].get_x()-2, moship[i].get_y()-2, c, c);
    moship.AddPoint(moship[i].get_x()-2, moship[i].get_y()+2, c, c);
    moship.EnableFill(false);
    moship.Rotate(moship[i].get_rotation());
    window.Draw(moship);
    // TODO draw moships here
  }

  window.Display();
}

void Interfacing::draw_string(const std::string &val, int x, int y){
  sf::Text text(val);
  text.SetX(x);
  text.SetY(y);
  window.Draw(text);
  window.Display(); // TODO possibly remove, depending if public or private (if priv, dont need)
}

// THE main loop xD (also most of the glue)
void Interfacing::main(){
  const sf::Input &input = window.GetInput();
  sf::Event event;
  int mx=-1, my=-1, lx=-1, ly=-1; // mouse x and y this frame (only used if clicked), last x and y when mouse was clicked

  // go go go !
  while(window.IsOpened()){
    // check for closing events
    while(window.PollEvent(event))
      if(Event.Type == sf::Event::Closed)
        window.Close();
      else if((Event.Type == sf::Event::KeyPressed) && (event.Key.Code == sf::Key::Escape))
        window.close();

    // if we are here, we are alive!
    mx = input.GetMouseX();
    my = input.GetMouseY();
    // a left click either means:
    //    if there was a click last frame:
    //      make an event happen
    //    otherwise:
    //      record a click
    // a right click means: delete the click if it was recorded last frame
    if(input.IsMouseButtonDown(sf::Mouse::Right)){
      // a left click could be an action
      if( ly > 0){ // omg, DO SOMETHING
        Planet *p = game.find_nearest_planet(lx, ly);
        if(p){
          // planet in the from, is there a plen in the too
          Planet *p2 = game.find_nearest_planet(mx, my);
          // send event, or ignore
          if(p2)
            game.launch_fleet(*p, *p2);
        } else {
          // no planet in the from position, so ignore it
          lx = mx;
          ly = my;
        }
      } else { // if we didn't record last frame, record
        lx = mx;
        ly = my;
      }
    } else if(input.IsMouseButtonDown(sf::Mouse::Right)){
      // a right click "empties" the stack"
      lx=-1;
      ly=-1;
    }

  }
}
