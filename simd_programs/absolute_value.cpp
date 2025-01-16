#include<iostream>
#include "immintrin.h"
#include<ctime>
#include<bits/stdc++.h>
using namespace std;
void print_reg(__m256i reg){
    int res[8];
    _mm256_storeu_si256((__m256i*)&res,reg);
    for(auto val : res) cout<<val<<" ";
    cout<<endl;
}
void assign_random_values(vector<int> &vec){
    for(int &v : vec){
        v = rand() % 21 - 10;
    }
}
void normal_function(vector<int> &input,vector<int> &result,int n){
    int iterations = 0;
    for(int idx = 0;idx < n;idx++){
        if(input[idx] < 0) result[idx] = -1 * input[idx];
        else result[idx] = input[idx];
        iterations++;
    }    
    cout<<"Iterations for Normal Code : "<<iterations<<endl;
}
void print_vector(vector<int> &vect){
    for(int n : vect) cout<<n<<" ";
    cout<<endl;
}
void intrinsic_function(vector<int> &input,vector<int> &result,int n){
    int iterations = 0;
    __m256i zero =  _mm256_setzero_si256();
    __m256i minus_one = _mm256_set1_epi32(-1);
    __m256i plus_one = _mm256_set1_epi32(1);
    for(int idx = 0;idx+8 <= n;idx+=8){
        __m256i temp = _mm256_loadu_si256((__m256i*)&input[idx]);
        __m256i pattern = _mm256_cmpgt_epi32(temp,zero);
        __m256i negative_vector = _mm256_mullo_epi32(temp,minus_one);
        __m256i finalized = _mm256_blendv_epi8(negative_vector,temp,pattern);
        _mm256_storeu_si256((__m256i*)&result[idx],finalized);
        iterations++;
    }
    // For remaining values
    int rem = n - (n % 8);
    for(int idx = rem;idx < n;idx++){
        if(input[idx] < 0) result[idx] = -1 * input[idx];
        else result[idx] = input[idx];
        iterations++;
    }      
    cout<<"Iterations for Intrinsic Code : "<<iterations<<endl;
}
void is_both_are_same(vector<int> &vec1,vector<int> &vec2,int n){
    for(int idx = 0;idx < n;idx++){
        if(vec1[idx]!=vec2[idx]){
            cout<<"Both are not same at idx "<<idx<<endl;
            return;
        }
    }
    cout<<"Both are same"<<endl;
}
int main(){
    int n = 55;
    vector<int> input(n,0),result(n,0),result2(n,0);
    assign_random_values(input);
    print_vector(input);
    normal_function(input,result,n);
    print_vector(result);
    intrinsic_function(input,result2,n);
    print_vector(result2);
    is_both_are_same(result,result2,n);
}