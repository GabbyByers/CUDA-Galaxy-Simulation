#pragma once

#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include "Star.h"

Star* initializeDeviceStars(Star* host_stars, int num_stars);
void deviceStarProjection(Star* host_stars, Star* device_stars, int num_stars);
void freeDeviceStars(Star* device_stars);