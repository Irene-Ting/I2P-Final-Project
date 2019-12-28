#ifndef OBJECT_H_INCLUDED
#define OBJECT_H_INCLUDED

#include "Square.h"

class Object {
public:
    Object() {}
    ~Object() {}

    // pure function for drawing object
    virtual void Draw() = 0;

    int getX() { return square->x; }
    int getY() { return square->y; }
    int getRadius() { return square->r; }

    Square* getSquare() const { return square; }

protected:
    Square *square;

};

#endif // OBJECT_H_INCLUDED
