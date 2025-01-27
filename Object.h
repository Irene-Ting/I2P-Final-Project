#ifndef OBJECT_H_INCLUDED
#define OBJECT_H_INCLUDED

class Object {
public:
    Object() {}
    ~Object() {}

    // pure function for drawing object
    virtual void Draw() = 0;
};

#endif // OBJECT_H_INCLUDED
