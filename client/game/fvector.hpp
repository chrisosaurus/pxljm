#ifndef FVECTOR_H
#define FVECTOR_H

#include <math.h>

struct FVector {
  float x;
  float y;

  float mag() {
    return hypot(x, y);
  }

  float dist(FVector& b) {
    return hypot(x-b.x, y-b.y);
  }

  void norm() {
    float magnitude = mag();
    x /= magnitude;
    y /= magnitude;
  }

  void limit(float max) {
    float magnitude = mag();
    if (magnitude <= max) return;
    norm();
    x *= max;
    y *= max;
  }

  FVector operator=(FVector &b){
    x = b.x;
    y = b.y;
    return *this;
  }

  FVector operator+(FVector &b){
    FVector n;
    n.x = x + b.x;
    n.y = y + b.y;
    return n;
  }
  FVector operator-(FVector &b){
    FVector n;
    n.x = x - b.x;
    n.y = y - b.y;
    return n;
  }

  FVector operator*(float mult){
    FVector n;
    n.x = x * mult;
    n.y = y * mult;
    return n;
  }
  FVector operator/(float div){
    FVector n;
    n.x = x / div;
    n.y = y / div;
    return n;
  }
  
  
  // composite Operators
  FVector& operator+=(FVector &b){
    x += b.x;
    y += b.y;
    return *this;
  }
  FVector& operator-=(FVector &b){
    x -= b.x;
    y -= b.y;
    return *this;
  }
  FVector& operator*=(float mult){
    x *= mult;
    y *= mult;
    return *this;
  }
  FVector& operator/=(float div){
    x /= div;
    y /= div;
    return *this;
  }

};

#endif
