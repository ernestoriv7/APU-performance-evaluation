#include<math.h>
#include "transformations.h"

#define PIXELOFFSET 0.5
#define WINDOWMIN 0
#define ZW 0

Float getXw(Float x, Float Xmin, Float Xmax, int Hres);
Float getYw(Float y, Float Ymin, Float Ymax, int Vres);


int matrixOffset(int x, int y, int xsize){
    //return x * xsize + y;
    return y * xsize + x ;
}

Vector obtainNormalizedDirection(Float x, Float y)
{
    Float Yw= getYw((Float)y, WINDOWMIN, (Float)scene->dimy, (Float)scene->dimy);              
    Float Xw= getXw((Float)x, WINDOWMIN, (Float)scene->dimx, (Float)scene->dimx);     
    Vector dir = {Xw - scene->eye->x, Yw - scene->eye->y, ZW - scene->eye->z}; 
    return normalizedVector(&dir);

}

Float getXw(Float x, Float Xmin, Float Xmax, int Hres)
{    
    Float result = ((((Float)x+PIXELOFFSET)*(Xmax-Xmin))/(Float)Hres) + Xmin;
    return result;
}

Float getYw(Float y, Float Ymin, Float Ymax, int Vres)
{
    return ((((Float)y+PIXELOFFSET)*(Ymax-Ymin))/(Float)Vres) + Ymin;
}

Float vectorNorm(Vector *vect)
{
    return (Float)sqrt( (Float)vect->x*vect->x + (Float)vect->y*vect->y + (Float)vect->z*vect->z);
}

Vector normalizedVector(Vector *vec)
{    
    Vector normalized;
    Float L = vectorNorm(vec);
    normalized.x = vec->x/L;
    normalized.y = vec->y/L;
    normalized.z = vec->z/L;
    return normalized;    
}

Float dotProduct(Vector *vec1, Vector *vec2)
{
    return vec1->x * vec2->x + vec1->y * vec2->y + vec1->z * vec2->z;
}

Vector substractVector(Vector *vec1, Vector *vec2){
    Vector result;
    result.x = vec1->x - vec2->x;
    result.y = vec1->y - vec2->y;
    result.z = vec1->z - vec2->z;
    return result;
}

Vector addVector(Vector *vec1, Vector *vec2){
    Vector result;
    result.x = vec1->x + vec2->x;
    result.y = vec1->y + vec2->y;
    result.z = vec1->z + vec2->z;
    return result;
}

Vector intersectionPoint(Ray *rayo, Float t){
    
    Vector intersection;
    intersection.x = rayo->origin.x + t*(rayo->direction.x);
    intersection.y = rayo->origin.y + t*(rayo->direction.y);
    intersection.z = rayo->origin.z + t*(rayo->direction.z);
    return intersection;

}

Vector lightVectorL(Vector intersection, Vector light){
     
    Vector retorno = substractVector(&light, &intersection);
    return normalizedVector(&retorno);

}

Vector inverseVector(Vector *vec1, Vector *vec2){
    Vector result = substractVector(vec1, vec2);
    return normalizedVector(&result);
}

Vector reflexVector(Vector *L, Vector *N){
    Vector result;
    Float pdot = dotProduct(N, L);
    result.x = N->x*2*pdot;
    result.y = N->y*2*pdot;
    result.z = N->z*2*pdot;
    result =  substractVector(&result, L); 
    return normalizedVector(&result);    
}

Float difuseLight(Vector *L, Vector *N, Vector *intersection,  Float Ip, 
                 Float kd){
   // Vector result = substractVector(light->position, intersection);    
   // Float raydistance =    getVectorNorm(&result);
    Float Fatt = 1;//fmin(1.0, 1/(light->C.x +light->C.y*raydistance + light->C.z*raydistance*raydistance));
    Float I = dotProduct(L, N)*kd*Ip*Fatt;
    if (I<0){
        return 0;
    }
    else return fmin(1.0,  I );
}


Vector difuseColor(Vector *intersection, Float difuse){
    Vector result;
    result.x = intersection->x *difuse;
    result.y = intersection->y *difuse;
    result.z = intersection->z *difuse;
    return result;
}

Vector specularColor(Vector *diff, Float specular){
    Vector result;
    result.x = diff->x + specular*(1.0-diff->x);
    result.y = diff->y + specular*(1.0-diff->y);
    result.z = diff->z + specular*(1.0-diff->z);
    return result;
}

Float specularLight(Vector *V, Vector *R, Vector *intersection, Float Ip, 
                    Float kn, Float ks){
   // printf("The value of the light is %f\n", light->Ip);
  //  Vector result = substractVector(light->position, intersection);    
    Float power= kn;
   // Float raydistance = getVectorNorm(&result);
    Float Fatt = 1;//fmin(1.0, 1/(light->C.x +light->C.y*raydistance + light->C.z*raydistance*raydistance));
    Float I = dotProduct(V, R);
        
    if (I<0) {
        return 0;
    }
    else{
        I = pow(I,power)*Ip*Fatt*ks;
        return fmin(1.0,  I); 
    } 
}



Vector crossProduct(Vector *vec1, Vector *vec2)
{
    Vector returnval;
 
    returnval.x = (vec1->y * vec2->z) - (vec2->y * vec1->z);
    returnval.y = (vec2->x * vec1->z) - (vec1->x * vec2->z);
    returnval.z = (vec1->x * vec2->y) - (vec2->x * vec1->y);
    
    return returnval;
     
}

Float angleBetweenVectors(Vector one, Vector two)
{

    Float dot = one.x*two.x + one.y*two.y + one.z*two.z; 
    Float lenSq1 = one.x*one.x + one.y*one.y + one.z*one.z;
    Float lenSq2 = two.x*two.x + two.y*two.y + two.z*two.z;
    Float angle = acos(dot/sqrt(lenSq1 * lenSq2));
    return angle*(180/3.12);

}

Vector negateVector(Vector *vec)
{
    
    Vector negated;
    negated.x = -vec->x;
    negated.y = -vec->y;
    negated.z = -vec->z;
    return negated;    
}

Vector obtainPositiveNormal(char *type, Vector N, Vector L){
    Vector normalcorrect = N;
    if(strcmp(type,"sphere")== 0){
        return normalcorrect; 
    } else if(dotProduct(&L, &N) < 0-epsilom){
         normalcorrect = negateVector(&N);
    }
    return normalcorrect;
}

Vector multiplyConstantVector(Float constant, Vector vec){
    Vector returnvec;
    returnvec.x = vec.x * constant;
    returnvec.y = vec.y * constant;
    returnvec.z = vec.z * constant;

    return returnvec;
}

