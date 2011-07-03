#include "../game/ship.hpp"
#include "../game/fleet.hpp"
#include "../game/planet.hpp"
#include "../game/game.hpp"
#include "../game/mothership.hpp"
#include "../game/player.hpp"
#include "interfacing.hpp"

#include <sstream>
#include <string>

#define PI 3.14

#define MINDFUCK 1

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
      bgimage.LoadFromFile("bg.png");
      bg.SetImage(bgimage);
      me = p;
      window.SetFramerateLimit(60);
}

void Interfacing::draw(std::vector<Planet*> &planets, std::vector<Fleet*> &fleets){
  window.Clear();
  window.Draw(bg); // TODO bg all white >.>

  unsigned int frametime = window.GetFrameTime();
  unsigned int gametime = clock.GetElapsedTime(); // TODO to be consistant, is this ok?
  
  std::vector<Fleet*> deletemes;

  // draw ships first
  for( int i=0; i<fleets.size(); ++i){
    sf::Shape ship;
    Fleet &fleet = *fleets[i];
    sf::Color c = colour_from_uid(fleet.owner.get_uid());
    int del = fleet.update(me->get_moship()->get_x(), me->get_moship()->get_y(), gametime, frametime);
    //window.Draw(sf::Shape::Circle(fleet.screenX, fleet.screenY, 20, sf::Color::Red)); // TODO debugging
    if(del > 0){
      deletemes.push_back(fleets[i]);
      continue;
    }
    //std::cout << std::endl << std::endl << " drawing a fleet " << fleet.screenX << ", " << fleet.screenY << std::endl;
    //std::cout << "owner of fleet to be drawn : " << fleet.owner.get_uid();
    for( int j=0; j<fleet.ships.size(); ++j){
#if MINDFUCK
      sf::Shape ship;
#endif
      Ship * s = fleet.ships[j];
      if(!s) continue;
      //std::cout << "drawing a shippity doo daa " << s->screenX << "," << s->screenY << " : " << s<< std::endl;
      ship.AddPoint(s->screenX+1, s->screenY,   c, c);
      ship.AddPoint(s->screenX-3, s->screenY-2, c, c);
      ship.AddPoint(s->screenX-3, s->screenY+2, c, c);
      ship.EnableFill(false);
      ship.SetOutlineThickness(1);
      ship.Rotate(s->rot * PI/180); // oh god, it burns! also: PI is exactly 3
      window.Draw(ship);
    }
  }

  for( int i=0; i<deletemes.size(); ++i)
    game.remove_fleet(deletemes[i], gametime);

  for( int i=0; i<planets.size(); ++i) {
    const Player * p = planets[i]->get_player();
    std::stringstream ss;
    ss << planets[i]->get_ship_count(gametime);
    draw_string( ss.str(), planets[i]->get_x(), planets[i]->get_y(), planets[i]->get_radius());
    planets[i]->draw(window, colour_from_uid(p ? p->get_uid() : -1));
    if(planets[i]->get_player()->get_uid() == me->get_uid())
      window.Draw(sf::Shape::Circle(planets[i]->get_x(), planets[i]->get_y(), planets[i]->get_radius(), colour_from_uid(planets[i]->get_player()->get_uid()), 0, colour_from_uid(planets[i]->get_player()->get_uid())));
  }

  window.Display();
}

void Interfacing::draw_string(const std::string &val, int x, int y, int offset){
  sf::Text text(val);
  text.SetX(x);
  text.SetY(y);
  window.Draw(text);
  //window.Display(); // TODO possibly remove, depending if public or private (if priv, dont need)
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
      if(event.Type == sf::Event::Closed){
        die();
        window.Close();
      }else if((event.Type == sf::Event::KeyPressed) && (event.Key.Code == sf::Key::Escape)){
        die();
        window.Close();
      }

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
      // a left click could be an action
      if( ly > 0){ // omg, DO SOMETHING
        Planet *p = game.find_nearest_planet(lx, ly, 1);
        if(p){
          //if( p->get_player() != me )
          //  continue; // skip this
          // planet in the from, is there a plen in the too
          Planet *p2 = game.find_nearest_planet(mx, my, 1);
          // send event, or ignore
          if(p!=p2 && p2){
            
            //std::cout << "checking if I own the from " << p << " thats p, me is " << me << "and player is" << p->get_player() << std::endl;
            if( !p->get_player() || p->get_player()->get_uid() != me->get_uid() ){
              ly = -1, lx = -1;
              continue;
            }
            
            //std::cout << "I should be launcing a fleet" << std::endl;
            game.launch_fleet(*p, *p2, clock.GetElapsedTime());
            mx=-1, my=-1, lx=-1, ly=-1;
            //std::cout << "launched!" << std::endl;
            // give dest planet a green border
            sf::Shape s = sf::Shape::Circle(p2->get_x(), p2->get_y(), p2->get_radius(), sf::Color::Black, 2, sf::Color::Green);
            s.EnableFill(false);
            window.Draw(s);
            window.Display();
          } /*else {
            sf::Shape s = sf::Shape::Circle(p2->get_x(), p2->get_y(), p2->get_radius(), sf::Color::Black, 2, sf::Color::Red);
            s.EnableFill(false);
            window.Draw(s);
            window.Display();
          }*/
        } else {
          // no planet in the from position, so no event can happen
          lx = mx;
          ly = my;
          //highlight the planet clicked just for shits and giggles
          Planet *p = game.find_nearest_planet(lx,ly, 1);
          if( p && p->get_player() && p->get_player()->get_uid() == me->get_uid() ){ // red outline
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
        //std::cout << "nothing last frame, recording" << std::endl;
        if( p && p->get_player() && p->get_player()->get_uid() == me->get_uid() ){ // red outline
            //if( p->get_player() != me )
            //  continue;
            sf::Shape s = sf::Shape::Circle(p->get_x(), p->get_y(), p->get_radius(), sf::Color::Black, 2, sf::Color::Red);
            s.EnableFill(false);
            window.Draw(s);
            window.Display();
        }
      }
    } else if(input.IsMouseButtonDown(sf::Mouse::Right)){
      // a right click "empties" the stack"
      lx=-1;
      ly=-1;
    }
    
    game.logic(*this);
  }
}

void Interfacing::die(){
  game.die();
}
