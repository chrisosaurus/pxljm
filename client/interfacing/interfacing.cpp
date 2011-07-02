#include "../game/ship.hpp"
#include "../game/fleet.hpp"
#include "../game/planet.hpp"
#include "../game/game.hpp"
#include "../game/mothership.hpp"
#include "../game/player.hpp"
#include "interfacing.hpp"

#define PI 3.14

sf::Color Interfacing::colour_from_uid(int uid){
  switch(uid){
    case 0:
      return sf::Color(255, 128, 0); // ornage
    case 1:
      return sf::Color::White;
    case 2:
      return sf::Color::Red;
    case 3:
      return sf::Color::Green;
    case 4:
      return sf::Color::Blue;
    case 5:
      return sf::Color::Yellow;
    case 6:
      return sf::Color::Magenta;
    case 7:
      return sf::Color::Cyan;
    default:
      return sf::Color(128,128,128);; // error or unowned(grey)
  }
}

Interfacing::Interfacing(ClientGame& ga, Player *p)
  : window(sf::VideoMode(1024, 600), "awesome title of doom", sf::Style::Close),
    game(ga) {
      me = p;
      window.SetFramerateLimit(60);
}

void Interfacing::draw(std::vector<Planet*> &planets, std::vector<Player*> &players, std::vector<Fleet*> &fleets){
  window.Clear();

  unsigned int frametime = window.GetFrameTime();
  unsigned int gametime = clock.GetElapsedTime(); // TODO to be consistant, is this ok?
  
  // draw ships first
  for( int i=0; i<fleets.size(); ++i){
    sf::Shape ship;
    Fleet &fleet = *fleets[i];
    sf::Color c = colour_from_uid(fleet.owner.get_uid());
    fleet.update(me->get_moship()->get_x(), me->get_moship()->get_y(), gametime, frametime);
    for( int j=0; j<fleet.ships.size(); ++j){
      Ship * s = fleet.ships[i];
      ship.AddPoint(s->screenX+1, s->screenY,   c, c);
      ship.AddPoint(s->screenX-1, s->screenY-1, c, c);
      ship.AddPoint(s->screenX-1, s->screenY+1, c, c);
      ship.EnableFill(false);
      ship.Rotate(s->rot * PI/180); // oh god, it burns! also: PI is exactly 3
      window.Draw(ship);
    }
  }

  for( int i=0; i<planets.size(); ++i){
    const Player * p = planets[i]->get_player();
    sf::Color c = colour_from_uid( p ? p->get_uid() : 0 ); // defaults to grey, for unowned.
    sf::Shape planet = sf::Shape::Circle(planets[i]->get_x(), planets[i]->get_y(), planets[i]->get_radius(), c, 0, c);
    window.Draw(planet);
  }

  for( int i=0; i<players.size(); ++i){
    sf::Color c = colour_from_uid(players[i]->get_uid());
    sf::Shape moship;
    Mothership *ms = players[i]->get_moship();
    moship.AddPoint(ms->get_x()+2, ms->get_y(), c, c);
    moship.AddPoint(ms->get_x()-2, ms->get_y()-2, c, c);
    moship.AddPoint(ms->get_x()-2, ms->get_y()+2, c, c);
    moship.EnableFill(false);
    moship.Rotate(ms->get_rotation());
    window.Draw(moship);
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
    //sf::Sleep(10);
    // check for closing events
    while(window.PollEvent(event))
      if(event.Type == sf::Event::Closed)
        window.Close();
      else if((event.Type == sf::Event::KeyPressed) && (event.Key.Code == sf::Key::Escape))
        window.Close();

    // if we are here, we are alive!
    mx = input.GetMouseX();
    my = input.GetMouseY();
    // a left click either means:
    //    if there was a click last frame:
    //      make an event happen
    //    otherwise:
    //      record a click
    // a right click means: delete the click if it was recorded last frame
    if(input.IsMouseButtonDown(sf::Mouse::Left)){
      std::cout << "left click!" << std::endl;
      // a left click could be an action
      if( ly > 0){ // omg, DO SOMETHING
        Planet *p = game.find_nearest_planet(lx, ly, 1);
        if(p){
          std::cout << "found a planet under the last click" << std::endl;
          // planet in the from, is there a plen in the too
          Planet *p2 = game.find_nearest_planet(mx, my, 1);
          // send event, or ignore
          if(p2){
            std::cout << "found a second planet under the recent click" << std::endl;
            game.launch_fleet(*p, *p2, clock.GetElapsedTime());
            // give dest planet a green border
            sf::Shape s = sf::Shape::Circle(p2->get_x(), p2->get_y(), p2->get_radius(), sf::Color::Black, 2, sf::Color::Green);
            s.EnableFill(false);
            window.Draw(s);
            window.Display();
          }
        } else {
          std::cout << "no planet under my last click" << std::endl;
          // no planet in the from position, so no event can happen
          lx = mx;
          ly = my;
          //highlight the planet clicked just for shits and giggles
          Planet *p = game.find_nearest_planet(lx,ly, 1);
          if(p){ // red outline
            sf::Shape s = sf::Shape::Circle(p->get_x(), p->get_y(), p->get_radius(), sf::Color::Black, 2, sf::Color::Red);
            s.EnableFill(false);
            window.Draw(s);
            window.Display();
          }
        }
      } else { // if we didn't record last frame, record
        lx = mx;
        ly = my;
        Planet *p = game.find_nearest_planet(lx,ly);
        if(p){ // highlight planet with red outline
            sf::Shape s = sf::Shape::Circle(p->get_x(), p->get_y(), p->get_radius(), sf::Color::Black, 2, sf::Color::Red);
            s.EnableFill(false);
            window.Draw(s);
            window.Display();
        }
      }
    } else if(input.IsMouseButtonDown(sf::Mouse::Right)){
      std::cout << "right click!" << std::endl;
      // a right click "empties" the stack"
      lx=-1;
      ly=-1;
    }
    
    game.logic(*this);
  }
}
