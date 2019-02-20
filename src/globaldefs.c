#include <stdio.h>
#include <stdlib.h>
#include "globaldefs.h"

void printfGenericShape(GenericShape shape)
{
    printf("shapetype: %d\n", shape.shapetype);
    printf("position: ");
    printVector(&shape.position); 
    printf("rad: %lf\n", shape.rad);
    printf("vec0: ");
    printVector(&shape.vec0);
    printf("plane: %lf, %lf, %lf, %lf\n", shape.cnst.A, shape.cnst.B, 
                                          shape.cnst.C, shape.cnst.D);
    printf("vec1: ");
    printVector(&shape.vec1);
    printf("vec2: ");
    printVector(&shape.vec2);
}

void printElementData(ElementData *Data){

    if(strcmp(Data->type, "triangle")==0){
        printf("type = %s\n", Data->type);
        printf("typeFill = %s\n", Data->typeFill);
        printf("color = %f, %f, %f\n", Data->color->x, Data->color->y, Data->color->z);
        printf("ka = %f\n", Data->ka);
        printf("kn = %f\n", Data->kn);
        printf("kd = %f\n", Data->kd);
        printf("fatt = %f\n", Data->fatt);
        printf("o1 = %f\n", Data->o1);
        printf("o2 = %f\n", Data->o2);
        printf("o3 = %f\n", Data->o3);
        printf("Ip = %f\n", Data->Ip);
        printf("Ia = %f\n", Data->Ia);
        printf("C = %f, %f, %f\n", Data->C.x, Data->C.y, Data->C.z);



    } else{
        printf("type = %s\n", Data->type);
        printf("position = %f, %f, %f\n", Data->position->x, Data->position->y, Data->position->z);
        printf("typeFill = %s\n", Data->typeFill);
        printf("color = %f, %f, %f\n", Data->color->x, Data->color->y, Data->color->z);
        printf("ka = %f\n", Data->ka);
        printf("kn = %f\n", Data->kn);
        printf("kd = %f\n", Data->kd);
        printf("fatt = %f\n", Data->fatt);
        printf("o1 = %f\n", Data->o1);
        printf("o2 = %f\n", Data->o2);
        printf("o3 = %f\n", Data->o3);
        printf("Ip = %f\n", Data->Ip);
        printf("Ia = %f\n", Data->Ia);
        printf("C = %f, %f, %f\n", Data->C.x, Data->C.y, Data->C.z);
    }
}

void printScene(Scene *Sceneactual){

    printf("eye = %f, %f, %f\n", Sceneactual->eye->x, Sceneactual->eye->y, Sceneactual->eye->z);
    printf("diffuse = %d\n", Sceneactual->diffuse);
    printf("specular = %d\n", Sceneactual->specular);
    printf("shadow = %d\n", Sceneactual->shadow);
    printf("levels = %d\n", Sceneactual->levels);
}

void printVector(Vector * vec){
    printf("Vector = %lf, %lf, %lf\n", vec->x, vec->y, vec->z);

}

void initrayscene(Ray * rayscene, Scene *scene){
    rayscene->origin.x = scene->eye->x;
    rayscene->origin.y = scene->eye->y;
    rayscene->origin.z = scene->eye->z;
}
