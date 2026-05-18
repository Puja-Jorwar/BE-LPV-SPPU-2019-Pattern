#include <iostream>
#include <cuda_runtime.h>

using namespace std;

__global__ void vectorAdd(int *A, int *B, int *C, int n) {

    int i = blockIdx.x * blockDim.x + threadIdx.x;

    if (i < n) {
        C[i] = A[i] + B[i];
    }
}

int main() {

    int n = 5;

    int A[n] = {1, 2, 3, 4, 5};
    int B[n] = {10, 20, 30, 40, 50};
    int C[n];

    int *d_A, *d_B, *d_C;

    cudaMalloc((void**)&d_A, n * sizeof(int));
    cudaMalloc((void**)&d_B, n * sizeof(int));
    cudaMalloc((void**)&d_C, n * sizeof(int));

    cudaMemcpy(d_A, A, n * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, B, n * sizeof(int), cudaMemcpyHostToDevice);

    vectorAdd<<<1, n>>>(d_A, d_B, d_C, n);

    cudaMemcpy(C, d_C, n * sizeof(int), cudaMemcpyDeviceToHost);

    cout << "Vector Addition Result:\n";

    for (int i = 0; i < n; i++) {
        cout << C[i] << " ";
    }

    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);

    return 0;
}