#include <math.h>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <iostream>
#include "mapper.hpp"

#define BORDER_THINKNESS 5

// game area size: 1024x600

// NOTE: I am NOT using client/game/planet
struct Planet {
  int x,y,r;
  Planet(int xx, int yy, int rr) : x(xx), y(yy), r(rr) { }
};

bool touching(Planet p, std::vector<Planet> &ps) {
  //is the distance greater than the sum of the radii?
  for (int i=0; i<ps.size(); ++i) 
    if (hypot(p.x-ps[i].x, p.y-ps[i].y) >= p.r + ps[i].r)
      return true;
  return false;
}

void generate_map(const char *fname = "generated.map", int maxPlanets=10, int averageSize=13) {  
  std::vector<Planet> planets;
  Planet centre(1024/2, 600/2, 3+(rand())%10);
  planets.push_back(centre); //add central planet
  
  int impossibleCounter;
  while (planets.size() < maxPlanets) {
    impossibleCounter=0;
    //(x,y,rad, player=8);
    Planet p(
      BORDER_THINKNESS+rand()%(1024-2*BORDER_THINKNESS),  // center X
      BORDER_THINKNESS+rand()%( 600-2*BORDER_THINKNESS),  // center Y
      3+rand()%10  //thickness
    );
    while (touching(p, planets) && impossibleCounter<=9001) { // retry anoter point
      ++impossibleCounter;
      p.x = BORDER_THINKNESS+rand()%(1024-2*BORDER_THINKNESS);  // center X
      p.y = BORDER_THINKNESS+rand()%( 600-2*BORDER_THINKNESS);  // center Y
      p.r = 3+rand()%10;  //thickness
    }
    
    if (impossibleCounter > 9000) return;   // over nine-thousand?!?
        
    planets.push_back(p);
    
    p.x = 1024/2 - p.x;
    p.x =  600/2 - p.x;
    if (touching(p, planets)) std::cout << "SYMETRY FAILED. YELL AT DOM! " << std::endl;
    planets.push_back(p);
  }
  
  // write to file
  std::ofstream out(fname);
  for (int i=0; i<planets.size(); ++i) {
    out << planets[i].x << " "
        << planets[i].y << " "
        << planets[i].r << " "
        << std::endl;
  }
  out.close();
}
