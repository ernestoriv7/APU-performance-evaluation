#include"shapes.h"


Vector objectNormal(Vector intersection, GenericShape object)
{
    Vector normal;
    if (object.shapetype == 0)
        normal = normalVectorSphere(intersection, object.position, object.rad);
    else if (object.shapetype == 1)
        normal = normalVectorCylinder(intersection, object.position, object.vec0, 
                                    object.rad);
    else if (object.shapetype == 2)
        normal = normalVectorCone(intersection, object.position, object.vec0);
    else if (object.shapetype == 3)
        normal = normalVectorDisc(object.cnst);
    else if (object.shapetype == 4)
        normal = normalVectorTriangle(object.cnst);
    return normal;
}

Float getIntersection(Ray *rayscene, GenericShape *primitive){
    if(primitive->shapetype == SPHERE)
        return intersectsSphere(rayscene, primitive);  
    else if(primitive->shapetype == CYL)
        return intersectsCylinder(rayscene, primitive);
    else if(primitive->shapetype == CONE)
        return intersectsCone(rayscene, primitive);
    else if(primitive->shapetype == DISC)
        return intersectsDisc(rayscene, primitive);
    else if(primitive->shapetype == TRIANGLE)
        return intersectsTriangle(rayscene, primitive);
    return -1;
}


void swap(Float *a, Float *b)
{
   Float t; 
   t  = *b;
   *b = *a;
   *a = t;
}

Float intersectsBox(Ray *r, Bbox *b){
    
    Float infointersect = 0;
    Float tmin = (b->pMin.x - r->origin.x) / r->direction.x; 
    Float tmax = (b->pMax.x - r->origin.x) / r->direction.x; 
 
    if (tmin > tmax) swap(&tmin, &tmax); 
 
    Float tymin = (b->pMin.y - r->origin.y) / r->direction.y; 
    Float tymax = (b->pMax.y - r->origin.y) / r->direction.y; 
 
    if (tymin > tymax) 
        swap(&tymin, &tymax); 
 
    if ((tmin > tymax) || (tymin > tmax)) 
        return -1; 
 
    if (tymin > tmin) 
        tmin = tymin; 
 
    if (tymax < tmax) 
        tmax = tymax; 
 
    Float tzmin = (b->pMin.z - r->origin.z) / r->direction.z; 
    Float tzmax = (b->pMax.z - r->origin.z) / r->direction.z; 
 
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
    if (infointersect < epsilom){
        infointersect = -1;
        return infointersect;
    }            
        return infointersect;
}

Bbox sphereBox(GenericShape sphere)
{
    Float radius = sphere.rad;
    Vector center = sphere.position;
    Vector p1 = {center.x-radius, center.y-radius, center.z-radius};
    Vector p2 = {center.x+radius, center.y+radius, center.z+radius};
    Bbox box = createBox(&p1, &p2);
    return box;
}

Float intersectsSphere(Ray *rayo, GenericShape *sphere){
    Float radius = sphere->rad;
    Float A = dotProduct(&rayo->direction, &rayo->direction);
    Vector distancia = substractVector(&rayo->origin, &sphere->position);
    Float B = 2 * dotProduct(&rayo->direction, &distancia);    
    Float C = dotProduct(&distancia, &distancia) - (radius * radius);
    Float discriminante = B*B - 4*A*C;
    Float infointersect = -1;
    //ElementNode *light;
     if(discriminante > 0){
        Float t1= (-B-sqrt(B*B-4*C))/2;
        Float t2= (-B+sqrt(B*B-4*C))/2;
        infointersect = fmin(t1, t2);
        if (infointersect < epsilom){
            infointersect = -1;
            return infointersect;
        }            
        return infointersect;
    }else{
        return infointersect;
    }
}

Bbox cylinderBox(GenericShape cylinder)
{
    Float radius = cylinder.rad;
    Float d1 = cylinder.cnst.A;
    Float d2 = cylinder.cnst.B;
    Vector dir = cylinder.vec0;
    Vector position = cylinder.position;
    Ray raycyl = {position, dir};
    Vector lowcenter  = intersectionPoint(&raycyl, d1);
    Vector upcenter = intersectionPoint(&raycyl, d2);
    
    Vector b1p1 = {lowcenter.x-radius, lowcenter.y-radius, lowcenter.z-radius};
    Vector b1p2 = {upcenter.x+radius, upcenter.y+radius, upcenter.z+radius};
    Bbox box1 = createBox(&b1p1, &b1p2);
    Vector b2p1 = {lowcenter.x+radius, lowcenter.y+radius, lowcenter.z+radius};
    Vector b2p2 = {upcenter.x-radius, upcenter.y-radius, upcenter.z-radius};
    Bbox box2 = createBox(&b2p1, &b2p2);
    Bbox box = unionBoxBox(&box1, &box2);
    return box;
}

Float intersectsCylinder(Ray *rayo, GenericShape *cylinder){
     
    Float radius = cylinder->rad;
    Float a, b, c, alpha, beta, gamma, t1, t2, d1, d2, d;
    Float Xq, Yq, Zq, Xr, Yr, Zr;
    Float infointersect = -1;
    Float discriminante;
    Vector intersection, normdir;      

    d1 = cylinder->cnst.A;
    d2 = cylinder->cnst.B;  

    normdir = normalizedVector(&cylinder->vec0);
    Xq = normdir.x;
    Yq = normdir.y;
    Zq = normdir.z;
    a =(pow(Xq,2)*rayo->direction.x)+(Xq*rayo->direction.y*Yq)+(Xq*rayo->direction.z*Zq)-rayo->direction.x;
    b =(pow(Yq,2)*rayo->direction.y)+(rayo->direction.x*Xq*Yq)+(Yq*rayo->direction.z*Zq)-rayo->direction.y;
    c =(pow(Zq,2)*rayo->direction.z)+(rayo->direction.x*Xq*Zq)+(rayo->direction.y*Yq*Zq)-rayo->direction.z;

    Xr= rayo->origin.x-cylinder->position.x;
    Yr= rayo->origin.y-cylinder->position.y;
    Zr= rayo->origin.z-cylinder->position.z;
    
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
    
        d= (intersection.x -cylinder->position.x)*Xq+(intersection.y -cylinder->position.y)*Yq+
        (intersection.z -cylinder->position.z)*Zq;
        
        if(d < d2 && d > d1){    
            if(t1<epsilom){
                infointersect = -1;
                return infointersect;
            }            
            infointersect = t1;
            return infointersect;
        }else{
            intersection =intersectionPoint(rayo, t2);
            d= (intersection.x -cylinder->position.x)*Xq+(intersection.y -cylinder->position.y)*Yq+
            (intersection.z -cylinder->position.z)*Zq;
            if(d < d2 && d > d1){
                if(t2<epsilom){
                    infointersect = -1;
                    return infointersect;
                }                 
                infointersect = t2;                
                return infointersect;                  
            }

        }

           if (infointersect < epsilom){
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


Bbox coneBox(GenericShape cone)
{
    Float d1 = cone.cnst.A;
    Float d2 = cone.cnst.B;
    Vector dir = cone.vec0;
    Vector position = cone.position;
    Ray raycyl = {position, dir};
    Vector lowcenter  = intersectionPoint(&raycyl, d1);
    Vector upcenter = intersectionPoint(&raycyl, d2);
    Float h = cone.cnst.D/cone.cnst.C;
    Float radius = 2.1*fmax(h*abs(d1), h*d2);
    Vector b1p1 = {lowcenter.x-radius, lowcenter.y-radius, lowcenter.z-radius};
    Vector b1p2 = {upcenter.x+radius, upcenter.y+radius, upcenter.z+radius};
    Bbox box1 = createBox(&b1p1, &b1p2);
    Vector b2p1 = {lowcenter.x+radius, lowcenter.y+radius, lowcenter.z+radius};
    Vector b2p2 = {upcenter.x-radius, upcenter.y-radius, upcenter.z-radius};
    Bbox box2 = createBox(&b2p1, &b2p2);
    Bbox box = unionBoxBox(&box1, &box2);
    return box;
}


Float intersectsCone(Ray *rayo, GenericShape *cone){
    
    Vector center = cone->position;  

    Float alpha, beta, gamma, t1, t2, d1, d2, a, b, c, d, f, e, g;
    Float Xa, Ya, Za, Xd, Yd, Zd, Xc, Yc, Zc, Xq, Yq, Zq;
    Float infointersect = -1;
    Float discriminante;
    
    Vector intersection, normdir;    
    Xa = rayo->origin.x;
    Ya = rayo->origin.y;
    Za = rayo->origin.z;    
    Xd = rayo->direction.x;
    Yd = rayo->direction.y;
    Zd = rayo->direction.z;
    Xc=center.x;
    Yc=center.y;
    Zc=center.z;
    normdir = normalizedVector(&cone->vec0);
    Xq = normdir.x;
    Yq = normdir.y;
    Zq = normdir.z;
   
    d1 = cone->cnst.A;
    d2 = cone->cnst.B;

    //Float k1 = coneSpecificData->k1;
    //Float k2 = coneSpecificData->k2;

    Float h = cone->cnst.D/cone->cnst.C;
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
			if(t1<epsilom){
                infointersect = -1;
                return infointersect;
            }             
			infointersect = t1;   
               return infointersect;
        }else{
			if(t2<epsilom){
                infointersect = -1;
                return infointersect;
            } 
            intersection =intersectionPoint(rayo, t2);
            d= (intersection.x -Xc)*Xq+(intersection.y -Yc)*Yq+
            (intersection.z -Zc)*Zq;
            if(d < d2 && d > d1){
                infointersect = t2;
                return infointersect;                  
            }

        }
           if (infointersect < epsilom){
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




Bbox discBox(GenericShape disc)
{
    Float radius = disc.rad;
    Vector center = disc.position;
    Vector p1 = {center.x-radius, center.y-radius, center.z-radius};
    Vector p2 = {center.x+radius, center.y+radius, center.z+radius};
    Bbox box = createBox(&p1, &p2);
    return box;
}


Float intersectsDisc(Ray *rayo, GenericShape *disc){
   
    Float infointersect = -1;
    
    infointersect = intersectsPlane(rayo, &disc->cnst);

    if(infointersect == -1 || infointersect < epsilom){ 
        infointersect = -1;
        return infointersect;
    }
    Vector planeintersect = intersectionPoint(rayo, infointersect);
    Float distanceX = planeintersect.x - disc->position.x;
    Float distanceY = planeintersect.y - disc->position.y;
    Float distanceZ = planeintersect.z - disc->position.z;

    Float intersect = pow(distanceX,2)+pow(distanceY,2)+pow(distanceZ,2) - 
                      pow(disc->rad,2);
    
    if(intersect > epsilom)
    {
        //even --> outside the polygon
        infointersect = -1;
        return infointersect;
    }
    else {
        return infointersect;     
        
    }

}


Float intersectsPlane(Ray *rayo, Plane *plane){

    Float returnval;
    Vector normalPlane;
    normalPlane.x = plane->A;
    normalPlane.y = plane->B;
    normalPlane.z = plane->C;    
    Float den = dotProduct(&normalPlane, &rayo->direction);
    if (den == 0){
        returnval =-1;
        return returnval;
    }else{
        returnval =-(dotProduct(&normalPlane, &rayo->origin)+plane->D)/den;
        return returnval;
    }

}

Bbox triangleBox(GenericShape triangle)
{
    Bbox box = createBox(&triangle.vec0, &triangle.vec1);
    box = unionBoxPoint(&box, &triangle.vec2);
    return box;
}

Float intersectsTriangle(Ray *rayo, GenericShape *triangle){
   
    Float infointersect = -1;
    
    infointersect = intersectsPlane(rayo, &triangle->cnst);
    if(infointersect == -1 || infointersect < epsilom){ 
        infointersect = -1;
        return infointersect;
    }

    Vector intersection = intersectionPoint(rayo, infointersect);

    Vector N = normalVectorPlane(&triangle->vec0, &triangle->vec1, 
                                 &triangle->vec2);
    N = negateVector(&N);
    Vector edge0 = substractVector(&triangle->vec1, &triangle->vec0);
    Vector edge1 = substractVector(&triangle->vec2, &triangle->vec1);
    Vector edge2 = substractVector(&triangle->vec0, &triangle->vec2);

    Vector C0 = substractVector(&intersection, &triangle->vec0);
    Vector C1 = substractVector(&intersection, &triangle->vec1);
    Vector C2 = substractVector(&intersection, &triangle->vec2);

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

Vector normalVectorPlane(Vector *v0, Vector *v1, Vector *v2){                
    Vector cross_product = crossProductPlane(v0, v1, v2);
    return cross_product;
}

Plane getNormalizePlane(Vector *point, Vector *abc){
    Float D = -dotProduct(point, abc);
    long double L = vectorNorm(abc);
    Plane normalized;
    normalized.A =abc->x/L;
    normalized.B =abc->y/L;
    normalized.C =abc->z/L;
    normalized.D =D/L;
    return normalized;
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
