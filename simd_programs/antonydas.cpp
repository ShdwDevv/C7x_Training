#include<immintrin.h>
#include<iostream>

int main(){
    __m256i a = _mm256_set_epi32(1,2,3,4,5,6,7,8);
    __m256i b = _mm256_set1_epi32(10);
    __m256i c = _mm256_mul_epi32(a,b);
    __m256i d = _mm256_mullo_epi32(a,b);
    int mullo[8],mull[8];
    _mm256_storeu_si256((__m256i*)mull,c);
    _mm256_storeu_si256((__m256i*)mullo,d);
    
    std::cout<<"Mull";
    for(int i=0; i<8; i++){
        std::cout<<mull[i]<<", ";
    }
    std::cout<<"\n";
    

    std::cout<<"Mullo";
    for(int i=0; i<8; i++){
        std::cout<<mullo[i]<<", ";
    }
}