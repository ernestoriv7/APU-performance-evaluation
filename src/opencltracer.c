#include"opencltracer.h"

//agregado para la parte de opencl



SceneInfo *initSceneInfo()
{
    SceneInfo *info = malloc(sizeof(SceneInfo));
    info->sizeLights = size(scene->lights); 
    info->levels = scene->levels;
    info->transparencies = scene->transparencies;
    info->antialiasing = scene->antialiasing;
    info->acceleration = scene->acceleration;
    info->sizeScene = scene->sizeScene;
    info->dimx = scene->dimx;
    info->dimy = scene->dimy;
    info->eye = *scene->eye;
    return info;
}

SceneLights *initSceneLights()
{
    int sizel = size(scene->lights);
    SceneLights *lights = malloc(sizeof(SceneLights)*(sizel+1));
    lights[0].par = *scene->ambientLight->color;
    lights[0].val = scene->ambientLight->value;
    for(int i = 1; i <= sizel; i ++){
        ElementNode *currentLight = getAt(&scene->lights,i-1);
        lights[i].par = *currentLight->data->position; 
        lights[i].val = currentLight->data->Ip; 
    }  
    return lights;
}
//Reduce the ammount of data given to the GPU

// Variables that are going to be used for several
//int workgroupsize;
size_t numWorkGroups;
cl_int status;
cl_mem bufInputObjects;
cl_command_queue cmdQueue;
cl_mem dResult;
cl_kernel kernel;
size_t indexSpaceSize[1]; 
size_t workGroupSize;


void printDeviceInfo(cl_device_id device){

    cl_char string[10240] = {0};
    
    cl_int err;
    err = clGetDeviceInfo(device, CL_DEVICE_NAME, sizeof(string), &string, NULL);
    if (err==-1) fprintf(stderr, "Getting device name");
    printf("\t\tName: %s\n", string);

// Get device OpenCL version
    err = clGetDeviceInfo(device, CL_DEVICE_OPENCL_C_VERSION, sizeof(string), &string, NULL);
    if (err==-1) fprintf(stderr, "Getting device OpenCL C version");
    printf("\t\tVersion: %s\n", string);
    
    cl_uint num;
    err = clGetDeviceInfo(device, CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(cl_uint), &num, NULL);
     if (err==-1) fprintf(stderr, "Getting device max compute units");
     printf("\t\tMax. Compute Units: %d\n", num);

     cl_ulong mem_size;
     err = clGetDeviceInfo(device, CL_DEVICE_LOCAL_MEM_SIZE, sizeof(cl_ulong), &mem_size, NULL);
     if (err==-1) fprintf(stderr, "Getting device local memory size");
     printf("\t\tLocal Memory Size: %lu KB\n", mem_size/1024);

    err = clGetDeviceInfo(device, CL_DEVICE_GLOBAL_MEM_SIZE, sizeof(cl_ulong), &mem_size, NULL);
    if (err==-1) fprintf(stderr, "Getting device global memory size");
    printf("\t\tGlobal Memory Size: %lu MB\n", mem_size/(1024*1024));

    // Get maximum buffer alloc. size
    err = clGetDeviceInfo(device, CL_DEVICE_MAX_MEM_ALLOC_SIZE, sizeof(cl_ulong), &mem_size, NULL);
    if (err==-1) fprintf(stderr, "Getting device max allocation size");
    printf("\t\tMax Alloc Size: %lu MB\n", mem_size/(1024*1024));
     
    size_t size;
    err = clGetDeviceInfo(device, CL_DEVICE_MAX_WORK_GROUP_SIZE, sizeof(size_t), &size, NULL);
    if (err==-1) fprintf(stderr, "Getting device max work-group size");
    printf("\t\tMax Work-group Total Size: %ld\n", size);
    workGroupSize = size;

    err = clGetDeviceInfo(device, CL_DEVICE_GLOBAL_MEM_CACHELINE_SIZE, sizeof(cl_uint), &num, NULL);
    if (err==-1) fprintf(stderr, "Getting device max compute units");
    printf("\t\tCache Line Size: %d\n", num);
    
     // Find the maximum dimensions of the work-groups
     err = clGetDeviceInfo(device, CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS, sizeof(cl_uint), &num, NULL);
     if (err==-1) fprintf(stderr, "Getting device max work-item dims");
            // Get the max. dimensions of the work-groups
     size_t dims[num];
     err = clGetDeviceInfo(device, CL_DEVICE_MAX_WORK_ITEM_SIZES, sizeof(dims), &dims, NULL);
     if (err==-1) fprintf(stderr, "Getting device max work-item sizes");
     printf("\t\tMax Work-group Dims: ( ");
     for (size_t k = 0; k < num; k++)
     {
          printf("%ld ", dims[k]);
     }
     printf(")\n");

     printf("\t-------------------------\n");
    
}



void rayTracerGPU()
{
    GenericShape *gpuPrim;
       
    SceneInfo *info = initSceneInfo();
    SceneLights *lights = initSceneLights();
    LinearBVHNode *bvhNodes;
    ReturnGPU *infoRet = malloc(sizeof(ReturnGPU)*(scene->dimx)*
                                (scene->dimy));
    image = malloc((scene->dimx)*(scene->dimy)*sizeof(Vector));
    rayscounter = (int*)calloc(scene->dimx*scene->dimy,sizeof(int));
    bvhNodes = scene->bvhNodes;
    int totalrays = 0;
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

    // printDeviceInfo(devices[0]); //+++++++++++++++++
    //-----------------------------------------------------
    // STEP 5: Create device buffers
    //----------------------------------------------------- 

    //Notar cómo es que se genera esto    
  

// This code executes on the OpenCL host

    cl_mem bufPrimitives = clCreateBuffer(
        context, 
        CL_MEM_READ_ONLY, 
        sizeof(GenericShape)*scene->sizeScene, 
        NULL, 
        &status);

    cl_mem bufSceneInfo = clCreateBuffer(
        context, 
        CL_MEM_READ_ONLY, 
        sizeof(SceneInfo), 
        NULL, 
        &status);

    cl_mem bufLights = clCreateBuffer(
        context, 
        CL_MEM_READ_ONLY, 
        sizeof(SceneLights)*(info->sizeLights+1), 
        NULL, 
        &status);
    
    cl_mem bufBVHnodes = clCreateBuffer(
        context, 
        CL_MEM_READ_ONLY, 
        sizeof(LinearBVHNode)*scene->totalBVHNodes, 
        NULL, 
        &status);

    cl_mem bufReturnInfo = clCreateBuffer(
        context, 
        CL_MEM_WRITE_ONLY ,                 
        sizeof(ReturnGPU)*(scene->dimx)*(scene->dimy), 
        NULL, 
        &status);

    
    //-----------------------------------------------------
    // STEP 6: Write host data to device buffers
    //----------------------------------------------------- 
    
    status = clEnqueueWriteBuffer(
        cmdQueue, 
        bufPrimitives, 
        CL_FALSE, 
        0, 
        sizeof(GenericShape)*scene->sizeScene,                         
        gpuPrim, 
        0, 
        NULL, 
        NULL);

    status = clEnqueueWriteBuffer(
        cmdQueue, 
        bufSceneInfo, 
        CL_FALSE, 
        0, 
        sizeof(SceneInfo),                         
        info, 
        0, 
        NULL, 
        NULL);

     status = clEnqueueWriteBuffer(
        cmdQueue, 
        bufLights, 
        CL_FALSE, 
        0, 
        sizeof(SceneLights)*(info->sizeLights+1),                         
        lights, 
        0, 
        NULL, 
        NULL);

    status = clEnqueueWriteBuffer(
        cmdQueue, 
        bufBVHnodes, 
        CL_FALSE, 
        0, 
        sizeof(LinearBVHNode)*scene->totalBVHNodes,                         
        bvhNodes, 
        0, 
        NULL, 
        NULL);
    
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

   // printf("status CreateProgramSource = %d\n", status);//++++++++++++++++
    
    // Build (compile) the program for the devices with
    // clBuildProgram()
    status = clBuildProgram(
        program, 
        numDevices, 
        devices, 
        NULL, 
        NULL, 
        NULL);
   
   // printf("status BuildProgram = %d\n", status);//+++++++++++++++++
    if(status != 0) exit(-1);
    //-----------------------------------------------------
    // STEP 8: Create the kernel
    //----------------------------------------------------- 

    cl_kernel kernel = NULL;

    // Use clCreateKernel() to create a kernel from the 
    // vector addition function (named "vecadd")
    kernel = clCreateKernel(program, "colDetection", &status);

   // printf("status clCreateKernel = %d\n", status);//+++++++++++++++
    if(status != 0) exit(-1);
   
    //-----------------------------------------------------
    // STEP 9: Set the kernel arguments
    //----------------------------------------------------- 
    
    // Associate the input and output buffers with the 
    // kernel 
    // using clSetKernelArg()

    status  = clSetKernelArg(
        kernel, 
        0, 
        sizeof(cl_mem), 
        &bufPrimitives);
    
     status  = clSetKernelArg(
        kernel, 
        1, 
        sizeof(cl_mem), 
        &bufSceneInfo);

     status  = clSetKernelArg(
        kernel, 
        2, 
        sizeof(cl_mem), 
        &bufLights);

    status  = clSetKernelArg(
        kernel, 
        3, 
        sizeof(cl_mem), 
        &bufBVHnodes);

    status = clSetKernelArg(
        kernel, 
        4, 
        sizeof(cl_mem), 
        &bufReturnInfo);

    //-----------------------------------------------------
    // STEP 10: Configure the work-item structure
    //----------------------------------------------------- 
    
    // Define an index space (global work size) of work 
    // items for 
    // execution. A workgroup size (local work size) is not 
    // required, 
    // but can be used.
    size_t globalWorkSize[1];   
    size_t workGroupSize[1]; 
    // There are 'elements' work-items 
    globalWorkSize[0] = scene->dimx*scene->dimy;
    workGroupSize[0] = 128;
    //-----------------------------------------------------
    // STEP 11: Enqueue the kernel for execution
    //----------------------------------------------------- 
    
    // Execute the kernel by using 
    // clEnqueueNDRangeKernel().
    // 'globalWorkSize' is the 1D dimension of the 
    // work-items

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
    //-----------------------------------------------------
    // STEP 12: Read the output buffer back to the host
    //----------------------------------------------------- 
    
    // Use clEnqueueReadBuffer() to read the OpenCL output  

    clEnqueueReadBuffer(
        cmdQueue, 
        bufReturnInfo, 
        CL_TRUE, 
        0, 
        sizeof(ReturnGPU)*(scene->dimx)*(scene->dimy), 
        infoRet, 
        0, 
        NULL, 
        NULL);
   

    Vector color;
 //Basicamente lo mismo que la funcion which color is it
    //Eso implica que debo cambar recover intersection c
    for(int i = 0 ;i < (scene->dimx)*(scene->dimy); i++){
        
            color = infoRet[i].color;        
            	
            image[matrixOffset(infoRet[i].x, infoRet[i].y, scene->dimx)] 
                = color;
            totalrays += infoRet[i].rays;
    }

    FILE *fp = fopen("gpuimage.ppm", "wb");
    (void) fprintf(fp, "P6\n%d %d\n255\n", scene->dimx, scene->dimy);
    for(int y = scene->dimy-1; y >= 0; y--){
        for(int x = 0; x < scene->dimx; x++){
            static unsigned char ppmcolor[3];
            ppmcolor[0] = image[matrixOffset(x, y, scene->dimx)].x * 255;  /* red */
            ppmcolor[1] = image[matrixOffset(x, y, scene->dimx)].y * 255;  /* green */
            ppmcolor[2] = image[matrixOffset(x, y, scene->dimx)].z * 255;  /* blue */
            (void) fwrite(ppmcolor, 1, 3, fp);	

        }

    }
    (void) fclose(fp);
    printf("GPU image written, Rays: %d\n", totalrays);

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
    clReleaseMemObject(bufReturnInfo);
    clReleaseContext(context);

    // Free host resources

    free(info);
   // free(gpuPrim);
   // free(bvhNodes);
    free(lights);
    free(infoRet);
    free(platforms);
    free(devices);
}



