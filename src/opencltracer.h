#ifndef _opencltracer_h
#define _opencltracer_h

#define CL_USE_DEPRECATED_OPENCL_1_2_APIS
#include <CL/cl.h>
#include <CL/opencl.h>
#include "../Utils/utils.h"
#include "globaldefs.h"
#include "transformations.h"
#include "shapes.h"
#include "methods.h"

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

SceneInfo *initSceneInfo();
SceneLights *initSceneLights();
void printDeviceInfo(cl_device_id device);
void plotPixel(int ix, int iy, int value);
void rayTracerGPU();

#endif
