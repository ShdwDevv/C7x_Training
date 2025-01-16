#include <iostream>
#include "immintrin.h"
using namespace std;
#define SIZE (32)
void normal_function(){
    int iteration = 0;
    int input[SIZE];
    for(int idx = 0;idx < SIZE;idx++) input[idx] = idx+1;
    float result[SIZE];
    for(int idx= 0;idx < SIZE;idx++){
        iteration++;
        result[idx] = input[idx] * 0.1;
        cout<<result[idx]<<" ";
    }
    cout<<"\nIteration : "<<iteration<<endl;
}
void intrinsic_function(){
    int iteration = 0;
    float result[SIZE];
    int input[SIZE];
    __m256 float_vector = _mm256_set1_ps(0.1);
    for(int idx = 0;idx < SIZE;idx++) input[idx] = idx+1;
    for(int idx = 0;idx < SIZE;idx+=8){
        iteration++;
        __m256i input_vector = _mm256_loadu_si256((__m256i*)&input[idx]);
        __m256 float_input_vector = _mm256_cvtepi32_ps(input_vector);
        __m256 temp_result = _mm256_mul_ps(float_input_vector,float_vector);
        _mm256_storeu_ps(&result[idx],temp_result);
    }
    for(auto v : result) cout<<v<<" ";
    cout<<"\nIteration : "<<iteration<<endl;
}
int main(){
    normal_function();
    intrinsic_function();
}

