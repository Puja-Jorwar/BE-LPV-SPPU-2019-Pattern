#include <iostream>
#include <cuda_runtime.h>

using namespace std;

#define SIZE 2

__global__ void matrixMul(int A[SIZE][SIZE],
                          int B[SIZE][SIZE],
                          int C[SIZE][SIZE]) {

    int row = threadIdx.y;
    int col = threadIdx.x;

    C[row][col] = 0;

    for (int k = 0; k < SIZE; k++) {
        C[row][col] += A[row][k] * B[k][col];
    }
}

int main() {

    int A[SIZE][SIZE] = {
        {1, 2},
        {3, 4}
    };

    int B[SIZE][SIZE] = {
        {5, 6},
        {7, 8}
    };

    int C[SIZE][SIZE];

    int (*d_A)[SIZE], (*d_B)[SIZE], (*d_C)[SIZE];

    cudaMalloc((void**)&d_A, sizeof(A));
    cudaMalloc((void**)&d_B, sizeof(B));
    cudaMalloc((void**)&d_C, sizeof(C));

    cudaMemcpy(d_A, A, sizeof(A), cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, B, sizeof(B), cudaMemcpyHostToDevice);

    dim3 threads(SIZE, SIZE);

    matrixMul<<<1, threads>>>(d_A, d_B, d_C);

    cudaMemcpy(C, d_C, sizeof(C), cudaMemcpyDeviceToHost);

    cout << "Matrix Multiplication Result:\n";

    for (int i = 0; i < SIZE; i++) {

        for (int j = 0; j < SIZE; j++) {

            cout << C[i][j] << " ";
        }

        cout << endl;
    }

    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);

    return 0;
}