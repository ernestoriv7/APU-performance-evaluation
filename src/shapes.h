#ifndef _cputracer_h
#define _cputracer_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include"transformations.h"
#include"bounding.h"





typedef struct{
    Float radius;
}SphereAditionalData;

typedef struct{
    Float radius;
    Vector * direction;
    Float d1;
    Float d2;
}CylinderAditionalData;

typedef struct{
    Vector * direction;
    Float d1;
    Float d2;
    Float k1;
    Float k2;
}ConeAditionalData;

typedef struct{
    Float radius;
    Vector * direction;
    Plane plane;
    int intersectionType;
}DiscAditionalData;

typedef struct TriangleSpecificData {
    Vector * rotation;
    Vector * translation;
    Vector points[3];
    Plane plane;
    int intersectionType;
}TriangleSpecificData;


Float intersectsSphere(Ray *rayo, GenericShape *sphere);
Float intersectsCylinder(Ray *rayo, GenericShape *cylinder);
Float intersectsCone(Ray *rayo, GenericShape *cone);
Float intersectsDisc(Ray *rayo, GenericShape *disc);
Float intersectsPlane(Ray *rayo, Plane *plane);
Float intersectsTriangle(Ray *rayo, GenericShape *triangle);
Float intersectsBox(Ray *r, Bbox *b);
Float getIntersection(Ray *rayscene, GenericShape *primitive);

Vector normalVectorSphere(Vector intersection, Vector center, Float radius);
Vector normalVectorCylinder(Vector intersection, Vector center, Vector direction,  Float radius);  
Vector normalVectorCone(Vector intersection, Vector center, Vector direction); 
Vector normalVectorPlane(Vector *v0, Vector *v1, Vector *v2);
Vector normalVectorDisc(Plane data);
Vector normalVectorTriangle(Plane data);
Vector crossProductPlane(Vector *vec1, Vector *vec2, Vector *vec3);
Plane getNormalizePlane(Vector *point, Vector *abc);
Vector objectNormal(Vector intersection, GenericShape object);

Bbox sphereBox(GenericShape esfera);
Bbox cylinderBox(GenericShape cylinder);
Bbox coneBox(GenericShape cone);
Bbox discBox(GenericShape disc);
Bbox triangleBox(GenericShape triangle);

#endif
