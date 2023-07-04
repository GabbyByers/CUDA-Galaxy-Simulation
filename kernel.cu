#include "kernel.cuh"

__global__ void gpuStarProjection(Star* device_stars, int num_stars, CanvasCamera* device_canvas_camera) {
    unsigned int index = (blockIdx.x * blockDim.x) + threadIdx.x;
    if (index >= num_stars) {
        return;
    }

    Star& star = device_stars[index];
    star.projection(device_canvas_camera);
}

// Canvas Camera
CanvasCamera* allocateDeviceCanvasCamera() {
    cudaSetDevice(0); // duplicate
    CanvasCamera* device_canvas_camera = nullptr;
    cudaMalloc((void**)&device_canvas_camera, sizeof(CanvasCamera));
    return device_canvas_camera;
}

void sendCanvasCameraToDevice(CanvasCamera* device_canvas_camera, CanvasCamera* host_canvas_camera) {
    cudaMemcpy(device_canvas_camera, host_canvas_camera, sizeof(CanvasCamera), cudaMemcpyHostToDevice);
}

void freeDeviceCanvasCamera(CanvasCamera* device_canvas_camera) {
    cudaFree(device_canvas_camera);
}

// Stars
Star* allocateDeviceStars(Star* host_stars, int num_stars) {
    cudaSetDevice(0); // duplicate
    Star* device_stars = nullptr;
    cudaMalloc((void**)&host_stars, num_stars * sizeof(Star));
    cudaMemcpy(device_stars, host_stars, num_stars * sizeof(Star), cudaMemcpyHostToDevice);
    return device_stars;
}

void deviceStarProjection(Star* device_stars, int num_stars, CanvasCamera* device_canvas_camera) {
    unsigned int NUM_THREADS = 512;
    unsigned int NUM_BLOCKS = (num_stars + NUM_THREADS - 1) / NUM_THREADS;
    gpuStarProjection <<<NUM_BLOCKS, NUM_THREADS>>> (device_stars, num_stars, device_canvas_camera);
    cudaDeviceSynchronize();
}

void copyDeviceStarsToHostStars(Star* host_stars, Star* device_stars, int num_stars) { // TODO: This should only copy the positions, not th whole gosh diddly-dang star
    cudaMemcpy(host_stars, device_stars, num_stars * sizeof(Star), cudaMemcpyDeviceToHost);
}

void freeDeviceStars(Star* device_stars) {
    cudaFree(device_stars);
}