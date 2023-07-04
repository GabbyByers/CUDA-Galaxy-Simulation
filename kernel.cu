#include "kernel.cuh"

__global__ void gpuStarProjection(Star* stars, int num_stars) {
    unsigned int i = (blockIdx.x * blockDim.x) + threadIdx.x;
    if (i >= num_stars) {
        return;
    }
}

Star* initializeDeviceStars(Star* host_stars, int num_stars) {
    cudaSetDevice(0);

    Star* device_stars = nullptr;
    cudaMalloc((void**)&host_stars, num_stars * sizeof(Star));

    cudaMemcpy(device_stars, host_stars, num_stars * sizeof(Star), cudaMemcpyHostToDevice);

    return device_stars;
}

void deviceStarProjection(Star* host_stars, Star* device_stars, int num_stars) {
    unsigned int NUM_THREADS = 512;
    unsigned int NUM_BLOCKS = (num_stars + NUM_THREADS - 1) / NUM_THREADS;
    gpuStarProjection <<<NUM_BLOCKS, NUM_THREADS>>> (device_stars, num_stars);
    cudaDeviceSynchronize();

    cudaMemcpy(host_stars, device_stars, num_stars * sizeof(Star), cudaMemcpyDeviceToHost);
}

void freeDeviceStars(Star* device_stars) {
    cudaFree(device_stars);
}