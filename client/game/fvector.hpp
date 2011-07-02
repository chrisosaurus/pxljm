#ifndef FVECTOR_H
#define FVECTOR_H

struct FVector {
  float x;
  float y;

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
