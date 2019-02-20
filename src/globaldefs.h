#ifndef _globaldefs_h
#define _globaldefs_h


#include <stdint.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <sys/sysinfo.h>
#include <pthread.h>

#define epsilom 0.005
#define CPU 0
#define GPU 1
#define APU 2
#define ON 1
#define OFF 0
#define NODEF -1

#define SPHERE 0
#define CYL 1
#define CONE 2
#define DISC 3
#define TRIANGLE 4


typedef double Float;
typedef struct ElementNode ElementNode;


typedef struct{
    Float x;
    Float y;
    Float z; 
} Vector;

typedef struct{  
    Vector pMin;
    Vector pMax;
} Bbox;

typedef struct LinearBVHNode {
    Bbox bounds;
    union {
        int primitivesOffset;   // leaf
        int secondChildOffset;  // interior
    };
    uint16_t nPrimitives;  // 0 -> interior node
    uint8_t axis;          // interior node: xyz
    uint8_t pad[1];        // ensure 32 byte total size
}LinearBVHNode;

typedef struct ElementData{
    char * type;
    Vector* position;
    char * typeFill;
    Vector* color;
    Float ka;
    Float kn;
    Float kd;
    Float ks;
    Float fatt;
    Float o1;
    Float o2;
    Float o3;
    void * specificData;   
    Float Ip;
    Float Ia;
    Vector C;   
} ElementData;


struct ElementNode{
    ElementData *data;
    struct ElementNode *next;
};

typedef struct Plane{
    Float A;
    Float B;
    Float C;
    Float D;
}Plane;

typedef struct Ray{
    Vector origin;
    Vector direction;
}Ray;

typedef struct LightAmbient{
    Float value;
    Vector * color;
} LightAmbient;

typedef struct{  
    Float t;
    int position;
} Interinfo;

typedef struct{
    Vector center;
    Float radius;        
} SimpleSphere;

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

typedef struct Scene{
    Vector * eye;
    ElementNode * lights;
    int diffuse;
    int specular;
    int shadow;
    //Float ambient;
    LightAmbient * ambientLight; 
    int levels;
    int transparencies;
    int dimx;
    int dimy;
    int architecture;
    int acceleration;
    int antialiasing; 
    GenericShape *orderedPrims;
    LinearBVHNode *bvhNodes;  
    int sizeScene; //Esta es la cantidad de primitivas
    int totalBVHNodes;
    GenericShape *prim;
}Scene;

Scene * scene;
Vector background;
Vector *image;
int *rayscounter;

void printfGenericShape(GenericShape shape);
void printElementData(ElementData *Data);
void printScene(Scene *Sceneactual);
void printVector(Vector * vec);
void initrayscene(Ray * rayscene, Scene *scene);

#endif

