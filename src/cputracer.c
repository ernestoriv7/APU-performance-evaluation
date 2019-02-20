#include"cputracer.h"

#define TILEDIMENSION 16

typedef struct{
    int xstart; 
    int xfinish;
    int ystart;
    int yfinish;      
} WorkDispatch;

static pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
static int remainingjobs = 0;
static int totaljobs = 0;
static WorkDispatch *threadWorks;

pthread_t *thread_id;
FILE *fp1;

void printWorkDispatch(WorkDispatch work)
{
    printf("xstart = %d, xfinish = %d\n", work.xstart, work.xfinish);
    printf("ystart = %d, yfinish = %d\n", work.ystart, work.yfinish);

}


static WorkDispatch * workDivision(int totalxworkgroups, int totalyworkgroups)
{

    float xworkgroups = (float)scene->dimx/TILEDIMENSION;
    float yworkgroups = (float)scene->dimy/TILEDIMENSION;
    WorkDispatch *threadWorks = malloc(totalxworkgroups*totalyworkgroups*sizeof(WorkDispatch));

    for(int y = 0; y < totalyworkgroups; y++){
        for(int x = 0; x < totalxworkgroups; x++){
            if(x == totalxworkgroups -1 &&  xworkgroups != ceil(xworkgroups)){
                threadWorks[matrixOffset(x, y, totalxworkgroups)].xstart = TILEDIMENSION*(int)xworkgroups;
                threadWorks[matrixOffset(x, y, totalxworkgroups)].xfinish = scene->dimx-1;
                
                if(y == totalyworkgroups -1 &&  yworkgroups != ceil(yworkgroups)){
                    threadWorks[matrixOffset(x, y, totalxworkgroups)].ystart = TILEDIMENSION*(int)yworkgroups;
                    threadWorks[matrixOffset(x, y, totalxworkgroups)].yfinish = scene->dimy-1;
                }
                else{
                    threadWorks[matrixOffset(x, y, totalxworkgroups)].ystart = y*TILEDIMENSION;
                    threadWorks[matrixOffset(x, y, totalxworkgroups)].yfinish = ((y+1)*TILEDIMENSION)-1;   
                }
            } 
            else{                       
                threadWorks[matrixOffset(x, y, totalxworkgroups)].xstart =  x*TILEDIMENSION; 
                threadWorks[matrixOffset(x, y, totalxworkgroups)].xfinish = ((x+1)*TILEDIMENSION)-1; 
                
                if(y == totalyworkgroups -1 &&  yworkgroups != ceil(yworkgroups)){
                    threadWorks[matrixOffset(x, y, totalxworkgroups)].ystart = TILEDIMENSION*(int)yworkgroups;
                    threadWorks[matrixOffset(x, y, totalxworkgroups)].yfinish = scene->dimy-1;  
                }
                else{
                    threadWorks[matrixOffset(x, y, totalxworkgroups)].ystart = y*TILEDIMENSION;
                    threadWorks[matrixOffset(x, y, totalxworkgroups)].yfinish = ((y+1)*TILEDIMENSION)-1;
                }
            }
        }     
     }
    return threadWorks;
}


static void *tileProcesser(void *dummyPtr)
{
    Vector color;
    WorkDispatch ownwork;
    while(remainingjobs > 0){
        //printf("Thread number %ld\n", pthread_self());
        pthread_mutex_lock( &mutex1 );
        if(remainingjobs <= 0){
            pthread_mutex_unlock( &mutex1 );
            break;
        }        
        else{
          //   printf("CPU puts completed = %f\n", 
//                (float)(totaljobs-remainingjobs)/totaljobs*100);
            ownwork = threadWorks[remainingjobs-1];
            remainingjobs--;
        };
        pthread_mutex_unlock( &mutex1 );

        for(int y = ownwork.ystart;y <= ownwork.yfinish; y++){
        
            for(int x = ownwork.xstart; x <= ownwork.xfinish; x++){

                if(scene->antialiasing == ON){
                    color = antialiasColor(x, y);
             
                }
                else if(scene->antialiasing == OFF){ 
                    
                    Ray raythread = {*scene->eye, obtainNormalizedDirection((Float)x, (Float)y)};
                    rayscounter[matrixOffset(x, y, scene->dimx)] += 1;
                    color = whichColorIsIt(&raythread, x, y);    
                }
                image[matrixOffset(x, y, scene->dimx)] = color;            
            }
        }
    }
    return NULL;
}

void rayTracerCPUMultiCore()
{
    int totalxworkgroups;
    int totalyworkgroups;
    int threadnumber = get_nprocs();
    //printf("threadnumber = %d\n", threadnumber);
    image = malloc(scene->dimx*scene->dimy*sizeof(Vector));
    rayscounter = (int*)calloc(scene->dimx*scene->dimy,sizeof(int));
    pthread_t thread_id[threadnumber];
    int i, j;
    int totalrays = 0;    

    totalxworkgroups = (int)ceil((float)scene->dimx/TILEDIMENSION);
    totalyworkgroups = (int)ceil((float)scene->dimy/TILEDIMENSION); 
    remainingjobs = totalxworkgroups*totalyworkgroups;
    threadWorks = workDivision(totalxworkgroups, totalyworkgroups);


    for(i=0; i < threadnumber; i++)
   {
      pthread_create( &thread_id[i], NULL, tileProcesser, NULL );
   }

   for(j=0; j < threadnumber; j++)
   {
      pthread_join( thread_id[j], NULL); 
   }


    FILE *fp1 = fopen("cpuimage.ppm", "wb"); /* b - binary mode */   
    (void) fprintf(fp1, "P6\n%d %d\n255\n", scene->dimx, scene->dimy);
    for(int y = scene->dimy-1; y >= 0; y--){
        for(int x = 0; x < scene->dimx; x++){
            static unsigned char ppmcolor[3];
            ppmcolor[0] = image[matrixOffset(x, y, scene->dimx)].x * 255;  /* red */
            ppmcolor[1] = image[matrixOffset(x, y, scene->dimx)].y * 255;  /* green */
            ppmcolor[2] = image[matrixOffset(x, y, scene->dimx)].z * 255;  /* blue */
            (void) fwrite(ppmcolor, 1, 3, fp1);
            totalrays += rayscounter[matrixOffset(x, y, scene->dimx)];
        }

    }
    (void) fclose(fp1);
    printf("CPU image written, Rays: %d\n", totalrays);
}


void *GPUthread(void *dummyPtr)
{
    GenericShape *gpuPrim;     
    SceneInfo *info = initSceneInfo();
    SceneLights *lights = initSceneLights();
    LinearBVHNode *bvhNodes = scene->bvhNodes; 
    ReturnGPU *infoRet;
    WorkDispatch *ownwork;
     if (scene->acceleration == ON)
        gpuPrim = scene->orderedPrims;  
    else
        gpuPrim = scene->prim;


    //Esta primera parte queda como tal

    // Use this to check the output of each API call
    cl_int status;  
     
    //-----------------------------------------------------
    // STEP 1: Discover and initialize the platforms
    //-----------------------------------------------------
    
    cl_uint numPlatforms = 0;
    cl_platform_id *platforms = NULL;
    
    // Use clGetPlatformIDs() to retrieve the number of 
    // platforms
    status = clGetPlatformIDs(0, NULL, &numPlatforms);
 
    // Allocate enough space for each platform
    platforms =   
        (cl_platform_id*)malloc(
            numPlatforms*sizeof(cl_platform_id));
 
    // Fill in platforms with clGetPlatformIDs()
    status = clGetPlatformIDs(numPlatforms, platforms, 
                NULL);

    //-----------------------------------------------------
    // STEP 2: Discover and initialize the devices
    //----------------------------------------------------- 
    
    cl_uint numDevices = 0;
    cl_device_id *devices = NULL;

    // Use clGetDeviceIDs() to retrieve the number of 
    // devices present
    status = clGetDeviceIDs(
        platforms[0], 
        CL_DEVICE_TYPE_ALL, 
        0, 
        NULL, 
        &numDevices);

    // Allocate enough space for each device
    devices = 
        (cl_device_id*)malloc(
            numDevices*sizeof(cl_device_id));

    // Fill in devices with clGetDeviceIDs()
    status = clGetDeviceIDs(
        platforms[0], 
        CL_DEVICE_TYPE_ALL,        
        numDevices, 
        devices, 
        NULL);

    //-----------------------------------------------------
    // STEP 3: Create a context
    //----------------------------------------------------- 
    
    cl_context context = NULL;

    // Create a context using clCreateContext() and 
    // associate it with the devices
    context = clCreateContext(
        NULL, 
        numDevices, 
        devices, 
        NULL, 
        NULL, 
        &status);

    //-----------------------------------------------------
    // STEP 4: Create a command queue
    //----------------------------------------------------- 
    
    cl_command_queue cmdQueue;

    // Create a command queue using clCreateCommandQueue(),
    // and associate it with the device you want to execute 
    // on
    cmdQueue = clCreateCommandQueue(
        context, 
        devices[0], 
        0, 
        &status);

     //printDeviceInfo(devices[0]); +++++++++++++

    //-----------------------------------------------------
    // STEP 4.5: Configure the work-item structure
    //----------------------------------------------------- 
    

    size_t globalWorkSize[1];   
    size_t workGroupSize[1]; 
    // There are 'elements' work-items 

    cl_int err;
    size_t size;
    err = clGetDeviceInfo(devices[0], CL_DEVICE_MAX_WORK_GROUP_SIZE, sizeof(size_t), &size, NULL);
    if (err==-1) fprintf(stderr, "Getting device max work-group size");
    //printf("\t\tMax Work-group Total Size: %ld\n", size); ++++++++++
    workGroupSize[0] = size;
    
    cl_uint num;
    err = clGetDeviceInfo(devices[0], CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(cl_uint), &num, NULL);
    if (err==-1) fprintf(stderr, "Getting device max compute units");
    //printf("\t\tMax. Compute Units: %d\n", num); +++++++++++
    num = num*6;
    globalWorkSize[0] = num*workGroupSize[0];

    infoRet = malloc(sizeof(ReturnGPU)*globalWorkSize[0]);
    ownwork =  malloc(sizeof(WorkDispatch)*num);
    //-----------------------------------------------------
    // STEP 5: Create device buffers
    //----------------------------------------------------- 

    //Notar cómo es que se genera esto    
  

// This code executes on the OpenCL host

    cl_mem bufPrimitives = clCreateBuffer(
        context, 
        CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR, 
        sizeof(GenericShape)*scene->sizeScene, 
        gpuPrim, 
        &status);

    cl_mem bufSceneInfo = clCreateBuffer(
        context, 
        CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR, 
        sizeof(SceneInfo), 
        info, 
        &status);

    cl_mem bufLights = clCreateBuffer(
        context, 
        CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR, 
        sizeof(SceneLights)*(info->sizeLights+1), 
        lights, 
        &status);
    
    cl_mem bufBVHnodes = clCreateBuffer(
        context, 
        CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR, 
        sizeof(LinearBVHNode)*scene->totalBVHNodes, 
        bvhNodes, 
        &status);

    cl_mem bufReturnInfo = clCreateBuffer(
        context, 
        CL_MEM_WRITE_ONLY | CL_MEM_USE_HOST_PTR,                 
        sizeof(ReturnGPU)*globalWorkSize[0], 
        infoRet, 
        &status);

    cl_mem bufOwnWork = clCreateBuffer(
        context, 
        CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR,                 
        sizeof(WorkDispatch)*num, 
        ownwork, 
        &status);
    
    //-----------------------------------------------------
    // STEP 6: Write host data to device buffers
    //----------------------------------------------------- 
    void* pointer0 = clEnqueueMapBuffer(cmdQueue, bufPrimitives, CL_TRUE, 
                    CL_MAP_READ, sizeof(GenericShape)*scene->sizeScene, 0, 0, NULL, NULL, NULL);
    void* pointer1 = clEnqueueMapBuffer(cmdQueue, bufSceneInfo, CL_TRUE, 
                    CL_MAP_READ, sizeof(SceneInfo), 0, 0, NULL, NULL, NULL);
    void* pointer2 = clEnqueueMapBuffer(cmdQueue, bufLights, CL_TRUE, 
                    CL_MAP_READ, sizeof(SceneLights)*(info->sizeLights+1), 0, 0, NULL, NULL, NULL);
    void* pointer3 = clEnqueueMapBuffer(cmdQueue, bufBVHnodes, CL_TRUE, 
                    CL_MAP_READ, sizeof(LinearBVHNode)*scene->totalBVHNodes, 0, 0, NULL, NULL, NULL);
    
    

    //-----------------------------------------------------
    // STEP 7: Create and compile the program
    //----------------------------------------------------- 


    // Create a program using clCreateProgramWithSource()
    char *programSource = readFile("../src/tracer.cl"); //Ojo agregado por mi
    cl_program program = clCreateProgramWithSource(
        context, 
        1, 
        (const char**)&programSource,                                 
        NULL, 
        &status);

  //  printf("status CreateProgramSource = %d\n", status); +++++++++
    
    // Build (compile) the program for the devices with
    // clBuildProgram()
    status = clBuildProgram(
        program, 
        numDevices, 
        devices, 
        NULL, 
        NULL, 
        NULL);
   
 //   printf("status BuildProgram = %d\n", status); ++++++++++
    if(status != 0) exit(-1);
    //-----------------------------------------------------
    // STEP 8: Create the kernel
    //----------------------------------------------------- 

    cl_kernel kernel = NULL;

    // Use clCreateKernel() to create a kernel from the 
    // vector addition function (named "vecadd")
    kernel = clCreateKernel(program, "apuTracer", &status);

   // printf("status clCreateKernel = %d\n", status);++++++++++++++
    if(status != 0) exit(-1);
   
    

    while(remainingjobs > 0){ 

        pthread_mutex_lock( &mutex1 );
        if(remainingjobs <= num){
            pthread_mutex_unlock( &mutex1 );
            break;
        }        
        else{
         //   printf("Completed %f %% \n", 
         //   (float)(totaljobs-remainingjobs)/totaljobs*100);
            for(int i = 0; i < num; i++){      
                ownwork[i] = threadWorks[remainingjobs-1];                
                remainingjobs--;

            }
        };
        pthread_mutex_unlock( &mutex1 );

        void* pointer4 = clEnqueueMapBuffer(cmdQueue, bufReturnInfo, CL_TRUE, 
                    CL_MAP_WRITE, sizeof(ReturnGPU)*globalWorkSize[0], 0, 0, NULL, NULL, NULL);
        void* pointer5 = clEnqueueMapBuffer(cmdQueue, bufOwnWork, CL_TRUE, 
                    CL_MAP_READ, sizeof(WorkDispatch)*num, 0, 0, NULL, NULL, NULL);

        clFinish(cmdQueue);
        status  = clSetKernelArg(
            kernel, 
            0, 
            sizeof(cl_mem), 
            &bufPrimitives);
    
        status  = clSetKernelArg(
            kernel, 
            1, 
            sizeof(cl_mem), 
            &bufOwnWork);

         status  = clSetKernelArg(
            kernel, 
            2, 
            sizeof(cl_mem), 
            &bufSceneInfo);

         status  = clSetKernelArg(
            kernel, 
            3, 
            sizeof(cl_mem), 
            &bufLights);

        status  = clSetKernelArg(
            kernel, 
            4, 
            sizeof(cl_mem), 
            &bufBVHnodes);

        status = clSetKernelArg(
            kernel, 
            5, 
            sizeof(cl_mem), 
            &bufReturnInfo);
    
        status = clEnqueueNDRangeKernel(
            cmdQueue, 
            kernel, 
            1, 
            NULL, 
            globalWorkSize, 
            workGroupSize, 
            0, 
            NULL, 
            NULL);

        clFinish(cmdQueue);

        
        clEnqueueUnmapMemObject(cmdQueue, bufReturnInfo, pointer4, 0, NULL, NULL);
        clEnqueueUnmapMemObject(cmdQueue, bufOwnWork, pointer5, 0, NULL, NULL);

        clFinish(cmdQueue);

        Vector color;
        for(int i = 0 ;i < globalWorkSize[0]; i++){
            if(infoRet[i].valid == 1){                
                color = infoRet[i].color;                    	
                image[matrixOffset(infoRet[i].x, infoRet[i].y, scene->dimx)] 
                    = color;
                rayscounter[matrixOffset(infoRet[i].x, infoRet[i].y, 
                scene->dimx)] = infoRet[i].rays;
            }         
        }
    }

    clEnqueueUnmapMemObject(cmdQueue, bufPrimitives, pointer0, 0, NULL, NULL);
    clEnqueueUnmapMemObject(cmdQueue, bufSceneInfo, pointer1, 0, NULL, NULL);
    clEnqueueUnmapMemObject(cmdQueue, bufLights, pointer2, 0, NULL, NULL);
    clEnqueueUnmapMemObject(cmdQueue, bufBVHnodes, pointer3, 0, NULL, NULL);
    //-----------------------------------------------------
    // STEP 13: Release OpenCL resources
    //----------------------------------------------------- 
    
    // Free OpenCL resources

    clReleaseKernel(kernel);
    clReleaseProgram(program);
    clReleaseCommandQueue(cmdQueue);
    clReleaseMemObject(bufSceneInfo);
    clReleaseMemObject(bufLights);
    clReleaseMemObject(bufPrimitives);
    clReleaseMemObject(bufBVHnodes);
    clReleaseMemObject(bufOwnWork);
    clReleaseMemObject(bufReturnInfo);
    clReleaseContext(context);

    // Free host resources

    free(info);   
//    free(gpuPrim);
//    free(bvhNodes);
    free(ownwork);
    free(lights);
    free(platforms);
    free(infoRet);
    free(devices);

    return NULL;
}


void rayTracerAPUMultiCore(){

    int totalxworkgroups;
    int totalyworkgroups;
    int threadnumber = get_nprocs();
    //printf("threadnumber = %d\n", threadnumber);
    image = malloc(scene->dimx*scene->dimy*sizeof(Vector));
    rayscounter = (int*)calloc(scene->dimx*scene->dimy,sizeof(int));
    thread_id = malloc(sizeof(pthread_t)*(threadnumber+1));
    int i, j;
    int totalrays = 0;    

    totalxworkgroups = (int)ceil((float)scene->dimx/TILEDIMENSION);
    totalyworkgroups = (int)ceil((float)scene->dimy/TILEDIMENSION); 
    remainingjobs = totalxworkgroups*totalyworkgroups;
    totaljobs = totalxworkgroups*totalyworkgroups;
    threadWorks = workDivision(totalxworkgroups, totalyworkgroups);


    for(i=0; i < threadnumber; i++)
    {
        pthread_create( &thread_id[i], NULL, tileProcesser, NULL );
    }
    
    pthread_create( &thread_id[i], NULL, GPUthread, NULL );

    for(j=0; j <= threadnumber; j++)
    {
        pthread_join( thread_id[j], NULL); 
    }

    fp1 = fopen("apuimage.ppm", "wb"); /* b - binary mode */   
    (void) fprintf(fp1, "P6\n%d %d\n255\n", scene->dimx, scene->dimy);
    for(int y = scene->dimy-1; y >= 0; y--){
        for(int x = 0; x < scene->dimx; x++){
            static unsigned char ppmcolor[3];
            ppmcolor[0] = image[matrixOffset(x, y, scene->dimx)].x * 255;  /* red */
            ppmcolor[1] = image[matrixOffset(x, y, scene->dimx)].y * 255;  /* green */
            ppmcolor[2] = image[matrixOffset(x, y, scene->dimx)].z * 255;  /* blue */
            (void) fwrite(ppmcolor, 1, 3, fp1);
            totalrays += rayscounter[matrixOffset(x, y, scene->dimx)];	

        }

    }
    (void) fclose(fp1);
    printf("APU image written, Rays: %d\n", totalrays);
}




/*void rayTracerCPU(){    
    
     //Adding this for the image ppm
    FILE *fp = fopen("first.ppm", "wb");   
    (void) fprintf(fp, "P6\n%d %d\n255\n", H_SIZE, V_SIZE);
    image = malloc(H_SIZE*V_SIZE*sizeof(Vector));    
    
    Vector color;
    int x, y; 
    for(y = V_SIZE-1;y >= 0; y--){
        
        for(x = 0; x < H_SIZE; x++){

            if(scene->antialiasing->antialias == ON){
                color = antialiasColor(scene->antialiasing->levels, scene->antialiasing->levels-1, x, y);
                // printVector(&color);
            }
            else if(scene->antialiasing->antialias == OFF){ 
                rayscene.direction = obtainNormalizedDirection((Float)x, (Float)y);
                color = whichColorIsIt(&rayscene, scene, scene->levels, scene->transparencies);    
            }
            static unsigned char ppmcolor[3];
            ppmcolor[0] = color.x * 255;  
            ppmcolor[1] = color.y * 255;  
            ppmcolor[2] = color.z * 255;  
            (void) fwrite(ppmcolor, 1, 3, fp);	

            image[matrixOffset(x, y, H_SIZE)] = color;            
        }
    }
    (void) fclose(fp);


    
}*/


