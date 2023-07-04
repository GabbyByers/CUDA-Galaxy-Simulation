#pragma once

class CanvasCamera {
public:
	float camera_depth;
	float canvas_depth;
	float theta;
	Vec3 origin;
	Vec3 vertical;

	Vec3 camera_position;
	Vec3 camera_direction;
	Vec3 camera_horizontal;

	Vec3 canvas_position;
	Vec3 canvas_normal;

	CanvasCamera() {
		camera_depth = 4.0f;
		canvas_depth = 2.0f;
		theta = 1.0f;
		origin = Vec3(0.0f, 0.0f, 0.0f);
		vertical = Vec3(0.0f, 1.0f, 0.0f);
	}

	void setProperties() {
		camera();
		canvas();
	}

	void camera() {
		camera_position.x = sin(theta) * camera_depth;
		camera_position.z = cos(theta) * camera_depth * -1.0f;
		camera_direction = origin - camera_position;
		camera_direction.normalize();
		camera_horizontal = camera_direction.cross(vertical);
	}

	void canvas() {
		canvas_position = camera_position;
		canvas_position.normalize();
		canvas_position *= canvas_depth;
		canvas_normal = origin - canvas_position;
		canvas_normal.normalize();
	}
};