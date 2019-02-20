#include "sceneparser.h"

Vector * readVector(char * string);
Vector * readColor(char * string);

GenericShape  parseSphere( char * configurationText );
ElementData * parseCube( char * configurationText );
GenericShape parseCylinder( char * configText);
GenericShape parseDisc( char * configText );
GenericShape parseTriangle( char * configText );
GenericShape parseCone( char * configText);

LightAmbient * parseAmbientLight(char * configText);
ElementData * parseLight(char * configText);

Vector * parseEye(char * configText);
int parseSpecular(char * configText);
int parseDiffuse(char * configText);
int parseShadow(char * configText);
int parseMirrorLevels(char * configText);
int parseXResolution(char * configText);
int parseYResolution(char * configText);
int parseSceneSize(char * configText);
int parseArchitecture(char * configText);
int parseAcceleration(char * configText);
int parseTransparencies(char * configText);
int parseAntialiasing(char * configText);
int readFlag( char* configText);


void  postProcessTriangle(TriangleSpecificData * specificData);
void  postProcessDisc(DiscAditionalData * specificData, Vector* position);


Scene * parserScene (char * file ){
    
    char *saveptr1;
    //char *type;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    
    FILE *fp;
    
 //   ElementNode * scene = NULL;

    Scene *newScene = malloc(sizeof(Scene));
    newScene->eye = NULL;
    newScene->lights = NULL;  
    newScene->ambientLight = NULL;    
    fp = fopen(file, "r");
    if (fp == NULL) 
        exit(EXIT_FAILURE);
    int primpos = 0;

   while ((read = getline(&line, &len, fp)) != -1) {
        //Reading the type of the polygons
        char * type = strtok_r(line, "&", &saveptr1);

         if (strcmp(type,"scenesize") == 0){
            int size = parseSceneSize(saveptr1);
            newScene->sizeScene = size;
            newScene->prim = calloc(size, sizeof(GenericShape));
            if(newScene->prim == NULL) exit(-1);
        } else if(strcmp(type,"sphere") == 0){
            //SPHERE
            newScene->prim[primpos++] = parseSphere(saveptr1);
        } else if (strcmp(type,"cylinder") == 0){
        //Cilinder
            newScene->prim[primpos++] = parseCylinder(saveptr1); 
        } else if (strcmp(type,"cone") == 0){
        //Cone
            newScene->prim[primpos++] = parseCone(saveptr1); 
        } else if (strcmp(type,"disc") == 0){
        //DISC
            newScene->prim[primpos++] = parseDisc(saveptr1); 
        } else if (strcmp(type,"triangle") == 0){
        //Triangle
            newScene->prim[primpos++] = parseTriangle(saveptr1); 
        } else if (strcmp(type,"light") == 0){
            ElementData * newLight = parseLight(saveptr1);
            push(&newScene->lights,&newLight);
        } else if (strcmp(type,"diffuse") == 0){
            newScene->diffuse = parseDiffuse(saveptr1);
        } else if (strcmp(type,"specular") == 0){
            newScene->specular = parseSpecular(saveptr1);
        } else if (strcmp(type,"eye") == 0){
            newScene->eye = parseEye(saveptr1);
        } else if (strcmp(type,"/") == 0){
            //DO NOTHING its a commnet
        } else if (strcmp(type,"SHAD") == 0){
            newScene->shadow = parseShadow(saveptr1);
        } else if (strcmp(type,"ambientlight") == 0){
            newScene->ambientLight = parseAmbientLight(saveptr1);
        } else if (strcmp(type,"reflections") == 0){
            newScene->levels = parseMirrorLevels(saveptr1); 
        } else if (strcmp(type,"transparencies") == 0){
            newScene->transparencies = parseTransparencies(saveptr1); 
        } else if (strcmp(type,"xresolution") == 0){
            newScene->dimx = parseXResolution(saveptr1); 
        } else if (strcmp(type,"yresolution") == 0){
            newScene->dimy = parseYResolution(saveptr1); 
        } else if (strcmp(type,"architecture") == 0){
            newScene->architecture = parseArchitecture(saveptr1); 
        } else if (strcmp(type,"antialiasing") == 0){
            newScene->antialiasing = parseAntialiasing(saveptr1); 
        } else if (strcmp(type,"BVHacceleration") == 0){
            newScene->acceleration = parseAcceleration(saveptr1); 
        }
        else {
            printf("UNKOWN POLYGON\n");
        
        }
    }
    //puts("Pase de acdda");
    free(line);
    fclose(fp);
  
    return newScene;
}

// Parsers of polygons

GenericShape parseSphere( char * configText){
    char *saveptr1;
  //  char * fragment = NULL;
    char * position = strtok_r(configText, "&", &saveptr1);
    Vector * positionVector = readVector(position);
    char * radius  = strtok_r(NULL, "&", &saveptr1);
    GenericShape data;
    data.position = *positionVector;
    free(positionVector);
    data.shapetype = SPHERE;

    char * typeTexture  = strtok_r(NULL, "&", &saveptr1);

    if(strcmp(typeTexture,"C") == 0){
        char * colorString  = strtok_r(NULL, "&", &saveptr1);
        Vector * newColor = readColor(colorString);        
       // data.typeFill = "C";
        data.color = *newColor;
        free (newColor);
    }
    //KA&KN&KD&KS
    char * kaString = strtok_r(NULL, "&", &saveptr1);    
    Float ka = strtof(kaString,NULL);

    char * knString = strtok_r(NULL, "&", &saveptr1);    
    Float kn = strtof(knString,NULL);

    char * kdString = strtok_r(NULL, "&", &saveptr1);    
    Float kd = strtof(kdString,NULL);

    char * ksString = strtok_r(NULL, "&", &saveptr1);    
    Float ks = strtof(ksString,NULL);

    char * fattString = strtok_r(NULL, "&", &saveptr1);    
    Float fatt = strtof(fattString,NULL);

    char * o1String = strtok_r(NULL, "&", &saveptr1);    
    Float o1 = strtof(o1String,NULL);

    char * o2String = strtok_r(NULL, "&", &saveptr1);    
    Float o2 = strtof(o2String,NULL);
    
    char * o3String = strtok_r(NULL, "&", &saveptr1);    
    Float o3 = strtof(o3String,NULL);

    data.ka = ka;
    data.kn = kn;
    data.kd = kd;
    data.ks = ks;
    data.fatt = fatt;
    data.o1 = o1;
    data.o2 = o2;
    data.o3 = o3;

    // Added the custom function for evaluate intersection with spheres
  //  data->intersectFunction = (Interinfo*)&intersectsSphere;

    data.rad = strtof(radius,NULL);
    return data;
}

GenericShape parseCylinder( char * configText){
    char *saveptr1;
    char * position = strtok_r(configText, "&", &saveptr1);
    Vector * positionVector = readVector(position);
    char * radius  = strtok_r(NULL, "&", &saveptr1);

    char * direction  = strtok_r(NULL, "&", &saveptr1);
    Vector * directionVector = readVector(direction);

    char * d1String = strtok_r(NULL, "&", &saveptr1);    
    Float d1 = strtof(d1String,NULL);

    char * d2String = strtok_r(NULL, "&", &saveptr1);    
    Float d2 = strtof(d2String,NULL);

    GenericShape data;
    data.position = *positionVector;
    free(positionVector);
    data.shapetype = CYL;

    char * typeTexture  = strtok_r(NULL, "&", &saveptr1);

    if(strcmp(typeTexture,"C") == 0){
        char * colorString  = strtok_r(NULL, "&", &saveptr1);
        Vector * newColor = readColor(colorString);
        //data.typeFill = "C";
        data.color = *newColor;
        free(newColor);
    }
    //KA&KN&KD&KS
    char * kaString = strtok_r(NULL, "&", &saveptr1);    
    Float ka = strtof(kaString,NULL);

    char * knString = strtok_r(NULL, "&", &saveptr1);    
    Float kn = strtof(knString,NULL);

    char * kdString = strtok_r(NULL, "&", &saveptr1);    
    Float kd = strtof(kdString,NULL);

    char * ksString = strtok_r(NULL, "&", &saveptr1);    
    Float ks = strtof(ksString,NULL);

    char * fattString = strtok_r(NULL, "&", &saveptr1);    
    Float fatt = strtof(fattString,NULL);

    char * o1String = strtok_r(NULL, "&", &saveptr1);    
    Float o1 = strtof(o1String,NULL);

    char * o2String = strtok_r(NULL, "&", &saveptr1);    
    Float o2 = strtof(o2String,NULL);

    char * o3String = strtok_r(NULL, "&", &saveptr1);    
    Float o3 = strtof(o3String,NULL);

   


    data.ka = ka;
    data.kn = kn;
    data.kd = kd;
    data.ks = ks;
    data.fatt = fatt;
    data.o1 = o1;
    data.o2 = o2;
    data.o3 = o3;

    data.rad =  strtof(radius,NULL);
    data.vec0 = *directionVector;
    free(directionVector);
    data.cnst.A = d1;
    data.cnst.B = d2;
    return data;
}

GenericShape parseCone( char * configText){
    char *saveptr1;
    char * position = strtok_r(configText, "&", &saveptr1);
    Vector * positionVector = readVector(position);

    char * direction  = strtok_r(NULL, "&", &saveptr1);
    Vector * directionVector = readVector(direction);

    char * d1String = strtok_r(NULL, "&", &saveptr1);    
    Float d1 = strtof(d1String,NULL);

    char * d2String = strtok_r(NULL, "&", &saveptr1);    
    Float d2 = strtof(d2String,NULL);

    GenericShape data;
    data.position = *positionVector;
    free(positionVector);
    data.shapetype = CONE;

    char * typeTexture  = strtok_r(NULL, "&", &saveptr1);

    if(strcmp(typeTexture,"C") == 0){
        char * colorString  = strtok_r(NULL, "&", &saveptr1);
        Vector * newColor = readColor(colorString);
      //  data.typeFill = "C";
        data.color = *newColor;
        free(newColor);
    }
    //KA&KN&KD&KS
    char * kaString = strtok_r(NULL, "&", &saveptr1);    
    Float ka = strtof(kaString,NULL);

    char * knString = strtok_r(NULL, "&", &saveptr1);    
    Float kn = strtof(knString,NULL);

    char * kdString = strtok_r(NULL, "&", &saveptr1);    
    Float kd = strtof(kdString,NULL);

    char * ksString = strtok_r(NULL, "&", &saveptr1);    
    Float ks = strtof(ksString,NULL);

    char * fattString = strtok_r(NULL, "&", &saveptr1);    
    Float fatt = strtof(fattString,NULL);

    char * o1String = strtok_r(NULL, "&", &saveptr1);    
    Float o1 = strtof(o1String,NULL);

    char * o2String = strtok_r(NULL, "&", &saveptr1);    
    Float o2 = strtof(o2String,NULL);

    char * o3String = strtok_r(NULL, "&", &saveptr1);    
    Float o3 = strtof(o3String,NULL);

    char * k1String = strtok_r(NULL, "&", &saveptr1);    
    Float k1 = strtof(k1String,NULL);

    char * k2String = strtok_r(NULL, "&", &saveptr1);    
    Float k2 = strtof(k2String,NULL);

    data.ka = ka;
    data.kn = kn;
    data.kd = kd;
    data.ks = ks;
    data.fatt = fatt;
    data.o1 = o1;
    data.o2 = o2;
    data.o3 = o3;
    // Added the custom function for evaluate intersection with spheres
    //data->intersectFunction = &intersectsCilinder;

  
    data.vec0 = *directionVector;
    free(directionVector);
    data.cnst.A = d1;
    data.cnst.B = d2;
    data.cnst.C = k1;
    data.cnst.D = k2;   
    return data;
}

GenericShape parseDisc( char * configText ){
    char *saveptr1;
    char * position = strtok_r(configText, "&", &saveptr1);
    Vector * positionVector = readVector(position);
    char * radius  = strtok_r(NULL, "&", &saveptr1);

    char * direction  = strtok_r(NULL, "&", &saveptr1);
    Vector * directionVector = readVector(direction);

    GenericShape data;
    data.position = *positionVector;
    free(positionVector);
    data.shapetype = DISC;

    char * typeTexture  = strtok_r(NULL, "&", &saveptr1);

    if(strcmp(typeTexture,"C") == 0){
        char * colorString  = strtok_r(NULL, "&", &saveptr1);
        Vector * newColor = readColor(colorString);
        //data.typeFill = "C";
        data.color = *newColor;
        free(newColor);
    }
    //KA&KN&KD&KS
    char * kaString = strtok_r(NULL, "&", &saveptr1);    
    Float ka = strtof(kaString,NULL);

    char * knString = strtok_r(NULL, "&", &saveptr1);    
    Float kn = strtof(knString,NULL);

    char * kdString = strtok_r(NULL, "&", &saveptr1);    
    Float kd = strtof(kdString,NULL);

    char * ksString = strtok_r(NULL, "&", &saveptr1);    
    Float ks = strtof(ksString,NULL);

    char * fattString = strtok_r(NULL, "&", &saveptr1);    
    Float fatt = strtof(fattString,NULL);

    char * o1String = strtok_r(NULL, "&", &saveptr1);    
    Float o1 = strtof(o1String,NULL);

    char * o2String = strtok_r(NULL, "&", &saveptr1);    
    Float o2 = strtof(o2String,NULL);

    char * o3String = strtok_r(NULL, "&", &saveptr1);    
    Float o3 = strtof(o3String,NULL);

    data.ka = ka;
    data.kn = kn;
    data.kd = kd;
    data.ks = ks;
    data.fatt = fatt;
    data.o1 = o1;
    data.o2 = o2;
    data.o3 = o3;

    // Added the custom function for evaluate intersection with spheres
   // data->intersectFunction = &intersectsDisc;

   
    data.rad =  strtof(radius,NULL);
    data.vec0 = *directionVector;
    free(directionVector);
    data.cnst = getNormalizePlane(&data.position, &data.vec0);
    return data;
}


GenericShape parseTriangle( char * configText ){
    char *saveptr1;
    char * rotation = strtok_r(configText, "&", &saveptr1);
    char * translation  = strtok_r(NULL, "&", &saveptr1);
    
    GenericShape data;
    data.shapetype = TRIANGLE;
    data.position = (Vector){0, 0, 0};
    char * typeTexture  = strtok_r(NULL, "&", &saveptr1);
    if(strcmp(typeTexture,"C") == 0){
        char * colorString  = strtok_r(NULL, "&", &saveptr1);
        Vector * newColor = readColor(colorString);
       // data.typeFill = "C";
        data.color = *newColor;
        free(newColor);
    }
    //KA&KN&KD&KS
    char * kaString = strtok_r(NULL, "&", &saveptr1);    
    Float ka = strtof(kaString,NULL);

    char * knString = strtok_r(NULL, "&", &saveptr1);    
    Float kn = strtof(knString,NULL);

    char * kdString = strtok_r(NULL, "&", &saveptr1);    
    Float kd = strtof(kdString,NULL);

    char * ksString = strtok_r(NULL, "&", &saveptr1);    
    Float ks = strtof(ksString,NULL);

    char * fattString = strtok_r(NULL, "&", &saveptr1);    
    Float fatt = strtof(fattString,NULL);
    
    char * o1String = strtok_r(NULL, "&", &saveptr1);    
    Float o1 = strtof(o1String,NULL);

    char * o2String = strtok_r(NULL, "&", &saveptr1);    
    Float o2 = strtof(o2String,NULL);

    char * o3String = strtok_r(NULL, "&", &saveptr1);    
    Float o3 = strtof(o3String,NULL);
    

    data.ka = ka;
    data.kn = kn;
    data.kd = kd;
    data.ks = ks;
    data.fatt = fatt;
    data.o1 = o1;
    data.o2 = o2;
    data.o3 = o3;

    //printf("El valor de  o1, o2 y o3 = %f, %f y %f\n", o1, o2, o3);

   
    Vector *drotation =  readVector(rotation);
    Vector *dtranslation =  readVector(translation);
    free(drotation);
    free(dtranslation);
    
    char * vertexesString = strtok_r(NULL, "&", &saveptr1);

    char * vertexString = strtok_r(vertexesString, "/", &saveptr1);
    char * saveprt2;

    char * xString = strtok_r(vertexString, ",", &saveprt2);
    char * yString = strtok_r(NULL, ",", &saveprt2);
    char * zString = strtok_r(NULL, ",", &saveprt2);
    data.vec0.x = strtof(xString,NULL);
    data.vec0.y = strtof(yString,NULL);
    data.vec0.z = strtof(zString,NULL);
    vertexString = strtok_r(NULL, "/", &saveptr1);
    
    xString = strtok_r(vertexString, ",", &saveprt2);
    yString = strtok_r(NULL, ",", &saveprt2);
    zString = strtok_r(NULL, ",", &saveprt2);
    data.vec1.x = strtof(xString,NULL);
    data.vec1.y = strtof(yString,NULL);
    data.vec1.z = strtof(zString,NULL);
    vertexString = strtok_r(NULL, "/", &saveptr1);

    xString = strtok_r(vertexString, ",", &saveprt2);
    yString = strtok_r(NULL, ",", &saveprt2);
    zString = strtok_r(NULL, ",", &saveprt2);
    data.vec2.x = strtof(xString,NULL);
    data.vec2.y = strtof(yString,NULL);
    data.vec2.z = strtof(zString,NULL);
    vertexString = strtok_r(NULL, "/", &saveptr1);

    Vector cross_product = crossProductPlane(&data.vec0, &data.vec1, 
                                             &data.vec2);
    data.cnst = getNormalizePlane(&data.vec0, &cross_product);

    return data;
}



//ParserLight

ElementData * parseLight(char * configText){
    char *saveptr1;
   // ElementNode * newNode = malloc(sizeof(ElementNode));
    ElementData * newNodeData = malloc(sizeof(ElementData));
    char * position = strtok_r(configText, "&", &saveptr1);
    char * color = strtok_r(NULL, "&", &saveptr1);
    Vector * VectorPosition = readVector(position);
    newNodeData->position = VectorPosition;    
    Vector * colorPointer = readColor(color);
    newNodeData->color = colorPointer;
    char * IpString = strtok_r(NULL, "&", &saveptr1);    
    Float iP = strtof(IpString,NULL);

    newNodeData->Ip = iP;

    //newNode->data = newNodeData;

    return newNodeData;
}

Vector * parseEye(char * configText){
    return readVector(configText);
}

int parseSpecular(char * configText){
    return readFlag(configText);
}

int parseShadow(char * configText){
    return readFlag(configText);
}

int parseDiffuse(char * configText){
    return readFlag(configText);
}

int parseMirrorLevels(char * configText){
    return readFlag(configText);
}

int parseXResolution(char * configText){
    return readFlag(configText);
}

int parseYResolution(char * configText){
    return readFlag(configText);
}

int parseAcceleration(char * configText){

    if(strcmp(configText,"ON\n") == 0){
        return ON;
    } else if (strcmp(configText,"OFF\n") == 0){
        return OFF;
    }
    return OFF;
}

int parseSceneSize(char * configText){
    return readFlag(configText);
}

int parseArchitecture(char * configText){

    if(strcmp(configText,"CPU\n") == 0){
        return CPU;
    } else if (strcmp(configText,"GPU\n") == 0){
        return GPU;
    } else if (strcmp(configText,"APU\n") == 0){
        return APU;
    }
    return NODEF;
}

int parseAntialiasing(char * configText){
    
    if(strcmp(configText,"ON\n") == 0){
        return ON;
    } else if (strcmp(configText,"OFF\n") == 0){
        return OFF;
    }
    return OFF;
}

int parseTransparencies(char * configText){
    
    return readFlag(configText);
}

LightAmbient * parseAmbientLight(char * configText){
    char *saveptr1;
    LightAmbient * newNode = malloc(sizeof(LightAmbient));
    char * value = strtok_r(configText, "&", &saveptr1);

    char * color = strtok_r(NULL, "&", &saveptr1);

    newNode->color = readColor(color);
    newNode->value = strtof(value,NULL);

    return newNode;
}


//  Common Functions 


int readFlag( char* configText){
    return atoi(configText);
}

Vector* readVector(char * string){
    char *saveptr1;
    //char * fragment = NULL;
    char * xString = strtok_r(string, ",", &saveptr1);
    char * yString = strtok_r(NULL, ",", &saveptr1);
    char * zString = strtok_r(NULL, ",", &saveptr1);    
    Float x = strtof(xString,NULL);
    Float y = strtof(yString,NULL);
    Float z = strtof(zString,NULL);

    Vector* newVector = malloc(sizeof(Vector));
    newVector->x = x;
    newVector->y = y;
    newVector->z = z;

    return newVector;
}



Vector * readColor(char * string){
    char *saveptr1;
    //char * fragment = NULL;
    char * rString = strtok_r(string, ",", &saveptr1);
    char * gString = strtok_r(NULL, ",", &saveptr1);
    char * bString = strtok_r(NULL, ",", &saveptr1);    
    Float r = strtof(rString,NULL);
    Float g = strtof(gString,NULL);
    Float b = strtof(bString,NULL);

    Vector* newVector = malloc( sizeof(Vector));
    newVector->x = r;
    newVector->y = g;
    newVector->z = b;

    return newVector;
}



