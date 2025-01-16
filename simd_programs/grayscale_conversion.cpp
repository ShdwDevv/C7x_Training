#include<iostream>
#include <xmmintrin.h>
using namespace std;
void print_reg(__m128 reg){
    float res[4];
    _mm_store_ps((float*)&res,reg);
    for(auto val : res) cout<<val<<" ";
    cout<<endl;
}
void normal_function(){
    int n = 16;
    int m = 4;
    int max = 255;
    float input[n] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16},output[n];
    float rconst = 2;
    float gconst = 3;
    float bconst = 4;
    for(int i = 0;i < m;i++){
        float r = (float) input[i * 4];
        float g = (float) input[i * 4 + 1];
        float b = (float) input[i * 4 + 2];
        float y = r * rconst + g * gconst + b*bconst;
        if(y > max) y = max;
        output[i*4] = output[i*4+1] = output[i*4+2] = y;
        output[i*4+3] = input[i*4+3]; 
    }
    cout<<"Normal Function : "<<endl;
    for(int i = 0;i < n;i++){
        cout<<output[i]<<" ";
    }
    cout<<endl;
}
void intrinsic_function(){
    int n = 16;
    int m = 4;
    int max = 255;
    float input[n] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16},output[n];
    float rconst = 2;
    float gconst = 3;
    float bconst = 4;
    __m128 rconst_vec = _mm_set1_ps(rconst);
    __m128 gconst_vec = _mm_set1_ps(gconst);
    __m128 bconst_vec = _mm_set1_ps(bconst);
    __m128 first = _mm_load_ps((float*)&input[0]);
    __m128 second = _mm_load_ps((float*)&input[4]);
    __m128 third = _mm_load_ps((float*)&input[8]);
    __m128 fourth = _mm_load_ps((float*)&input[12]);
    __m128 temp1 = _mm_unpacklo_ps (first, second);
    __m128 temp2 = _mm_unpackhi_ps (first, second);
    __m128 temp3 = _mm_unpacklo_ps (third, fourth);
    __m128 temp4 = _mm_unpackhi_ps (third, fourth);
    __m128 row1 = _mm_shuffle_ps(temp1, temp3, _MM_SHUFFLE(1, 0, 1, 0)); 
    __m128 row2 = _mm_shuffle_ps(temp1, temp3, _MM_SHUFFLE(3, 2, 3, 2)); 
    __m128 row3 = _mm_shuffle_ps(temp2, temp4, _MM_SHUFFLE(1, 0, 1, 0)); 
    __m128 row4 = _mm_shuffle_ps(temp2, temp4, _MM_SHUFFLE(3, 2, 3, 2)); 
    __m128 red = _mm_mul_ps(row1,rconst_vec);
    __m128 green = _mm_mul_ps(row2,gconst_vec);
    __m128 blue = _mm_mul_ps(row3,bconst_vec);
    __m128 res = _mm_add_ps(red,green);
    res = _mm_add_ps(res,blue);
    float temp_res[n/4];
    _mm_storeu_ps((float*)temp_res,res);
    for(int idx = 0;idx < n/4;idx++){
        output[idx * 4] = output[idx * 4 + 1] = output[idx * 4 + 2] = temp_res[idx];
        output[idx * 4 + 3] = input[idx * 4 + 3] ;
    }
    cout<<"Inrinsic Function : "<<endl;
    for(int idx = 0;idx < n;idx++){
        cout<<output[idx]<<" ";
    }
    cout<<endl;
}
int main(){
    normal_function();
    intrinsic_function();
}