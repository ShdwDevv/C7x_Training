/*
* module name       : c7x_sample1
*
* module descripton : Addition of two array using C7x vector types
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/

#include "add_arrays.h"

using namespace c7x;

void addArrays(int16_t *pInA, int16_t *pInB, int16_t *pOutC, int32_t arraySize)
{
    int32_t ctr;
    
    // Get simd length of short_vec type
    const int vec_len = element_count_of<short_vec>::value;

    for(ctr = 0; ctr < arraySize; ctr+=vec_len)
    {
        
        //Read a vector of 32-16b elements from input Array A
        short_vec vInA = *(short_vec *)(pInA + ctr);

        //Read a vector of 32-16b elements from input Array A
        short_vec vInB = *(short_vec *)(pInB + ctr);
    
        //Added 32-16b elements in parallel
        // '+' operator is overloaded to pick up the right instruction under the hood
        short_vec vOutC = vInA + vInB;
    
        //Store 32-16b elements to output array C
        *(short_vec *)(pOutC + ctr) = vOutC;
    }
}



