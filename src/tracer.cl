//#pragma OPENCL EXTENSION cl_khr_fp64 : enable

//++++++++++++++++++DEFINES++++++++++++++++++++++++++
#define EPSILOM 0.005
#define PIXELOFFSET 0.5
#define WINDOWMIN 0
#define ZW 0
#define ON 1
#define OFF 0

//+++++++++++++++++++++++++++++TYPEDEFS++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++TYPEDEFS++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++TYPEDEFS++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++TYPEDEFS++++++++++++++++++++++++++++++++++++++++

typedef double Float;

typedef struct Vector{
	Float x;
	Float y;
	Float z;
}Vector;


typedef struct Ray{
    Vector origin;
    Vector direction;
}Ray;

typedef struct Bbox{  
    Vector pMin;
    Vector pMax;
} Bbox;

typedef struct Plane{
    Float A;
    Float B;
    Float C;
    Float D;
}Plane;

typedef struct LinearBVHNode {
    Bbox bounds;
    union {
        int primitivesOffset;   // leaf
        int secondChildOffset;  // interior
    };
    ushort nPrimitives;  // 0 -> interior node
    uchar axis;          // interior node: xyz
    uchar pad[1];        // ensure 32 byte total size
}LinearBVHNode;

typedef struct GenericShape{
    int shapetype; //enum: sphere, cyl, cone, disc, triangle    
    Vector position; // sphere, cil, cone, disc
    Float rad; // sphere, cill, disc
    Vector vec0; //cyl, cone and disc: direction, triangle: point 1 
    Plane cnst; //cil: d1, d2, cone: d1, d2, k1, k2, disc and triangle
                                                        //plane
    Vector vec1; // triangle point 2
    Vector vec2; // triangle point 3
    //++++++++Added to pass everything to the GPU+++++++++
    Vector color;
    Float ka;
    Float kn;
    Float kd;
    Float ks;
    Float fatt;
    Float o1;
    Float o2;
    Float o3;   
    Float Ip;
    Float Ia; 
} GenericShape;

typedef struct{  
    Float t;
    int position;
} Interinfo;

typedef struct nodesTree{  
    Ray ray;
    int parentpos;
    Interinfo inter;
    int colortype;
    Vector color;
    int levels;
    int transparencies;
    Float intensitydif;
    Float intensityspe;
} nodesTree;

typedef struct ReturnGPU{  
    Interinfo inteserct;
    Ray ray;
    int x;
    int y;
    Vector color;
    int valid;
    int rays;
} ReturnGPU;

typedef struct SceneLights{  
    Vector par;
    Float val;
} SceneLights;

typedef struct SceneInfo{  
    int sizeLights;
    int levels;
    int transparencies;
    int antialiasing;
    int acceleration;
    int sizeScene;
    int dimx;
    int dimy;
    Vector eye;
} SceneInfo;

typedef struct{
    int xstart; 
    int xfinish;
    int ystart;
    int yfinish;      
} WorkDispatch;



//++++++++++++++++++++++++++AUXILIAR FUNCTIONS++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++AUXILIAR FUNCTIONS++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++AUXILIAR FUNCTIONS++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++AUXILIAR FUNCTIONS++++++++++++++++++++++++++++++++++

Vector intersectionPoint(Ray rayo, Float t){
    
    Vector intersection;
    intersection.x = rayo.origin.x + t*(rayo.direction.x);
    intersection.y = rayo.origin.y + t*(rayo.direction.y);
    intersection.z = rayo.origin.z + t*(rayo.direction.z);
    return intersection;

}



Float getXw(Float x, Float Xmin, Float Xmax, int Hres)
{    
    return ((((Float)x+PIXELOFFSET)*(Xmax-Xmin))/(Float)Hres) + Xmin;
}

Float getYw(Float y, Float Ymin, Float Ymax, int Vres)
{
    return ((((Float)y+PIXELOFFSET)*(Ymax-Ymin))/(Float)Vres) + Ymin;
}


Float vectorNorm(Vector *vect)
{
    return (Float)sqrt( (Float)vect->x*vect->x + (Float)vect->y*vect->y + 
            (Float)vect->z*vect->z);
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

Vector obtainNormalizedDirection(Vector eye, Float x, Float y, int dimx, 
                                 int dimy)
{
    Float Yw= getYw((Float)y, WINDOWMIN, (Float)dimy, (Float)dimy);              
    Float Xw= getXw((Float)x, WINDOWMIN, (Float)dimx, (Float)dimx);     
    Vector dir = {Xw - eye.x, Yw - eye.y, ZW - eye.z}; 
    return normalizedVector(&dir);

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

Vector negateVector(Vector *vec)
{
    
    Vector negated;
    negated.x = -vec->x;
    negated.y = -vec->y;
    negated.z = -vec->z;
    return negated;    
}

Vector crossProduct(Vector *vec1, Vector *vec2)
{
    Vector returnval;
 
    returnval.x = (vec1->y * vec2->z) - (vec2->y * vec1->z);
    returnval.y = (vec2->x * vec1->z) - (vec1->x * vec2->z);
    returnval.z = (vec1->x * vec2->y) - (vec2->x * vec1->y);
    
    return returnval;    
}

void swap(Float *a, Float *b)
{
   Float t; 
   t  = *b;
   *b = *a;
   *a = t;
}


Vector inverseVector(Vector *vec1, Vector *vec2){
    Vector result = substractVector(vec1, vec2);
    return normalizedVector(&result);
}

Vector lightVectorL(Vector intersection, Vector light){
    Vector retorno = substractVector(&light, &intersection);
    return normalizedVector(&retorno);
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

Vector multiplyConstantVector(Float cnst, Vector vec){
    Vector returnvec;
    returnvec.x = vec.x * cnst;
    returnvec.y = vec.y * cnst;
    returnvec.z = vec.z * cnst;

    return returnvec;
}

Vector addVector(Vector *vec1, Vector *vec2){
    Vector result;
    result.x = vec1->x + vec2->x;
    result.y = vec1->y + vec2->y;
    result.z = vec1->z + vec2->z;
    return result;
}

Float difuseLight(Vector *L, Vector *N, Vector *intersection, Float Ip, 
                  Float kd)
{
    Float Fatt = 1;
    Float I = dotProduct(L, N)*kd*Ip*Fatt;
    if (I<0){
        return 0;
    }
    else return fmin(1.0,  I );
}

Vector difuseColor(Vector *intersection, Float difuse)
{
    Vector result;
    result.x = intersection->x *difuse;
    result.y = intersection->y *difuse;
    result.z = intersection->z *difuse;
    return result;
}

Vector specularColor(Vector *diff, Float specular)
{
    Vector result;
    result.x = diff->x + specular*(1.0-diff->x);
    result.y = diff->y + specular*(1.0-diff->y);
    result.z = diff->z + specular*(1.0-diff->z);
    return result;
}

Float specularLight(Vector *V, Vector *R, Vector *intersection, Float Ip, 
                    Float kn, Float ks)
{    
    Float power= kn;
    Float Fatt = 1;
    Float I = dotProduct(V, R);
    if (I<0) {
        return 0;
    }
    else{
        I = pow(I,power)*Ip*Fatt*ks;
        return fmin(1.0,  I); 
    } 
}

//+++++++++++++++++++++++++INTERSECTION FUNCTIONS++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++INTERSECTION FUNCTIONS++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++INTERSECTION FUNCTIONS++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++INTERSECTION FUNCTIONS++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++INTERSECTION FUNCTIONS++++++++++++++++++++++++++++++


Float intersectsBox(Ray r, Bbox b)
{
    Float infointersect = 0;
    Float tmin = (b.pMin.x - r.origin.x) / r.direction.x; 
    Float tmax = (b.pMax.x - r.origin.x) / r.direction.x; 
 
    if (tmin > tmax) swap(&tmin, &tmax); 
 
    Float tymin = (b.pMin.y - r.origin.y) / r.direction.y; 
    Float tymax = (b.pMax.y - r.origin.y) / r.direction.y; 

    if (tymin > tymax) 
        swap(&tymin, &tymax); 
 
    if ((tmin > tymax) || (tymin > tmax)) 
        return -1; 
 
    if (tymin > tmin) 
        tmin = tymin; 
 
    if (tymax < tmax) 
        tmax = tymax; 
 
    Float tzmin = (b.pMin.z - r.origin.z) / r.direction.z; 
    Float tzmax = (b.pMax.z - r.origin.z) / r.direction.z; 
 
    if (tzmin > tzmax) swap(&tzmin, &tzmax); 
 
    if ((tmin > tzmax) || (tzmin > tmax)) 
        return -1; 
 
    if (tzmin > tmin) 
        tmin = tzmin; 
 
    if (tzmax < tmax) 
        tmax = tzmax; 
 
    if (tmin < 0) tmin = 9999999;
    if (tmax < 0) tmax = 9999999;
    infointersect = fmin(tmin, tmax);
   // if (infointersect < 0) infointersect = abs(infointersect);
    if (infointersect < EPSILOM){
        infointersect = -1;
        return infointersect;
    }         
    return infointersect;
}
      
Float intersectsSphere(Ray rayo, GenericShape shape){
    Float radius = shape.rad;
    Float A = dotProduct(&rayo.direction, &rayo.direction);
    Vector distancia = substractVector(&rayo.origin, &shape.position);
    Float B = 2 * dotProduct(&rayo.direction, &distancia);    
    Float C = dotProduct(&distancia, &distancia) - (radius * radius);
    Float discriminante = B*B - 4*A*C;
    Float infointersect = -1;
    //ElementNode *light;
     if(discriminante > 0){
        Float t1= (-B-sqrt(B*B-4*C))/2;
        Float t2= (-B+sqrt(B*B-4*C))/2;
        infointersect = fmin(t1, t2);
        if (infointersect < EPSILOM){
            infointersect = -1;
            return infointersect;
        }            
        return infointersect;
    }else{
        return infointersect;
    }
}                                     

Float intersectsCylinder(Ray rayo, GenericShape shape){
     
    Float radius = shape.rad;
    Float a, b, c, alpha, beta, gamma, t1, t2, d1, d2, d;
    Float Xq, Yq, Zq, Xr, Yr, Zr;
    Float infointersect = -1;
    Float discriminante;
    Vector intersection, normdir;      

    d1 = shape.cnst.A;
    d2 = shape.cnst.B;  

    normdir = normalizedVector(&shape.vec0);
    Xq = normdir.x;
    Yq = normdir.y;
    Zq = normdir.z;
   a =(pow(Xq,2)*rayo.direction.x)+(Xq*rayo.direction.y*Yq)+(Xq*rayo.direction.z*Zq)-rayo.direction.x;
    b =(pow(Yq,2)*rayo.direction.y)+(rayo.direction.x*Xq*Yq)+(Yq*rayo.direction.z*Zq)-rayo.direction.y;
    c =(pow(Zq,2)*rayo.direction.z)+(rayo.direction.x*Xq*Zq)+(rayo.direction.y*Yq*Zq)-rayo.direction.z;
 
    Xr= rayo.origin.x-shape.position.x;
    Yr= rayo.origin.y-shape.position.y;
    Zr= rayo.origin.z-shape.position.z;
    
    alpha = pow(a,2) + pow(b,2) + pow(c, 2);

    beta = 2*a*Xr*(pow(Xq,2)-1) + 2*a*Xq*(Yq*Yr+Zq*Zr)+2*b*Yr*(pow(Yq,2)-1) + 
2*b*Yq*(Xq*Xr+Zq*Zr)+2*c*Zr*(pow(Zq,2)-1) + 2*c*Zq*(Xq*Xr+Yq*Yr);

    gamma= pow(((pow(Xq,2)-1)*Xr),2) + pow(Xq*(Yq*Yr+Zq*Zr),2)+
pow(((pow(Yq,2)-1)*Yr),2) +pow(Yq*(Xq*Xr+Zq*Zr),2)+pow(((pow(Zq,2)-1)*Zr),2)
+pow(Zq*(Xq*Xr+Yq*Yr),2)+(2*Xr*Xq*(pow(Xq,2)-1))*(Yq*Yr+Zq*Zr)
+(2*Yr*Yq*(pow(Yq,2)-1))*(Xq*Xr+Zq*Zr)+(2*Zr*Zq*(pow(Zq,2)-1))*(Xq*Xr+Yq*Yr)
-radius*radius;
        
    discriminante = beta*beta - 4*alpha*gamma;

    if(discriminante > 0){
        t1= (-beta-sqrt(beta*beta-4*alpha*gamma))/(2*alpha);
        t2= (-beta+sqrt(beta*beta-4*alpha*gamma))/(2*alpha);
        
        intersection =intersectionPoint(rayo, t1);
    
        d= (intersection.x -shape.position.x)*Xq+(intersection.y -shape.position.y)*Yq+
        (intersection.z -shape.position.z)*Zq;
        
        if(d < d2 && d > d1){    
            if(t1<EPSILOM){
                infointersect = -1;
                return infointersect;
            }            
            infointersect = t1;
            return infointersect;
        }else{
            intersection =intersectionPoint(rayo, t2);
            d= (intersection.x -shape.position.x)*Xq+(intersection.y -shape.position.y)*Yq+
            (intersection.z -shape.position.z)*Zq;
            if(d < d2 && d > d1){
                if(t2 < EPSILOM){
                    infointersect = -1;
                    return infointersect;
                }                 
                infointersect = t2;                
                return infointersect;                  
            }

        }

           if (infointersect < EPSILOM){
            infointersect = -1;
            return infointersect;
           }    
    }else{
        infointersect = -1;
        return infointersect;
    }

    infointersect = -1;
    return infointersect;

}

Float intersectsCone(Ray rayo, GenericShape shape){
    
    Vector center = shape.position;      

    Float alpha, beta, gamma, t1, t2, d1, d2, a, b, c, d, f, e, g;
    Float Xa, Ya, Za, Xd, Yd, Zd, Xc, Yc, Zc, Xq, Yq, Zq;
    Float infointersect = -1;
    Float discriminante;
    
    Vector intersection, normdir;    
    Xa = rayo.origin.x;
    Ya = rayo.origin.y;
    Za = rayo.origin.z;    
    Xd = rayo.direction.x;
    Yd = rayo.direction.y;
    Zd = rayo.direction.z;
    Xc= center.x;
    Yc= center.y;
    Zc= center.z;
    normdir = normalizedVector(&shape.vec0);
    Xq = normdir.x;
    Yq = normdir.y;
    Zq = normdir.z;
   
    d1 = shape.cnst.A;
    d2 = shape.cnst.B;;

    //Float k1 = coneSpecificData->k1;
    //Float k2 = coneSpecificData->k2;

    Float h = shape.cnst.D/shape.cnst.C;
    a = (pow(Xq,2)*Xd)+(Xq*Yd*Yq)+(Xq*Zd*Zq)-Xd;
    b = (pow(Yq,2)*Yd)+(Xd*Xq*Yq)+(Yq*Zd*Zq)-Yd;
    c = (pow(Zq,2)*Zd)+(Xd*Xq*Zq)+(Yd*Yq*Zq)-Zd;
    d = (Xa-Xc);
    e = (Ya-Yc);
    f = (Za-Zc);
    g = (Xd*Xq)+(Yd*Yq)+(Zd*Zq);

    alpha = pow(a, 2)+pow(b, 2)+pow(c, 2)-(h*pow(g, 2));

    beta = (2*a*d*(pow(Xq, 2)-1))+(2*a*Xq*((Yq*e)+(Zq*f)))
        +(2*b*e*(pow(Yq, 2)-1))+(2*b*Yq*((Xq*d)+(Zq*f)))
        +(2*c*f*(pow(Zq, 2)-1))+(2*c*Zq*((Xq*d)+(Yq*e)))
        -(h*2*g*d*Xq)-(h*2*g*e*Yq)-(h*2*g*f*Zq);

    gamma = pow((pow(Xq,2)-1)*d, 2)+pow(Xq*((Yq*e)+(Zq*f)), 2)
        +pow((pow(Yq,2)-1)*e, 2)+pow(Yq*((Xq*d)+(Zq*f)), 2)
        +pow((pow(Zq,2)-1)*f, 2)+pow(Zq*((Xq*d)+(Yq*e)), 2)
        +(2*d*Xq*(pow(Xq, 2)-1)*((Yq*e)+(Zq*f)))
        +(2*e*Yq*(pow(Yq, 2)-1)*((Xq*d)+(Zq*f)))
        +(2*f*Zq*(pow(Zq, 2)-1)*((Xq*d)+(Yq*e)))
        -(h*pow(Xq*d, 2))-(h*pow(Yq*e, 2))-(h*pow(Zq*f, 2))
        -(h*2*d*e*Xq*Yq)-(h*2*d*f*Xq*Zq)-(h*2*e*f*Yq*Zq);


    discriminante = beta*beta - 4*alpha*gamma;

    if(discriminante > 0){
        t1= (-beta-sqrt(beta*beta-4*alpha*gamma))/(2*alpha);
        t2= (-beta+sqrt(beta*beta-4*alpha*gamma))/(2*alpha);
        
        intersection =intersectionPoint(rayo, t1);
    
        d= (intersection.x -Xc)*Xq+(intersection.y -Yc)*Yq+
        (intersection.z -Zc)*Zq;
        
        if(d < d2 && d > d1){    
			if(t1 < EPSILOM){
                infointersect = -1;
                return infointersect;
            }             
			infointersect = t1;   
               return infointersect;
        }else{
			if(t2 < EPSILOM){
                infointersect = -1;
                return infointersect;
            } 
            intersection = intersectionPoint(rayo, t2);
            d= (intersection.x -Xc)*Xq+(intersection.y -Yc)*Yq+
            (intersection.z -Zc)*Zq;
            if(d < d2 && d > d1){
                infointersect = t2;
                return infointersect;                  
            }

        }
           if (infointersect < EPSILOM){
            infointersect = -1;
            return infointersect;
           }    
    }else{
        infointersect = -1;
        return infointersect;
    }
    infointersect = -1;
    return infointersect;
}

Float intersectsPlane(Ray rayo, Plane plane){

    Float returnval;
    Vector normalPlane;
    normalPlane.x = plane.A;
    normalPlane.y = plane.B;
    normalPlane.z = plane.C;    
    Float den = dotProduct(&normalPlane, &rayo.direction);
    if (den == 0){
        returnval =-1;
        return returnval;
    }else{
        returnval =-(dotProduct(&normalPlane, &rayo.origin)+plane.D)/den;
        return returnval;
    }

}

Float intersectsDisc(Ray rayo, GenericShape shape){
   
    Float infointersect = -1;
    
    infointersect = intersectsPlane(rayo, shape.cnst);

    if(infointersect == -1 || infointersect < EPSILOM){ 
        infointersect = -1;
        return infointersect;
    }
    Vector planeintersect = intersectionPoint(rayo, infointersect);
    Float distanceX = planeintersect.x - shape.position.x;
    Float distanceY = planeintersect.y - shape.position.y;
    Float distanceZ = planeintersect.z - shape.position.z;

    Float intersect = pow(distanceX,2)+pow(distanceY,2)+pow(distanceZ,2)-pow(shape.rad,2);
    
    if(intersect > EPSILOM)
    {
        //even --> outside the polygon
        infointersect = -1;
        return infointersect;
    }
    else {
        return infointersect;        
    }
}

Vector crossProductPlane(Vector *vec1, Vector *vec2, Vector *vec3)
{
    Vector A_B_C;
    //destination - origin
    //vec1->0, vec2->1, vec3->2
    Vector vector1 = substractVector(vec1, vec2);
    Vector vector2 = substractVector(vec3, vec2);
    //Ax + By + Cz + D = 0
    A_B_C.x = (vector1.y * vector2.z) - (vector2.y * vector1.z);
    A_B_C.y = (vector2.x * vector1.z) - (vector1.x * vector2.z);
    A_B_C.z = (vector1.x * vector2.y) - (vector2.x * vector1.y);
    
    return A_B_C;
     
}


Vector normalVectorPlane(GenericShape triangle){
                
    Vector vec1 = triangle.vec0;
    
    Vector vec2 = triangle.vec1;
    
    Vector vec3 = triangle.vec2;
                
    Vector cross_product = crossProductPlane(&vec1, &vec2, &vec3);
    return cross_product;
}

Float intersectsTriangle(Ray rayo, GenericShape shape){
   
    Float infointersect = -1;
    
    infointersect = intersectsPlane(rayo, shape.cnst);
    if(infointersect == -1 || infointersect < EPSILOM){ 
        infointersect = -1;
        return infointersect;
    }

    Vector intersection = intersectionPoint(rayo, infointersect);

    Vector N = normalVectorPlane(shape);
    N = negateVector(&N);
    Vector edge0 = substractVector(&shape.vec1, &shape.vec0);
    Vector edge1 = substractVector(&shape.vec2, &shape.vec1);
    Vector edge2 = substractVector(&shape.vec0, &shape.vec2);

    Vector C0 = substractVector(&intersection, &shape.vec0);
    Vector C1 = substractVector(&intersection, &shape.vec1);
    Vector C2 = substractVector(&intersection, &shape.vec2);

    C0 = crossProduct(&edge0, &C0);
    C1 = crossProduct(&edge1, &C1); 
    C2 = crossProduct(&edge2, &C2);

    if(dotProduct(&N, &C0) > 0 && dotProduct(&N, &C1) > 0 && 
       dotProduct(&N, &C2) > 0){
    
        return infointersect;
    }
    infointersect = -1;
    return infointersect;
       
}

Float getIntersection(Ray rayscene, GenericShape shape){
    if(shape.shapetype == 0)
        return intersectsSphere(rayscene, shape);  
    else if(shape.shapetype == 1)
        return intersectsCylinder(rayscene, shape);
    else if(shape.shapetype == 2)
        return intersectsCone(rayscene, shape);
    else if(shape.shapetype == 3)
        return intersectsDisc(rayscene, shape);
    else if(shape.shapetype == 4)
        return intersectsTriangle(rayscene, shape);
    return -1;
}


Vector normalVectorSphere(Vector intersection, Vector center, Float radius){
    Vector retorno;
    retorno.x = (intersection.x - center.x)/radius;
    retorno.y = (intersection.y - center.y)/radius;
    retorno.z = (intersection.z - center.z)/radius;    
    return normalizedVector(&retorno);
}

Vector normalVectorCylinder(Vector intersection, Vector center, Vector direction,  Float radius){
    Vector retorno;
    Float d;
    d = ((intersection.x-center.x)*direction.x)+((intersection.y-center.y)*direction.y)+((intersection.z-center.z)*direction.z);
    retorno.x = (intersection.x - (center.x+d*direction.x))/radius;
    retorno.y = (intersection.y - (center.y+d*direction.y))/radius;
    retorno.z = (intersection.z - (center.z+d*direction.z))/radius;    
    return retorno;
}

Vector normalVectorCone(Vector intersection, Vector center, Vector direction){
    Vector retorno;
    Float cateto;
    Vector dir = normalizedVector(&direction);
    Vector hipotenusa =  substractVector(&intersection, &center);
    Float d = vectorNorm(&hipotenusa);
    hipotenusa = normalizedVector(&hipotenusa);
    cateto = d/dotProduct(&dir,&hipotenusa);
    retorno.x = intersection.x -(center.x+cateto*dir.x);
    retorno.y = intersection.y -(center.y+cateto*dir.y); 
    retorno.z = intersection.z -(center.z+cateto*dir.z);
    retorno = normalizedVector(&retorno);
    return retorno;
}

Vector normalVectorDisc(Plane data){
    Vector N;
    N.x = data.A;
    N.y = data.B;
    N.z = data.C;
    return N;
}

Vector normalVectorTriangle(Plane data){
    Vector N;
    N.x = data.A;
    N.y = data.B;
    N.z = data.C;
    N = negateVector(&N);
    return N;
}

//++++++++++++++++++PRINT FUNCTION++++++++++++++++++++++++++
void printLinearBVHNode(LinearBVHNode node)
{
   
    printf("Bounds pMax = %lf, %lf, %lf\n", node.bounds.pMax.x, 
            node.bounds.pMax.y, node.bounds.pMax.z);
    printf("Bounds pMin = %lf, %lf, %lf\n", node.bounds.pMin.x, 
            node.bounds.pMin.y, node.bounds.pMin.z);    
    printf("primitivesOffset = %d\n", node.primitivesOffset);
    printf("secondChildOffset = %d\n", node.secondChildOffset);
    printf("nPrimitives = %d\n", node.nPrimitives);
    printf("axis = %d\n", node.axis);
    printf("pad = %d\n", node.pad[0]);
}


int intersectionBVHShadow(Ray finalray, 
                          global GenericShape *primitives, 
                          global LinearBVHNode *nodes,
                          Float lightdist)
{
    Interinfo finalint = {9999999,0};
    Float boxintersect = 0;

    int toVisitOffset = 0; 
    int currentNodeIndex = 0;
    int nodesToVisit[128];
    
     while(true) {
        LinearBVHNode node = nodes[currentNodeIndex];
      //  printLinearBVHNode(node);
        // Check ray against BVH node
        boxintersect = intersectsBox(finalray, node.bounds);
        if (boxintersect > EPSILOM ) {
            if (node.nPrimitives > 0) {
                // Intersect ray with primitives in leaf BVH node
                Float tintersect = getIntersection(finalray, 
                                   primitives[node.primitivesOffset]);
                if (tintersect > EPSILOM && tintersect < lightdist){
                    return 1;
                }   
                if (toVisitOffset == 0) break; 
                currentNodeIndex = nodesToVisit[--toVisitOffset]; 
            } else {
                // Put far BVH node on _nodesToVisit_ stack, advance to near
                // node
                Float t1 = intersectsBox(finalray,      
                           nodes[currentNodeIndex+1].bounds);
                Float t2 = intersectsBox(finalray,      
                           nodes[node.secondChildOffset].bounds);
                if(t1 == -1) t1 = 9999999;
                if(t2 == -1) t2 = 9999999;

                if (t2 < t1) {
                    nodesToVisit[toVisitOffset++] = currentNodeIndex + 1;
                    currentNodeIndex = node.secondChildOffset;
                } else {
                    nodesToVisit[toVisitOffset++] = node.secondChildOffset;
                    currentNodeIndex = currentNodeIndex + 1;
                }
            }
        } else {
            if (toVisitOffset == 0) break;
            currentNodeIndex = nodesToVisit[--toVisitOffset];
        }
    }

    return 0;
}



Interinfo intersectionBVH(Ray finalray, 
                          global GenericShape *primitives, 
                          global LinearBVHNode *nodes)
{
    Interinfo finalint = {9999999,0};
    Float boxintersect = 0;

    int toVisitOffset = 0; 
    int currentNodeIndex = 0;
    int nodesToVisit[128];
    
     while(true) {
        LinearBVHNode node = nodes[currentNodeIndex];
      //  printLinearBVHNode(node);
        // Check ray against BVH node
        boxintersect = intersectsBox(finalray, node.bounds);
        if (boxintersect > EPSILOM && boxintersect < finalint.t ) {
            if (node.nPrimitives > 0) {
                // Intersect ray with primitives in leaf BVH node
                Float tintersect = getIntersection(finalray, 
                                   primitives[node.primitivesOffset]);
                if (tintersect > EPSILOM && tintersect < finalint.t){
                    finalint.t = tintersect;        
                    finalint.position = node.primitivesOffset;
                }   
                if (toVisitOffset == 0) break; 
                currentNodeIndex = nodesToVisit[--toVisitOffset]; 
            } else {
                // Put far BVH node on _nodesToVisit_ stack, advance to near
                // node
                Float t1 = intersectsBox(finalray,      
                           nodes[currentNodeIndex+1].bounds);
                Float t2 = intersectsBox(finalray,      
                           nodes[node.secondChildOffset].bounds);
                if(t1 == -1) t1 = 9999999;
                if(t2 == -1) t2 = 9999999;

                if (t2 < t1) {
                    nodesToVisit[toVisitOffset++] = currentNodeIndex + 1;
                    currentNodeIndex = node.secondChildOffset;
                } else {
                    nodesToVisit[toVisitOffset++] = node.secondChildOffset;
                    currentNodeIndex = currentNodeIndex + 1;
                }
            }
        } else {
            if (toVisitOffset == 0) break;
            currentNodeIndex = nodesToVisit[--toVisitOffset];
        }
    }

    return finalint;
}

int shadowIntersectBrute(Ray finalray, 
                         global GenericShape *primitives, 
                         Float lightdist, int sizeScene)
{
    Float tintersect = 0;
    for(int i=0; i < sizeScene; i++){
        GenericShape primitive = primitives[i];
        tintersect = getIntersection(finalray, primitive);
        if(tintersect > EPSILOM && tintersect < lightdist){        
            return 1;
        } 
    }
    return 0;
}

Interinfo intersectionBrute(Ray finalray, 
                            global GenericShape *primitives, int sizeScene)
{
    Interinfo finalintersection = {9999999,0};
    Float tintersect = 0;
    for(int i=0; i < sizeScene; i++){
        GenericShape primitive = primitives[i];
        tintersect = getIntersection(finalray, primitive);
        if(tintersect > EPSILOM && tintersect < finalintersection.t){
                finalintersection.t = tintersect;
                finalintersection.position = i;
        }
    }
    return finalintersection;
}


Vector objectNormal(Vector intersection, GenericShape object)
{
    Vector normal;
    if (object.shapetype == 0)
        return normalVectorSphere(intersection, object.position, object.rad);
    else if (object.shapetype == 1)
        return normalVectorCylinder(intersection, object.position, object.vec0, 
                                    object.rad);
    else if (object.shapetype == 2)
        return normalVectorCone(intersection, object.position, object.vec0);
    else if (object.shapetype == 3)
        return normalVectorDisc(object.cnst);
    else if (object.shapetype == 4)
        return normalVectorTriangle(object.cnst);
}



Vector whichColorIsIt(Ray ray, 
                      __global GenericShape *primitives, 
                      __global LinearBVHNode *nodes,
                      __global SceneInfo *info,
                      __global SceneLights *lights, int idx,
                      __global ReturnGPU *ret)
{
    Vector background = {0.5, 0.5, 0.5};
    Vector refraction = {0.1, 0.1, 0.1};
    int toVisitOffset = 0; 
    int currentNodeIndex = 0;
    nodesTree dfsNodes[128];
    nodesTree raysToVisit[128];

    int levels = info->levels;
    int transparencies = info->transparencies;
    int parentpos = 0;
    Ray iray = ray;
    Float intensitydif;
    Float intensityspe;
    int colortype = 1;
    Vector color = {0,0,0}; 
   
    while(true){
   
        Interinfo inter;
        if(info->acceleration == ON)
            inter = intersectionBVH(iray, primitives, nodes);
        else
            inter = intersectionBrute(iray, primitives, info->sizeScene);

        if(inter.t == 9999999){
            dfsNodes[currentNodeIndex].inter = inter;
            dfsNodes[currentNodeIndex].color = background;
            dfsNodes[currentNodeIndex].parentpos = parentpos;
            dfsNodes[currentNodeIndex].colortype = colortype;
            currentNodeIndex++;
        } else{
             //Aca tenemos interseccion
            // Guardamos este rayo con su respectiva interseccion    
            Float o1= primitives[inter.position].o1;
            Float o2= primitives[inter.position].o2;
            Float o3= primitives[inter.position].o3;
            
            intensitydif = lights[0].val;
            intensityspe = 0;                 
            Vector intersection = intersectionPoint(iray, inter.t);
            Vector N = objectNormal(intersection, primitives[inter.position]);
            Vector V = inverseVector(&iray.origin, &intersection);
            for(int i=1; i <= info->sizeLights; i++){
                Vector L = lightVectorL(intersection, lights[i].par);
                Vector R = reflexVector(&L, &N);
                Ray raythread = {intersection, R};
                if(levels > 0 && o2 != 0){
                    toVisitOffset++;
                    raysToVisit[toVisitOffset].ray = raythread;
                    raysToVisit[toVisitOffset].parentpos = currentNodeIndex;
                    raysToVisit[toVisitOffset].colortype = 2;
                    raysToVisit[toVisitOffset].levels = levels-1;
                    raysToVisit[toVisitOffset].transparencies = transparencies;
                    ret[idx].rays += 1;       
                }   
                if(transparencies > 0 && o3 != 0){
                    toVisitOffset++;
                    raythread.direction = addVector(&iray.direction, &refraction);
                    raythread.direction = normalizedVector(&raythread.direction);
                    raysToVisit[toVisitOffset].ray = raythread;
                    raysToVisit[toVisitOffset].parentpos = currentNodeIndex;
                    raysToVisit[toVisitOffset].colortype = 3;
                    raysToVisit[toVisitOffset].levels = levels;
                    raysToVisit[toVisitOffset].transparencies = transparencies-1;
                    ret[idx].rays += 1;             
                }
                Ray shadow;
                shadow.origin = intersection;
                Vector dir = lights[i].par;
                dir = substractVector(&dir, &shadow.origin); 
                shadow.direction = normalizedVector(&dir);
                Float lightdst = vectorNorm(&dir);
                ret[idx].rays += 1;

                int shadowcheck;                
                if(info->acceleration == ON)
                    shadowcheck = intersectionBVHShadow(shadow, primitives, 
                                                        nodes, lightdst);
                else
                    shadowcheck = shadowIntersectBrute(shadow, primitives, 
                                                       lightdst, 
                                                       info->sizeScene);
                if(shadowcheck){
          
                } else{
                  
                    Float difuse = difuseLight(&L,  &N, &intersection, 
                                               lights[i].val, primitives[inter.position].kd);  
                    Float specular= specularLight(&V,  &R, &intersection, lights[i].val, 
                                                  primitives[inter.position].kn, 
                                                  primitives[inter.position].ks);
                    intensitydif += difuse;
                    intensityspe += specular;
                }        
            } 
            dfsNodes[currentNodeIndex].ray = iray;
            dfsNodes[currentNodeIndex].inter = inter;
            dfsNodes[currentNodeIndex].color = multiplyConstantVector(o1, 
                                               primitives[inter.position].color); 
            dfsNodes[currentNodeIndex].parentpos = parentpos;
            dfsNodes[currentNodeIndex].intensitydif = intensitydif;
            dfsNodes[currentNodeIndex].intensityspe = intensityspe;   
            dfsNodes[currentNodeIndex].colortype = colortype;
            currentNodeIndex++;                        
        }
        if(toVisitOffset == 0){
            break;
        } else{ 
            iray = raysToVisit[toVisitOffset].ray; 
            levels = raysToVisit[toVisitOffset].levels;
            transparencies = raysToVisit[toVisitOffset].transparencies;
            parentpos = raysToVisit[toVisitOffset].parentpos;
            colortype = raysToVisit[toVisitOffset].colortype;
            toVisitOffset--;
        }
    }

/*  if (idx == 819840) {
        printf("Current node index %d\n", currentNodeIndex);
        for(int i = currentNodeIndex - 1; i >= 0; i--){
            printf("i = %d\n", i);            
            printf("Color = %lf, %lf, %lf\n", dfsNodes[i].color.x, 
                   dfsNodes[i].color.y, dfsNodes[i].color.z);
            printf("ParentPos = %d\n", dfsNodes[i].parentpos);
            printf("ColorType = %d\n", dfsNodes[i].colortype);
             printf("transparencies = %d\n", info->transparencies);  
        }
    } */
    for(int i = currentNodeIndex - 1; i >= 0; i--){
        if(i == 0 && dfsNodes[i].inter.t == 9999999){
            return dfsNodes[i].color;
        }
        else if(i == 0){
            color = dfsNodes[i].color;
            color = difuseColor(&color, fmin(1.0, dfsNodes[i].intensitydif));
            color = specularColor(&color, fmin(1.0, dfsNodes[i].intensityspe));
        } else if(dfsNodes[i].colortype == 2){
            int parentprim =  dfsNodes[dfsNodes[i].parentpos].inter.position;
            Float o2 = primitives[parentprim].o2; 
            Vector thiscol = dfsNodes[i].color;
            if(dfsNodes[i].inter.t == 9999999){
                thiscol = multiplyConstantVector(o2, thiscol);
                Vector parentcolor = dfsNodes[dfsNodes[i].parentpos].color;
                dfsNodes[dfsNodes[i].parentpos].color = addVector(&parentcolor, 
                                                                  &thiscol);
            } else{
                thiscol = difuseColor(&thiscol, fmin(1.0, dfsNodes[i].intensitydif));
                thiscol = specularColor(&thiscol, fmin(1.0, dfsNodes[i].intensityspe));              
                thiscol = multiplyConstantVector(o2, thiscol);
                Vector parentcolor = dfsNodes[dfsNodes[i].parentpos].color;
                dfsNodes[dfsNodes[i].parentpos].color = addVector(&parentcolor, 
                                                                  &thiscol);
            }
        } else if(dfsNodes[i].colortype == 3){
            int parentprim =  dfsNodes[dfsNodes[i].parentpos].inter.position;
            Float o3 = primitives[parentprim].o3; 
            Vector thiscol = dfsNodes[i].color;
            if(dfsNodes[i].inter.t == 9999999){
                thiscol = multiplyConstantVector(o3, thiscol);
                Vector parentcolor = dfsNodes[dfsNodes[i].parentpos].color;
                dfsNodes[dfsNodes[i].parentpos].color = addVector(&parentcolor, 
                                                                  &thiscol);
            } else{
                thiscol = difuseColor(&thiscol, fmin(1.0, dfsNodes[i].intensitydif));
                thiscol = specularColor(&thiscol, fmin(1.0, dfsNodes[i].intensityspe));              
                thiscol = multiplyConstantVector(o3, thiscol);
                Vector parentcolor = dfsNodes[dfsNodes[i].parentpos].color;
                dfsNodes[dfsNodes[i].parentpos].color = addVector(&parentcolor, 
                                                                  &thiscol);
            }
        }            
    }

    return color;
}

Vector antialiasColor(Vector eye, 
                      int x, int y, int dimx, int dimy,
                      __global GenericShape *primitives, 
                      __global LinearBVHNode *nodes,
                      __global SceneInfo *info,
                      __global SceneLights *lights, int idx,
                      __global ReturnGPU *ret)
{
    Ray raythread;
    raythread.origin = eye; 
    raythread.direction = obtainNormalizedDirection(eye, (Float)x, 
                                                   (Float)y, dimx, 
                                                   dimy);
    Vector finalcolor;
    Vector intermediate;
    Float average = (Float)1/5;
    
    Float offset= (Float)1/2;

    raythread.direction = obtainNormalizedDirection(eye, (Float)x, 
                                                   (Float)y, dimx, 
                                                   dimy);
    ret[idx].rays += 1;
    finalcolor = whichColorIsIt(raythread, primitives, nodes, info, lights, idx, ret);

    raythread.direction = obtainNormalizedDirection(eye, (Float)x-offset, 
                                                   (Float)y, dimx, 
                                                   dimy);
    ret[idx].rays += 1;
    intermediate = whichColorIsIt(raythread, primitives, nodes, info, lights, idx, ret);
    finalcolor = addVector(&finalcolor, &intermediate);

    raythread.direction = obtainNormalizedDirection(eye, (Float)x+offset, 
                                                   (Float)y, dimx, 
                                                   dimy);
    ret[idx].rays += 1;
    intermediate = whichColorIsIt(raythread, primitives, nodes, info, lights, idx, ret);
    finalcolor = addVector(&finalcolor, &intermediate);


    raythread.direction = obtainNormalizedDirection(eye, (Float)x, 
                                                   (Float)y-offset, dimx, 
                                                   dimy);
    ret[idx].rays += 1;
    intermediate = whichColorIsIt(raythread, primitives, nodes, info, lights, idx, ret);
    finalcolor = addVector(&finalcolor, &intermediate);

    raythread.direction = obtainNormalizedDirection(eye, (Float)x, 
                                                   (Float)y+offset, dimx, 
                                                   dimy);   
    ret[idx].rays += 1;
    intermediate = whichColorIsIt(raythread, primitives, nodes, info, lights, idx, ret);
    finalcolor = addVector(&finalcolor, &intermediate);
    
    finalcolor.x = finalcolor.x * average;
    finalcolor.y = finalcolor.y * average;
    finalcolor.z = finalcolor.z * average;

    return finalcolor;   
}


__kernel                                            
void colDetection(__global GenericShape *primitives, 
                  __global SceneInfo *info,
                  __global SceneLights *lights,
                  __global LinearBVHNode *nodes,  
                  __global ReturnGPU *ret)                        
{                                                   
                                                    
   // Get the work-item’s unique ID                 
    int idx = get_global_id(0);                      
    int ycord;
    int xcord;
    Vector eye = info->eye;
    Float div;              
    Vector background = {0.5, 0.5, 0.5};
  //Esta parte funciona perfecot  
    div = (Float)idx/((Float)(info->dimx));  
    ycord = (int)((Float)idx/((Float)info->dimx)); 
    xcord = round(((div - (Float)ycord)*(Float)(info->dimx)));
    Vector color;
    ret[idx].rays = 0;

    if(info->antialiasing == ON){
        color = antialiasColor(eye, xcord, ycord, info->dimx, info->dimy,
                               primitives, nodes, info, lights, idx, ret);
    }
    else if(info->antialiasing == OFF){  
        Ray finalray;
        finalray.origin = eye; 
        finalray.direction = obtainNormalizedDirection(eye, (Float)xcord, 
                                                       (Float)ycord, info->dimx, 
                                                       info->dimy);   
        ret[idx].rays += 1;
        color = whichColorIsIt(finalray, primitives, nodes, info, lights, idx, ret);
    }

    ret[idx].color = color;
    ret[idx].x = xcord;
    ret[idx].y = ycord;
  //  barrier( CLK_LOCAL_MEM_FENCE );                      
}                                                  

__kernel                                            
void apuTracer(__global GenericShape *primitives,
               __global WorkDispatch *work, 
               __global SceneInfo *info,
               __global SceneLights *lights,
               __global LinearBVHNode *nodes,  
               __global ReturnGPU *ret)                        
{                                                   
                                                    
   // Get the work-item’s unique ID                 
    int idx = get_global_id(0); 
    int numItems = get_local_size( 0 );	
    //printf("El global local size per group es: %d\n", numItems);
    int tnum = get_local_id( 0 );
    //printf("El local id es: %d\n", tnum);
    int wgNum = get_group_id( 0 );
    //printf("El numero de work group es: %d\n", wgNum);


                       
    int ycord;
    int xcord;
    Vector eye = info->eye;
    Float div;              
    Vector background = {0.5, 0.5, 0.5};
  //Esta parte funciona perfecot  
    div = (Float)tnum/((Float)(16));  
    ycord = (int)((Float)tnum/((Float)16)); 
    xcord = work[wgNum].xstart + round(((div - (Float)ycord)*(Float)(16)));
    ycord += work[wgNum].ystart;
    Vector color;
    ret[idx].rays = 0;
    


   // printf("GlobalID = %d, WorkGroup = %d, LocalID = %d, x = %d, y = %d, xstart = %d, ystart = %d\n", idx, tnum, wgNum, xcord, ycord, work[wgNum].xstart, work[wgNum].ystart);
    if(xcord > work[wgNum].xfinish || ycord > work[wgNum].yfinish){
        ret[idx].valid = 0;
        ret[idx].color = background;
    } else{
        if(info->antialiasing == ON){
            color = antialiasColor(eye, xcord, ycord, info->dimx, info->dimy,
                                   primitives, nodes, info, lights, idx, ret);
        }
        else if(info->antialiasing == OFF){  
            Ray finalray;
            finalray.origin = eye; 
            finalray.direction = obtainNormalizedDirection(eye, (Float)xcord, 
                                                           (Float)ycord, info->dimx, 
                                                           info->dimy);   
            ret[idx].rays += 1;
            color = whichColorIsIt(finalray, primitives, nodes, info, lights, idx, ret);
        }
        ret[idx].color = color;
        ret[idx].valid = 1;
        ret[idx].x = xcord;
        ret[idx].y = ycord;
    
    }
                                               
                      
}        



