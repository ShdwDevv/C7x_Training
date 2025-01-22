#include "c7x.h" 


void addArrays(int16_t *pInA, int16_t *pInB, int16_t *pOutC, int32_t arraySize)
{
    int32_t ctr;
    
    for(ctr = 0; ctr < arraySize; ctr+=32)
    {
        //Read a vector of 32-16b elements from input Array A
        short32 vInA = *(short32_ptr)(pInA + ctr);
    
        //Read a vector of 32-16b elements from input Array A
        short32 vInB = *(short32_ptr)(pInB + ctr);
    
        //Added 32-16b elements in parallel
        // '+' operator is overloaded to pick up the right instruction under the hood
        short32 vOutC = vInA + vInB;
    
        //Store 32-16b elements to output array C
        *(short32_ptr)(pOutC + ctr) = vOutC;
    }
}

//ADD_ARRAY_
