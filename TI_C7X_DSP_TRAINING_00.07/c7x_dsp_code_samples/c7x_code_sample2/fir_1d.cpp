/*
* module name       : c7x_sample2
*
* module descripton : 1D FIR filter using C7x vector types
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/

#include "fir_1d.h"

using namespace c7x;


void fir1D(int16_t *pIn, int16_t *pCoeff, int16_t *pOut, int32_t inputSize, int32_t coeffSize)
{
    int32_t i, j;
    int32_t outputSize;

    outputSize = inputSize - coeffSize + 1;
    
    // Get vector length of short_vec type 
    const int vec_len = element_count_of<short_vec>::value;

    /* Loop iterates for OUTPUT_SIZE/SIMD_WIDTH */
    for(j = 0; j < outputSize; j+=vec_len) 
    {    
        /* Initialize output vector */
        short_vec vOut = (short_vec)(0);
    
        /* Loop iterates for number of coefficients */
        for(i = 0; i < coeffSize; i++) 
        {
            /* Read a vector of 32-16b elements from input Array */
            short_vec vIn = *(short_vec *)(pIn + j + i);

            /* Load and duplicate each coefficient 32 times */
            short_vec vCoeff = (short_vec)(pCoeff[i]);
    
            /* Multiply input with coefficient and accumulate the result */
            vOut += (vIn * vCoeff);
        }    

        /* Store the result */
        *((short_vec *)(pOut + j)) = vOut;
    }

    return;
}




