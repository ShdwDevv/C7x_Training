/*
* module name       : c7x_sample4
*
* module descripton : 1D FIR filter using C7x vector types, Streaming Engine and Streaming Address generator
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/

#include "fir_1d_se_sa.h"

#define SE0_PARAM_OFFSET (0)
#define SE1_PARAM_OFFSET (SE0_PARAM_OFFSET + sizeof(__SE_TEMPLATE_v1))
#define SA0_PARAM_OFFSET (SE1_PARAM_OFFSET + sizeof(__SE_TEMPLATE_v1))

using namespace c7x;

void fir_1d_se_sa_init(int16_t *pIn, int16_t *pCoeff, int16_t *pOut, int32_t inputSize, int32_t coeffSize, uint8_t *pBlock)
{
    // Get vector length of short_vec type 
    const int vec_len = element_count_of<short_vec>::value;

    __SE_TEMPLATE_v1 seTemplate;
    __SA_TEMPLATE_v1 saTemplate;

    int32_t outputSize;
    
    //Setup Streaming Engine 0 to fetch input data
    seTemplate = __gen_SE_TEMPLATE_v1();
    
    seTemplate.DIMFMT  = __SE_DIMFMT_3D;
    seTemplate.ELETYPE  = se_eletype<short_vec>::value;
    seTemplate.VECLEN   = se_veclen<short_vec>::value;

    seTemplate.ICNT0 = vec_len;
    seTemplate.ICNT1 = coeffSize;             seTemplate.DIM1 = 1;          //Stride by 1 element
    seTemplate.ICNT2 = inputSize/vec_len;     seTemplate.DIM2 = vec_len;    //Stride by 32 elements

    *((__SE_TEMPLATE_v1 *)((uint8_t *)pBlock + SE0_PARAM_OFFSET)) = seTemplate;

    //Setup Streaming Engine 1 to fetch and duplicate coefficients
    seTemplate = __gen_SE_TEMPLATE_v1();

    seTemplate.DIMFMT    = __SE_DIMFMT_3D;
    seTemplate.ELEDUP    = __SE_ELEDUP_32X;
    seTemplate.VECLEN   = se_veclen<short_vec>::value;
    seTemplate.ELETYPE  = se_eletype<short_vec>::value;

    seTemplate.ICNT0 = coeffSize;
    seTemplate.ICNT1 = inputSize/vec_len;  seTemplate.DIM1  = 0;
    seTemplate.ICNT2 = 1;                     seTemplate.DIM2  = 0;


    *((__SE_TEMPLATE_v1 *)((uint8_t *)pBlock + SE1_PARAM_OFFSET)) = seTemplate;

    //Setup Address generator to store output result
    saTemplate = __gen_SA_TEMPLATE_v1();
    
    saTemplate.DIMFMT    = __SA_DIMFMT_3D;
    saTemplate.VECLEN    = sa_veclen<short_vec>::value;

    outputSize = inputSize - coeffSize + 1;
    saTemplate.ICNT0 = outputSize;
    saTemplate.ICNT1 = 1;  saTemplate.DIM1 = 0;
    saTemplate.ICNT2 = 1;  saTemplate.DIM2 = 0;

    *((__SA_TEMPLATE_v1 *)((uint8_t *)pBlock + SA0_PARAM_OFFSET)) = saTemplate;
}

void fir_1d_se_sa(int16_t *pIn, int16_t *pCoeff, int16_t *pOut, int32_t inputSize, int32_t coeffSize, uint8_t *pBlock)
{
    // Get vector length of short_vec type 
    const int vec_len = element_count_of<short_vec>::value;

    __SE_TEMPLATE_v1 seTemplate;
    __SA_TEMPLATE_v1 saTemplate;
    
    int32_t i, j;
    int32_t outputSize;
    
    /* Read template and open Streaming Engine 0 */
    seTemplate = *((__SE_TEMPLATE_v1 *)((uint8_t *)pBlock + SE0_PARAM_OFFSET));
    __SE0_OPEN(pIn, seTemplate);

    /* Read template and open Streaming Engine 1 */
    seTemplate = *((__SE_TEMPLATE_v1 *)((uint8_t *)pBlock + SE1_PARAM_OFFSET));
    __SE1_OPEN(pCoeff, seTemplate);

    /* Read template and open Address Generator 0 */
    saTemplate = *((__SA_TEMPLATE_v1 *)((uint8_t *)pBlock + SA0_PARAM_OFFSET));
    __SA0_OPEN(saTemplate);
    
    outputSize = inputSize - coeffSize + 1;
    
    /* Loop iterates for OUTPUT_SIZE/vec_len */
    for(j = 0; j < outputSize; j+=vec_len) {
        
        /* Initialize output vector */
        short32 vOut = (short32)(0);
    
        /* Loop iterates for number of coefficients */
        for(i = 0; i < coeffSize; i++) {

            //Read a vector of 32-16b elements from input Array
            short_vec vIn = strm_eng<0, short_vec>::get_adv();

            //Load and duplicate each coefficient 32 times
            short_vec vCoeff = strm_eng<1, short_vec>::get_adv();
    
            /* Multiply input with coefficient and accumulate the result */
            vOut += (vIn * vCoeff);
        }
    
        //Store the result using SA
        __vpred pred = strm_agen<0, short_vec>::get_vpred();
        short_vec * addr = strm_agen<0, short_vec>::get_adv(pOut);
        __vstore_pred(pred, addr, vOut);

    }

    /* Close Streaming Engine and Address Generator */
    __SA0_CLOSE();
    __SE1_CLOSE();
    __SE0_CLOSE();
    
}



