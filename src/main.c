#include "cputracer.h"
#include "opencltracer.h"
#include "sceneparser.h"
#include "bvh.h"


bool isNumber(char number[])
{
    int i = 0;

    //checking for negative numbers
    if (number[0] == '-')
        i = 1;
    for (; number[i] != 0; i++)
    {
        //if (number[i] > '9' || number[i] < '0')
        if (!isdigit(number[i]))
            return false;
    }
    return true;
}


int main(int argc, char **argv){

    if(argc < 2){
        fprintf(stderr, "Use: %s [Scene File Name]\n", argv[0]);    
        return 0;
    }

    if( access( argv[1], F_OK ) == -1 ) {
        fprintf(stderr, "The specified file does not exists\n");
        return 0;
    } 
    
   // printf("This system has %d processors configured and "
   //     "%d processors available.\n",
   //     get_nprocs_conf(), get_nprocs());

    scene = parserScene(argv[1]);

    if(scene->acceleration == ON)
        BVHAccel();
    else
        scene->totalBVHNodes = 0;
    
    background = (Vector){.x = 0.5, .y= 0.5, .z= 0.5}; //This must be changed
    if(scene->architecture == CPU){
    
       // rayTracerCPU();
        rayTracerCPUMultiCore();
    } else if(scene->architecture == GPU){
    
       rayTracerGPU(); 

    } else if(scene->architecture == APU){
    
       rayTracerAPUMultiCore(); 

    } else  fprintf(stderr, "Check your coding error\n");  

	
}
	
