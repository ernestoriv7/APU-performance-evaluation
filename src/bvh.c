#include "bvh.h"

int leafNodes;
int totalLeafNodes;
int interiorNodes;
int totalPrimitives;
int orderedprimpos;


typedef struct BVHBuildNode BVHBuildNode;

struct BVHBuildNode{
    // BVHBuildNode Public Methods
    Bbox bounds;
    BVHBuildNode *children[2];
    int splitAxis, firstPrimOffset, nPrimitives;
};



typedef struct BVHPrimitiveInfo {
    int primitiveNumber;
    Bbox bounds;
    Vector centroid;
}BVHPrimitiveInfo;

void printLinearBVHNode(LinearBVHNode *node);


void InitLeaf(int first, int n, Bbox *b, BVHBuildNode *node) {
    node->firstPrimOffset = first;
    node->nPrimitives = n;
    node->bounds = *b;
    node->children[0] = node->children[1] = NULL;
    ++leafNodes;
    ++totalLeafNodes;
    totalPrimitives += n;
}

void InitInterior(int axis, BVHBuildNode *c0, BVHBuildNode *c1, BVHBuildNode *node) {
    node->children[0] = c0;
    node->children[1] = c1;
    node->bounds = unionBoxBox(&c0->bounds, &c1->bounds);
    node->splitAxis = axis;
    node->nPrimitives = 0;
    ++interiorNodes;
}

Vector getCentroid(Bbox *box){

    Vector result1 = multiplyConstantVector(0.5, box->pMin);
    Vector result2 = multiplyConstantVector(0.5, box->pMax);
    return addVector(&result1, &result2);
}


int cmpfunc0 (const void * a, const void * b) {
    BVHPrimitiveInfo i = *(BVHPrimitiveInfo*)a;
    BVHPrimitiveInfo j = *(BVHPrimitiveInfo*)b;
    return ( i.centroid.x - j.centroid.x );
}

int cmpfunc1 (const void * a, const void * b) {
    BVHPrimitiveInfo i = *(BVHPrimitiveInfo*)a;
    BVHPrimitiveInfo j = *(BVHPrimitiveInfo*)b;
    return ( i.centroid.y - j.centroid.y );
}

int cmpfunc2 (const void * a, const void * b) {
    BVHPrimitiveInfo i = *(BVHPrimitiveInfo*)a;
    BVHPrimitiveInfo j = *(BVHPrimitiveInfo*)b;
    return ( i.centroid.z - j.centroid.z );
}


int flattenBVHTree(BVHBuildNode *node, int *offset, LinearBVHNode *nodes) {
    LinearBVHNode *linearNode = &nodes[*offset];
    linearNode->bounds = node->bounds;
    int myOffset = (*offset)++;
    if (node->nPrimitives > 0) {
        linearNode->primitivesOffset = node->firstPrimOffset;
        linearNode->nPrimitives = node->nPrimitives;
    } else {
        // Create interior flattened BVH node
        linearNode->axis = node->splitAxis;
        linearNode->nPrimitives = 0;
        flattenBVHTree(node->children[0], offset, nodes);
        linearNode->secondChildOffset = flattenBVHTree(node->children[1], 
                                        offset, nodes);
    }
    return myOffset;
}


BVHBuildNode *recursiveBuild(BVHPrimitiveInfo *primitiveInfo, 
                            int start, int end, int *totalNodes,
                            GenericShape *orderedPrims,  
                            GenericShape *primitives) 
{

    BVHBuildNode *node = malloc(sizeof(BVHBuildNode));
    (*totalNodes)++;
    // Compute bounds of all primitives in BVH node
    Bbox bounds = primitiveInfo[start].bounds;
    for (int i = start; i < end; ++i)
        bounds = unionBoxBox(&bounds, &primitiveInfo[i].bounds);
    int nPrimitives = end - start;
    if (nPrimitives == 1) {
        // Create leaf _BVHBuildNode_
        int firstPrimOffset = orderedprimpos;
        for (int i = start; i < end; ++i) {
            int primNum = primitiveInfo[i].primitiveNumber;
            orderedPrims[orderedprimpos] = primitives[primNum];
            orderedprimpos++;
        }
        InitLeaf(firstPrimOffset, nPrimitives, &bounds, node);
        return node;
    } else {
        // Compute bound of primitive centroids, choose split dimension _dim_
        Bbox centroidBounds;
        centroidBounds = primitiveInfo[start].bounds;

        for (int i = start; i < end; ++i)
            centroidBounds = unionBoxPoint(&centroidBounds, &primitiveInfo[i].centroid);
        int dim = maximumExtendBox(&centroidBounds);

        // Partition primitives into two sets and build children
        int mid = (start + end) / 2;

        int checkdimcondition = 0;

        switch(dim){
            case 0:
                if(centroidBounds.pMax.x == centroidBounds.pMin.x)
                    checkdimcondition = 1;
                break;
            case 1:
                if(centroidBounds.pMax.y == centroidBounds.pMin.y)
                    checkdimcondition = 1;
                break;
            case 2:
                if(centroidBounds.pMax.z == centroidBounds.pMin.z)
                    checkdimcondition = 1;
                break;
        }
        
        if (checkdimcondition) {
            // Create leaf _BVHBuildNode_
            int firstPrimOffset = orderedprimpos;
            for (int i = start; i < end; ++i) {
                int primNum = primitiveInfo[i].primitiveNumber;
                orderedPrims[orderedprimpos] = primitives[primNum];
                orderedprimpos++;
            }
            InitLeaf(firstPrimOffset, nPrimitives, &bounds, node);
            return node;
        } else {
            // Partition primitives based on _splitMethod_
                // Partition primitives through node's midpoint
                
           //Split equal counts
                // Partition primitives into equally-sized subsets
            mid = (start + end) / 2;
            switch(dim){
            case 0:
                 qsort(&primitiveInfo[start], nPrimitives, 
                  sizeof(BVHPrimitiveInfo), cmpfunc0);
                break;
            case 1:
                 qsort(&primitiveInfo[start], nPrimitives, 
                  sizeof(BVHPrimitiveInfo), cmpfunc1);
                break;
            case 2:
                 qsort(&primitiveInfo[start], nPrimitives, 
                  sizeof(BVHPrimitiveInfo), cmpfunc2);
                break;
            }
      
                InitInterior(dim,
                           recursiveBuild(primitiveInfo, start, mid,
                                          totalNodes, orderedPrims, primitives),
                           recursiveBuild(primitiveInfo, mid, end,
                                          totalNodes, orderedPrims,primitives), node);
        }
    return node;
    }
}


void BVHAccel() 
{
   
    int primitivesSize = scene->sizeScene;    
    if (primitivesSize == 0) return;
    // Build BVH from _primitives_

    // Initialize _primitiveInfo_ array for primitives
    BVHPrimitiveInfo *primitiveInfo = malloc(sizeof(BVHPrimitiveInfo)*
                                             primitivesSize); 
    for (int i = 0; i < primitivesSize; ++i){  
        Bbox bound = getBoundingBox(scene->prim[i]);
        primitiveInfo[i] = (BVHPrimitiveInfo){i, bound, getCentroid(&bound)};
    }

    // Build BVH tree for primitives using _primitiveInfo_
    int totalNodes = 0;
    GenericShape *orderedPrims= malloc(sizeof(GenericShape)*primitivesSize);
    orderedprimpos = 0;

    BVHBuildNode *root = recursiveBuild(primitiveInfo, 0, primitivesSize, 
                         &totalNodes, orderedPrims, scene->prim);

    LinearBVHNode *nodes = malloc(sizeof(LinearBVHNode)*totalNodes);
    scene->totalBVHNodes = totalNodes;
    int offset = 0;
    flattenBVHTree(root, &offset, nodes);

    
    scene->orderedPrims = orderedPrims;
    scene->bvhNodes = nodes;
 //   freeList(scene->polygons);
  /*  for(int i=0; i<totalNodes; i++)
        printLinearBVHNode(&nodes[i]);

     for(int i=0; i<primitivesSize; i++){
        printf("***********Primitive %d***********", i);        
        printfGenericShape(orderedPrims[i]);
        
    }*/
}



void printLinearBVHNode(LinearBVHNode *node)
{
    puts("");
    printf("Bounds pMax = %lf, %lf, %lf\n", node->bounds.pMax.x, 
            node->bounds.pMax.y, node->bounds.pMax.z);
    printf("Bounds pMin = %lf, %lf, %lf\n", node->bounds.pMin.x, 
            node->bounds.pMin.y, node->bounds.pMin.z);    
    printf("primitivesOffset = %d\n", node->primitivesOffset);
    printf("secondChildOffset = %d\n", node->secondChildOffset);
    printf("nPrimitives = %d\n", node->nPrimitives);
    printf("axis = %d\n", node->axis);
    printf("pad = %d\n", node->pad[0]);
}

/*void BVHBuildNode(BVHBuildNode *node)
{
    puts("");
    printf("Bounds pMax = %lf, %lf, %lf\n", node->bounds.pMax.x, 
            node->bounds.pMax.y, node->bounds.pMax.z);
    printf("Bounds pMin = %lf, %lf, %lf\n", node->bounds.pMin.x, 
            node->bounds.pMin.y, node->bounds.pMin.z);    
    printf("primitivesOffset = %d\n", node->primitivesOffset);
    printf("secondChildOffset = %d\n", node->secondChildOffset);
    printf("nPrimitives = %d\n", node->nPrimitives);
    printf("axis = %d\n", node->axis);
    printf("pad = %d\n", node->pad[0]);
}
*/

/*struct BVHBuildNode{
    // BVHBuildNode Public Methods
    Bbox bounds;
    BVHBuildNode *children[2];
    int splitAxis, firstPrimOffset, nPrimitives;
};*/

/*

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

*/
