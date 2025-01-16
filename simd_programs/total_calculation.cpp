#include <iostream>
#include "immintrin.h"
using namespace std;
#define MAX_NUM (2048)
void normal_addition(){
    int sum = 0, iterations = 0;
    for(int val = 1;val <= MAX_NUM;val++){
        sum += val;
        iterations++;
    }
    cout<<"Total : "<<sum<<" Iterations : "<<iterations<<endl;
}
void intrinsic_function(){
    int sum = 0, iterations = 0;
    __m256i eight_step = _mm256_set1_epi32(8);
    __m256i sum_vector = _mm256_set1_epi32(0);
    int values[8] = {1,2,3,4,5,6,7,8};
    __m256i value_vector = _mm256_loadu_si256((__m256i*)values);
    for(int idx = 0;idx < MAX_NUM;idx+=8){
        iterations++;
        sum_vector = _mm256_add_epi32(sum_vector,value_vector);
        value_vector = _mm256_add_epi32(value_vector,eight_step);
    }
    int res[8];
    _mm256_storeu_si256((__m256i*)&res,sum_vector);
    for(auto val : res) sum += val;
    cout<<endl;
    cout<<"Total : "<<sum<<" Iterations : "<<iterations<<endl;
}
int main(){
    normal_addition();
    intrinsic_function();
}