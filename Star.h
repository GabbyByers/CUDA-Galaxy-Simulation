#pragma once

#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include "Vec3.h"
#include "CanvasCamera.h"

__device__ class Ray {
public:
	Vec3 position;
	Vec3 direction;

	Vec3 __device__ at(float t) {
		return position + (direction * t);
	}
};

class Star {
public:
	Vec3 pos;
	Vec3 vel;

	int image_position = 0;

	Star() {}

	Star(Vec3 pos) {
		this->pos = pos;
	}

	__device__ void projection(CanvasCamera* canvas_camera) {
		// create a ray from the camera to the star
		Ray ray;
		ray.position = canvas_camera->camera_position;
		ray.direction = canvas_camera->origin - canvas_camera->camera_position;
		ray.direction.normalize();

		float t = (canvas_camera->canvas_position - ray.position).dot(canvas_camera->canvas_normal);
		t /= ray.direction.dot(canvas_camera->canvas_normal);

		Vec3 canvas_projection = ray.at(t);

		Vec3 barry = canvas_projection - canvas_camera->canvas_position;
		float fx = barry.dot(canvas_camera->camera_horizontal);
		float fy = barry.dot(canvas_camera->vertical);

		//int ix = fx * 500;
	}
};