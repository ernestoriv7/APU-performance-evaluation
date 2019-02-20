#ifndef _methods_h
#define _methods_h

#include "list.h"
#include "transformations.h"
#include "shapes.h"
#include "opencltracer.h"

Vector whichColorIsIt(Ray *ray, int x, int y);
Vector antialiasColor(int x, int y);
Vector recoverIntersectionColor(Float  tvalue, Ray *ray, GenericShape *object, 
                                Scene *scene, int levels, int transparencies);

#endif
