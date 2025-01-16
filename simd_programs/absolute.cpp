/*
PSEUDO CODE
1.Load value from array a,b to vector
2.Initailize Array C to stor a result
3.Create a Mask using cmpgt() function
4.Do subtraction in both ways (a-b and b-a)
5.Blender the ouptup which we need with the help of Pattern/Mask
6.Store the result in C array
 */

#include<iostream>
#include "immintrin.h"
using namespace std;
void print(__m256i vector,const char *name,int count){
    int temp[8];
    _mm256_storeu_si256((__m256i*)temp,vector);
    printf("%s\n",name);
    for(int idx = 0;idx < count;idx++){
        cout<<temp[idx]<<" ";
    }
    cout<<endl;
}
int main(){
    int a[8] = {10,32,11,44,2,44,22,98};
    int b[8] = {3,35,8,57,9,22,42,100};
    int c[8];
    __m256i va = _mm256_loadu_si256((__m256i*)a);
    __m256i vb = _mm256_loadu_si256((__m256i*)b);
    __m256i pattern = _mm256_cmpgt_epi32 (va,vb);
    print(pattern,"Pattern",8);
    __m256i first_great = _mm256_sub_epi32(va,vb);
    print(first_great,"A is Greater",8);
    __m256i second_great = _mm256_sub_epi32(vb,va);
    print(second_great,"B is Greater",8);
    __m256i vfinal =  _mm256_blendv_epi8(second_great,first_great,pattern);
    print(vfinal,"Final Output : ",8);
    _mm256_storeu_si256((__m256i*)c,vfinal);
}