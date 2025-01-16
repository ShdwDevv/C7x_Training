/*
PSEUDO CODE
1.Load value from array a,b to vector
2.Initailize Array C to stor a result
3.Add 2 vectors using add function
4.Store the result in C array
 */
#include <stdio.h>
#include "immintrin.h"
int main(){
    int a[8] = {1,2,3,4,5,6,7,8};
    int b[8] = {9,10,11,12,13,14,15,16};
    int c[8];
    __m256i va = _mm256_loadu_si256((__m256i*)a); 
    __m256i vb = _mm256_loadu_si256((__m256i*)b);
    __m256i vc = _mm256_add_epi32(va,vb);
    _mm256_storeu_si256((__m256i*)c,vc);
    printf("%d %d %d",c[0],c[1],c[2]);
    printf("\n");
    return 0;
}