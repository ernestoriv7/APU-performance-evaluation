#include"bounding.h"


Bbox getBoundingBox(GenericShape shape){
    Bbox boundbox;    
    if(shape.shapetype == SPHERE)
        boundbox = sphereBox(shape);
    else if(shape.shapetype == CYL)
        boundbox = cylinderBox(shape);
    else if(shape.shapetype == CONE)
        boundbox = coneBox(shape);
    else if(shape.shapetype == DISC)
        boundbox = discBox(shape);
    else if(shape.shapetype == TRIANGLE)
        boundbox = triangleBox(shape);
    return boundbox;
}

Bbox createBox(Vector *p1, Vector *p2)
{
    Vector pmin = {fmin(p1->x, p2->x), fmin(p1->y, p2->y), 
                 fmin(p1->z, p2->z)};
    Vector pmax = {fmax(p1->x, p2->x), fmax(p1->y, p2->y), 
                  fmax(p1->z, p2->z)};

    Bbox newbox = {pmin, pmax};
    return newbox;
}

Vector corner(int corner)
{
    Vector cornervalue = {(float)(corner & 1), (corner & 2) ? 1 : 0,
                         (corner & 4) ? 1 : 0};
    return cornervalue;
}

Bbox unionBoxPoint(Bbox *box, Vector *point)
{
    Bbox unionbox;
    unionbox.pMin.x = fmin(box->pMin.x, point->x);
    unionbox.pMin.y = fmin(box->pMin.y, point->y);
    unionbox.pMin.z = fmin(box->pMin.z, point->z);
    unionbox.pMax.x = fmax(box->pMax.x, point->x);
    unionbox.pMax.y = fmax(box->pMax.y, point->y);
    unionbox.pMax.z = fmax(box->pMax.z, point->z);
    return unionbox;
}

Bbox unionBoxBox(Bbox *box1, Bbox *box2)
{
    Bbox unionbox;
    unionbox.pMin.x = fmin(box1->pMin.x, box2->pMin.x);
    unionbox.pMin.y = fmin(box1->pMin.y, box2->pMin.y);
    unionbox.pMin.z = fmin(box1->pMin.z, box2->pMin.z);
    unionbox.pMax.x = fmax(box1->pMax.x, box2->pMax.x);
    unionbox.pMax.y = fmax(box1->pMax.y, box2->pMax.y);
    unionbox.pMax.z = fmax(box1->pMax.z, box2->pMax.z);
    return unionbox;
}


Bbox intersectionBox(Bbox *box1, Bbox *box2)
{
    Bbox unionbox;
    unionbox.pMin.x = fmax(box1->pMin.x, box2->pMin.x);
    unionbox.pMin.y = fmax(box1->pMin.y, box2->pMin.y);
    unionbox.pMin.z = fmax(box1->pMin.z, box2->pMin.z);
    unionbox.pMax.x = fmin(box1->pMax.x, box2->pMax.x);
    unionbox.pMax.y = fmin(box1->pMax.y, box2->pMax.y);
    unionbox.pMax.z = fmin(box1->pMax.z, box2->pMax.z);
    return unionbox;
}


bool boxOverlaps(Bbox *box1, Bbox *box2) {
    bool x = (box1->pMax.x >= box2->pMin.x) && (box1->pMin.x <= box2->pMax.x);
    bool y = (box1->pMax.y >= box2->pMin.y) && (box1->pMin.y <= box2->pMax.y);
    bool z = (box1->pMax.z >= box2->pMin.z) && (box1->pMin.z <= box2->pMax.z);
    return (x && y && z);
}

bool insideBox(Vector *point, Bbox *box) {
    return (point->x >= box->pMin.x && point->x <= box->pMax.x &&
            point->y >= box->pMin.y && point->y <= box->pMax.y &&
            point->z >= box->pMin.z && point->z <= box->pMax.z);
}

bool insideExclusiveBox(Vector *point, Bbox *box) {
    return (point->x >= box->pMin.x && point->x < box->pMax.x &&
            point->y >= box->pMin.y && point->y < box->pMax.y &&
            point->z >= box->pMin.z && point->z < box->pMax.z);
}

Bbox expandBox(Bbox *box, Float delta) 
{
    Bbox expanded;
    expanded.pMin.x = box->pMin.x - delta;
    expanded.pMin.y = box->pMin.y - delta;
    expanded.pMin.z = box->pMin.z - delta;
    expanded.pMax.x = box->pMax.x + delta;
    expanded.pMax.y = box->pMax.x + delta;
    expanded.pMax.z = box->pMax.x + delta;
    return expanded;
}

Vector diagonalBox(Bbox *box)
{
    return substractVector(&box->pMax, &box->pMin);
}

Float surfaceAreaBox(Bbox *box)
{
    Vector d = diagonalBox(box);
    return 2*(d.x*d.y + d.x*d.z + d.y*d.z);
}

Float volumeBox(Bbox *box)
{
    Vector d = diagonalBox(box);
    return d.x*d.y*d.z;
}
    
int maximumExtendBox(Bbox *box)
{
    Vector d = diagonalBox(box);
    if (d.x > d.y && d.x > d.z)
        return 0;
    else if (d.y > d.z)
        return 1;
    else
        return 2;
}

Vector offsetInsideBox(Vector *point, Bbox *box)
{
    Vector o = substractVector(point, &box->pMin);
    if (box->pMax.x > box->pMin.x) o.x /= box->pMax.x - box->pMin.x;
    if (box->pMax.y > box->pMin.y) o.y /= box->pMax.y - box->pMin.y;
    if (box->pMax.z > box->pMin.z) o.z /= box->pMax.z - box->pMin.z;
    return o;

}

Float distanceSphere(Vector *point, Bbox *box)
{
    Float dx = fmax(0,fmax(box->pMin.x - point->x, point->x - box->pMin.x));
    Float dy = fmax(0,fmax(box->pMin.y - point->y, point->y - box->pMin.y));
    Float dz = fmax(0,fmax(box->pMin.z - point->z, point->z - box->pMin.z));
    return sqrt(dx * dx + dy * dy + dz * dz);
}

SimpleSphere boundingSphere(Bbox *box)
{
    SimpleSphere bounded;
    bounded.center = addVector(&box->pMin, &box->pMax);
    bounded.center.x = bounded.center.x*0.5;
    bounded.center.y = bounded.center.y*0.5;
    bounded.center.z = bounded.center.z*0.5;
    bounded.radius = insideBox(&bounded.center, box) ? distanceSphere(
                     &bounded.center, box ) : 0;
    return bounded;
}


