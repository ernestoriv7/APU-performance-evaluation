#include"methods.h"



int verifyShadow(Vector *intersect, Scene *scene, ElementNode *light);
Vector recoverIntersectionColor(Float  tvalue, Ray *ray, GenericShape *object, 
                                Scene *scene, int levels, int transparencies);
Interinfo intersectionBrute(Ray *rayscene, GenericShape *shape);
Interinfo intersectionBruteBox(Ray *rayscene, GenericShape *shape);
int shadowIntersectBrute(Ray *shadray, Float lightdist);

int shadowIntersectBrute(Ray *shadray, Float lightdist)
{
    Float tintersect = 0;
    for(int i=0; i < scene->sizeScene; i++){
        GenericShape primitive = scene->prim[i];
        tintersect = getIntersection(shadray, &primitive);
        if(tintersect > epsilom && tintersect < lightdist){        
            return 1;
        } 
    }
    return 0;
}

int intersectionBVHShadow(Ray *shadray, Float lightdist)
{
    Float boxintersect = 0;

    int toVisitOffset = 0; 
    int currentNodeIndex = 0;
    int nodesToVisit[128];

     while (true) {
        LinearBVHNode *node = &scene->bvhNodes[currentNodeIndex];
        // Check ray against BVH node
        boxintersect = intersectsBox(shadray, &node->bounds);
        if (boxintersect > epsilom) {
            if (node->nPrimitives > 0) {
                // Intersect ray with primitives in leaf BVH node
                Float tintersect = getIntersection(shadray,
                                   &scene->orderedPrims[node->primitivesOffset]);
                if (tintersect > epsilom && tintersect < lightdist){
                    return 1;
                }   
                if (toVisitOffset == 0) break;
                currentNodeIndex = nodesToVisit[--toVisitOffset];
            } else {
                // Put far BVH node on _nodesToVisit_ stack, advance to near
                // node
                Float t1 = intersectsBox(shadray,      
                           &scene->bvhNodes[currentNodeIndex+1].bounds);
                Float t2 = intersectsBox(shadray,      
                           &scene->bvhNodes[node->secondChildOffset].bounds);
                if(t1 == -1) t1 = 9999999;
                if(t2 == -1) t2 = 9999999;

                if (t2 < t1) {
                    nodesToVisit[toVisitOffset++] = currentNodeIndex + 1;
                    currentNodeIndex = node->secondChildOffset;
                } else {
                    nodesToVisit[toVisitOffset++] = node->secondChildOffset;
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




Interinfo intersectionBrute(Ray *rayscene, GenericShape *shape)
{
    Interinfo finalintersection = {9999999,0};
    Float tintersect = 0;
    for(int i=0; i < scene->sizeScene; i++){
        GenericShape primitive = scene->prim[i];
        tintersect = getIntersection(rayscene, &primitive);
        if(tintersect > epsilom && tintersect < finalintersection.t){
                finalintersection.t = tintersect;
                finalintersection.position = i;
        }
    }
    return finalintersection;
}

Interinfo intersectionBruteBox(Ray *rayscene, GenericShape *notused)
{
    int sizeScene = scene->sizeScene;
    Interinfo finalintersection = {9999999,0};
    Float tintersect = 0;
    for(int i=0; i < sizeScene; i++){
        GenericShape shape = scene->prim[i];
        if(shape.shapetype == SPHERE){   
            Bbox prueba = sphereBox(shape);
            tintersect = intersectsBox(rayscene, &prueba);
        } else if(shape.shapetype == CYL){
            Bbox prueba = cylinderBox(shape);
            tintersect = intersectsBox(rayscene, &prueba);          
        } else if(shape.shapetype == CONE){
            Bbox prueba = coneBox(shape);
            tintersect = intersectsBox(rayscene, &prueba);           
        } else if(shape.shapetype == DISC){  
            Bbox prueba = discBox(shape);
            tintersect = intersectsBox(rayscene, &prueba);          
        } else if(shape.shapetype == TRIANGLE){      
            Bbox prueba = triangleBox(shape);
            tintersect = intersectsBox(rayscene, &prueba);    
        }
        if(tintersect > 0 && tintersect < finalintersection.t){
                finalintersection.t = tintersect;
                finalintersection.position = i;
        }
    }
    return finalintersection;
}


Interinfo intersectionBVH(Ray *rayscene, GenericShape *primitives, 
                          LinearBVHNode *nodes, int sizeScene)
{
    Interinfo finalint = {9999999,0};
    Float boxintersect = 0;

    int toVisitOffset = 0; 
    int currentNodeIndex = 0;
    int nodesToVisit[128];

     while (true) {
        LinearBVHNode *node = &nodes[currentNodeIndex];
        // Check ray against BVH node
        boxintersect = intersectsBox(rayscene, &node->bounds);
        if (boxintersect > epsilom && boxintersect < finalint.t  ) {
            if (node->nPrimitives > 0) {
                // Intersect ray with primitives in leaf BVH node
                Float tintersect = getIntersection(rayscene,
                                   &primitives[node->primitivesOffset]);
                if (tintersect > epsilom && tintersect < finalint.t){
                    finalint.t = tintersect;        
                    finalint.position = node->primitivesOffset;
                }   
                if (toVisitOffset == 0) break;
                currentNodeIndex = nodesToVisit[--toVisitOffset];
            } else {
                // Put far BVH node on _nodesToVisit_ stack, advance to near
                // node
                Float t1 = intersectsBox(rayscene,      
                           &nodes[currentNodeIndex+1].bounds);
                Float t2 = intersectsBox(rayscene,      
                           &nodes[node->secondChildOffset].bounds);
                if(t1 == -1) t1 = 9999999;
                if(t2 == -1) t2 = 9999999;

                if (t2 < t1) {
                    nodesToVisit[toVisitOffset++] = currentNodeIndex + 1;
                    currentNodeIndex = node->secondChildOffset;
                } else {
                    nodesToVisit[toVisitOffset++] = node->secondChildOffset;
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


//Acceleration type will be used here
Vector whichColorIsIt(Ray *ray, int x, int y)
{
    Vector background = {0.5, 0.5, 0.5};
    Vector refraction = {0.1, 0.1, 0.1};
    int toVisitOffset = 0; 
    int currentNodeIndex = 0;
    nodesTree dfsNodes[128];
    nodesTree raysToVisit[128];

    int levels = scene->levels;
    int transparencies = scene->transparencies;
    int parentpos = 0;
    Ray iray = *ray;
    Float intensitydif;
    Float intensityspe;
    int colortype = 1;
    Vector color = {0,0,0}; 
    SceneLights *lights = initSceneLights();
    int sizeLights = size(scene->lights);

    GenericShape *primitives;
    if(scene->acceleration == ON)
        primitives = scene->orderedPrims;
    else
        primitives = scene->prim;
   
    while(true){
   
        Interinfo inter;
        if(scene->acceleration == ON)
            inter = intersectionBVH(&iray, primitives, scene->bvhNodes, 
                                    scene->sizeScene);
        else
            inter = intersectionBrute(&iray, primitives);

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
            Vector intersection = intersectionPoint(&iray, inter.t);
            Vector N = objectNormal(intersection, primitives[inter.position]);
            Vector V = inverseVector(&iray.origin, &intersection);
            for(int i=1; i <= sizeLights; i++){
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
                    rayscounter[matrixOffset(x, y, scene->dimx)] += 1;       
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
                    rayscounter[matrixOffset(x, y, scene->dimx)] += 1;             
                }
                Ray shadow;
                shadow.origin = intersection;
                Vector dir = lights[i].par;
                dir = substractVector(&dir, &shadow.origin); 
                shadow.direction = normalizedVector(&dir);
                Float lightdst = vectorNorm(&dir);
                rayscounter[matrixOffset(x, y, scene->dimx)] += 1;

                int shadowcheck;                
                if(scene->acceleration == ON)
                    shadowcheck = intersectionBVHShadow(&shadow, lightdst);
                else
                    shadowcheck = shadowIntersectBrute(&shadow, lightdst);
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

    for(int i = currentNodeIndex - 1; i >= 0; i--){
        if(i == 0 && dfsNodes[i].inter.t == 9999999){
            return dfsNodes[i].color;
        }
        else if(i == 0){
            color = dfsNodes[i].color;
            color = difuseColor(&color, fmin(1, dfsNodes[i].intensitydif));
            color = specularColor(&color, fmin(1, dfsNodes[i].intensityspe));
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
                thiscol = difuseColor(&thiscol, fmin(1, dfsNodes[i].intensitydif));
                thiscol = specularColor(&thiscol, fmin(1, dfsNodes[i].intensityspe));              
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
                thiscol = difuseColor(&thiscol, fmin(1, dfsNodes[i].intensitydif));
                thiscol = specularColor(&thiscol, fmin(1, dfsNodes[i].intensityspe));              
                thiscol = multiplyConstantVector(o3, thiscol);
                Vector parentcolor = dfsNodes[dfsNodes[i].parentpos].color;
                dfsNodes[dfsNodes[i].parentpos].color = addVector(&parentcolor, 
                                                                  &thiscol);
            }
        }            
    }

    return color;
}


Vector antialiasColor(int x, int y){
    Ray raythread;
    initrayscene( &raythread, scene); 
    Vector finalcolor;
    Vector intermediate;
    Float average = (Float)1/5;
    
    Float offset= (Float)1/2;

    raythread.direction = obtainNormalizedDirection(x, y);
    rayscounter[matrixOffset(x, y, scene->dimx)] += 1;
    finalcolor = whichColorIsIt(&raythread, x, y);

    raythread.direction = obtainNormalizedDirection(x-offset, y);
    rayscounter[matrixOffset(x, y, scene->dimx)] += 1;
    intermediate = whichColorIsIt(&raythread, x, y);
    finalcolor = addVector(&finalcolor, &intermediate);

    raythread.direction = obtainNormalizedDirection(x+offset, y);
    rayscounter[matrixOffset(x, y, scene->dimx)] += 1;
    intermediate = whichColorIsIt(&raythread, x, y);
    finalcolor = addVector(&finalcolor, &intermediate);


    raythread.direction = obtainNormalizedDirection(x, y-offset);
    rayscounter[matrixOffset(x, y, scene->dimx)] += 1;
    intermediate = whichColorIsIt(&raythread, x, y);
    finalcolor = addVector(&finalcolor, &intermediate);

    raythread.direction = obtainNormalizedDirection(x, y+offset);
    rayscounter[matrixOffset(x, y, scene->dimx)] += 1;
    intermediate = whichColorIsIt(&raythread, x, y);
    finalcolor = addVector(&finalcolor, &intermediate);
    
    finalcolor.x = finalcolor.x * average;
    finalcolor.y = finalcolor.y * average;
    finalcolor.z = finalcolor.z * average;

    return finalcolor;   
    
}



/*
Vector whichColorIsIt(Ray *rayscene, Scene *scene, int levels, 
                      int transparencies){   
    
    Vector color;
    Interinfo intersection;

    if(scene->acceleration == ON){
        intersection = intersectionBVH(rayscene, 
                       scene->orderedPrims, scene->bvhNodes,
                       scene->sizeScene);

        if (intersection.t != 9999999){
            GenericShape primitive= scene->orderedPrims[intersection.position];
            color = recoverIntersectionColor(intersection.t, rayscene,
                    &primitive, scene, levels, transparencies);
            return color;
        } else
            return background;

    } else{
        intersection = intersectionBrute(rayscene, 
                       scene->prim);

        if (intersection.t != 9999999){
            GenericShape primitive= scene->prim[intersection.position];
            color = recoverIntersectionColor(intersection.t, rayscene,
                    &primitive, scene, levels, transparencies);
            return color;
        }else
            return background;
    }
    return background;
}

int verifyShadow(Vector *intersect, Scene *scene, ElementNode *light){   
    Ray shadow;
    shadow.origin = *intersect;
    Vector dir = substractVector(light->data->position, &shadow.origin); 
    shadow.direction = normalizedVector(&dir);
    Float distanceLight = vectorNorm(&dir);    

    if(scene->acceleration == ON)
        return shadowIntersectBVH(&shadow, distanceLight);
    else
        return shadowIntersectBrute(&shadow, distanceLight);
}

Vector recoverIntersectionColor(Float  tvalue, Ray *ray, GenericShape *object, 
                                Scene *scene, int levels, int transparencies)
{
    
    LightAmbient *lightAmbient = scene->ambientLight;
    ElementNode *lights = scene->lights;
    Float intensitydif= lightAmbient->value*object->ka;
    Float intensityspe= 0;
    Vector intersection  = intersectionPoint(ray, tvalue);
    Vector N;
    
    if(object->shapetype == SPHERE){
        Float radius = object->rad;
        N = normalVectorSphere(intersection, object->position, radius);
    } else if(object->shapetype == CYL){
        Float radius = object->rad;
        Vector direction = object->vec0;
        N = normalVectorCylinder(intersection, object->position,
                                 direction, radius);
    } else if(object->shapetype == CONE){
        Vector direction = object->vec0;
        N = normalVectorCone(intersection, object->position, direction);
    } else if(object->shapetype == DISC){
        N.x = object->cnst.A;
        N.y = object->cnst.B;
        N.z = object->cnst.C;
    }
    else if(object->shapetype == TRIANGLE){
        N.x = object->cnst.A;
        N.y = object->cnst.B;
        N.z = object->cnst.C;
        N = negateVector(&N);
    }
   
    Vector color = object->color;
          
    Vector V = inverseVector(&ray->origin, &intersection);     
    Float o1= object->o1;
    Float o2= object->o2;
    Float o3= object->o3;
    color = multiplyConstantVector(o1, color);

    int sizeLights = size(lights), i;
    for(i=0; i < sizeLights; i++){
        ElementNode *currentLight = getAt(&lights,i);        
        Vector L = lightVectorL(intersection, *currentLight->data->position); 
            //N = obtainPositiveNormal(object->type, N, L);                 
        Vector R = reflexVector(&L, &N);
        Ray raythread = {intersection, R};
        
        if((levels > 0 && o2 != 0)){                        
            Vector colorreflected = multiplyConstantVector(o2,      
                                    whichColorIsIt(&raythread, scene,
                                    levels-1, transparencies));   
            color = addVector(&color, &colorreflected);
        }
        if(transparencies > 0 && o3 != 0){
            raythread.direction = ray->direction;  
            Vector colortransparencies = multiplyConstantVector(o3,
                                         whichColorIsIt(&raythread, scene,
                                         levels, transparencies -1));
            color = addVector(&color, &colortransparencies);  
        }

        if(verifyShadow(&intersection, scene, currentLight)){
    
        } else{
            
            Float difuse = difuseLight(&L,  &N, &intersection, currentLight->data, object->kd);  
            Float specular= specularLight(&V,  &R, &intersection, currentLight->data, object->kn, object->ks);
            intensitydif += difuse;
            intensityspe += specular;
        }
    }
    color = difuseColor(&color, fmin(1, intensitydif));
    color = specularColor(&color, fmin(1, intensityspe));
    
    return color;
    
}

*/


