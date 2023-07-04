#pragma once

#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include "Star.h"
#include "CanvasCamera.h"

// Renderer
CanvasCamera* allocateDeviceCanvasCamera();
void sendCanvasCameraToDevice(CanvasCamera* device_canvas_camera, CanvasCamera* host_canvas_camera);
void freeDeviceCanvasCamera(CanvasCamera* device_canvas_camera);

// Stars
Star* allocateDeviceStars(Star* host_stars, int num_stars);
void deviceStarProjection(Star* device_stars, int num_stars, CanvasCamera* device_canvas_camera);
void copyDeviceStarsToHostStars(Star* host_stars, Star* device_stars, int num_stars);
void freeDeviceStars(Star* device_stars);