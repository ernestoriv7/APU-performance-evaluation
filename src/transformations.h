#ifndef _transformations_h
#define _transformations_h

#include "globaldefs.h"

int matrixOffset(int x, int y, int xsize);
Float vectorNorm(Vector *vect);
Float dotProduct(Vector *vec1, Vector *vec2);
Vector normalizedVector(Vector *vec);
Vector substractVector(Vector *vec1, Vector *vec2);
Vector addVector(Vector *vec1, Vector *vec2);
Vector intersectionPoint(Ray *rayo, Float t);      
Vector reflexVector(Vector *L, Vector *N);
Vector inverseVector(Vector *vec1, Vector *vec2);
Vector negateVector(Vector *vec);
Vector crossProduct(Vector *vec1, Vector *vec2);
Vector multiplyConstantVector(Float constant, Vector vec);

Vector lightVectorL(Vector intersection, Vector light);
Float difuseLight(Vector *L, Vector *N, Vector *intersection,  Float Ip, 
                 Float kd);
Vector difuseColor(Vector *intersection, Float difuse);
Vector specularColor(Vector *diff, Float specular);
Float specularLight(Vector *V, Vector *R, Vector *intersection, Float Ip, 
                    Float kn, Float ks);


Vector obtainNormalizedDirection(Float x, Float y);
Float angleBetweenVectors(Vector one, Vector two);
Vector obtainPositiveNormal(char *type, Vector N, Vector L);



#endif
