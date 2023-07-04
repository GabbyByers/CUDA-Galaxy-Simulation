#pragma once

#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include "Vec3.h"
#include "CanvasCamera.h"

class Star {
public:
	Vec3 position;
	Vec3 velocity;

	int image_position = 0;

	Star() {}

	Star(Vec3 position) {
		this->position = position;
	}

	__device__ __host__ void projection(CanvasCamera* cc) {

		//std::cout << "\n\n";

		Vec3 ray_position = cc->camera_position;
		//ray_position.print("ray position");

		Vec3 ray_direction = position - cc->camera_position;
		//ray_direction.print("ray direction");

		ray_direction.normalize();
		//ray_direction.print("ray direction normalized");

		float t = (cc->canvas_position - ray_position).dot(cc->canvas_normal);
		t /= ray_direction.dot(cc->canvas_normal);
		//std::cout << "t: " << t << "\n";

		Vec3 canvas_projection = ray_position + (ray_direction * t);
		//canvas_projection.print("canvas projection");

		Vec3 barry = canvas_projection - cc->canvas_position;
		//barry.print("barry");

		Vec3 corner_position = cc->canvas_position + cc->camera_horizontal + cc->vertical;
		//corner_position.print("corner position");

		Vec3 screen_vector = canvas_projection - corner_position;
		//screen_vector.print("screen_vector");

		screen_vector /= 2.0f;
		//screen_vector.print("screen_vector half");

		Vec3 screen_x_axis = (cc->canvas_position + cc->vertical) - corner_position;
		Vec3 screen_y_axis = (cc->canvas_position + cc->camera_horizontal) - corner_position;
		//screen_x_axis.print("screen x axis");
		//screen_y_axis.print("screen y axis");

		float xpos = screen_vector.dot(screen_x_axis);
		float ypos = screen_vector.dot(screen_y_axis);
		//std::cout << "float screen coords: (" << xpos << ", " << ypos << ")\n";
		
		int width = 500;
		int height = 500;

		int xcord = static_cast<int>(xpos * static_cast<float>(width));
		int ycord = static_cast<int>(ypos * static_cast<float>(height));
		//std::cout << "int screen coords: (" << xcord << ", " << ycord << ")\n";

		image_position = (ycord * width) + xcord;
		//std::cout << "image_position: " << image_position << "\n";
	}
};