#ifndef _bounding_h
#define _bounding_h

#include"globaldefs.h"
#include"transformations.h"
#include"shapes.h"

Bbox createBox(Vector *p1, Vector *p2);
Vector corner(int corner);
Bbox unionBoxBox(Bbox *box1, Bbox *box2);
Bbox unionBoxPoint(Bbox *box, Vector *point);
Bbox getBoundingBox(GenericShape shape);
int maximumExtendBox(Bbox *box);
#endif

