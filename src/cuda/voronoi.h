#ifndef __VORONOI_H__
#define __VORONOI_H__

#include <thrust/host_vector.h>
#include <thrust/device_vector.h>

#include <cuda.h>


class Voronoi
{

    public: 
    Voronoi() {}; 
    ~Voronoi() {}; 


    template <typename T>
        void print(int m, int n, const thrust::device_vector<T>& d_data);

    void vector_to_pgm(thrust::host_vector<int> &t, int m, int n,char *out);
    void generate_random_sites(thrust::host_vector<int> &t, int Nb, int m, int n); 
    void jfa(thrust::device_vector<int>& in,thrust::device_vector<int>& out, unsigned int k, int m, int n);
    int main(); 


    void timer_start(); 
    float timer_stop_and_display(); 


    private: 
    cudaEvent_t start;
    cudaEvent_t end;
}; 


#endif 
