/*
* module name       : c7x_sample5
*
* module descripton : 1D FIR filter using VFIR instruction
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
*
* ALL RIGHTS RESERVED
*/

#include "fir_1d_vfir.h"

#define SE0_PARAM_OFFSET (0)
#define SA0_PARAM_OFFSET (SE0_PARAM_OFFSET + sizeof(__SE_TEMPLATE_v1))

using namespace c7x;

void fir_1d_vfir_init(int16_t *pIn, int16_t *pCoeff, int16_t *pOut, int32_t inputSize, int32_t coeffSize, uint8_t *pBlock)
{

    __SE_TEMPLATE_v1 seTemplate;
    __SA_TEMPLATE_v1 saTemplate;

    int32_t outputSize;
    
    //Setup Streaming Engine 0 to fetch input data
    seTemplate = __gen_SE_TEMPLATE_v1();
    
    seTemplate.DIMFMT  = __SE_DIMFMT_3D;
    seTemplate.ELETYPE   = se_eletype<short_vec>::value;
    seTemplate.VECLEN    = se_veclen<short_vec>::value;
    
    seTemplate.ICNT0 = inputSize;
    seTemplate.ICNT1 = 1;  seTemplate.DIM1 = 0;
    seTemplate.ICNT2 = 1;  seTemplate.DIM2 = 0;

    *((__SE_TEMPLATE_v1 *)((uint8_t *)pBlock + SE0_PARAM_OFFSET)) = seTemplate;

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

void fir_1d_vfir(int16_t *pIn, int16_t *pCoeff, int16_t *pOut, int32_t inputSize, int32_t coeffSize, uint8_t *pBlock)
{
    __SE_TEMPLATE_v1 seTemplate;
    __SA_TEMPLATE_v1 saTemplate;
    
    int32_t j;
    int32_t outputSize;

    // Get vector length of short_vec type 
    const int vec_len = element_count_of<short_vec>::value;
    
    /* Read template and open Streaming Engine 0 */
    seTemplate = *((__SE_TEMPLATE_v1 *)((uint8_t *)pBlock + SE0_PARAM_OFFSET));
    __SE0_OPEN(pIn, seTemplate);
    __SE1_OPEN(pIn + vec_len, seTemplate);

    /* Read template and open Address Generator 0 */
    saTemplate = *((__SA_TEMPLATE_v1 *)((uint8_t *)pBlock + SA0_PARAM_OFFSET));
    __SA0_OPEN(saTemplate);

    /* Read 4-16b coefficients as 1-64b value and load duplicate to fill vCoeff vector */
    ulong8 vCoeff = __vload_dup((ulong *)pCoeff);

    outputSize = inputSize - coeffSize + 1;
    
    /* Loop iterates for OUTPUT_SIZE/vec_len */
    for(j = 0; j < outputSize; j+=vec_len) {
    
        int16 vOutLo, vOutHi;
        short_vec vOut;
    
        /* USE VFIR4HW to compute 1D FIR of 4 tap filter. */
        __vfir4hw_vww(__as_short32(vCoeff), __SE_REG_PAIR_0_ADV, vOutLo, vOutHi);
    
        /* Pack and Saturate 32-bit results to 16-bits */
        vOut = __pack_sat(vOutHi, vOutLo);
    
        //Store the result using SA
        __vpred pred = strm_agen<0, short_vec>::get_vpred();
        short_vec * addr = strm_agen<0, short_vec>::get_adv(pOut);
        __vstore_pred(pred, addr, __deal_stride2(vOut));
    }

    /* Close Streaming Engine and Address Generator */
    __SA0_CLOSE();
    __SE1_CLOSE();
    __SE0_CLOSE();
    
}



