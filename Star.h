#pragma once

#include "Vec3.h"

class Ray {
public:
	Vec3 position;
	Vec3 direction;
};

class Star {
public:
	Vec3 pos;
	Vec3 vel;

	Star() {}

	Star(Vec3 pos) {
		this->pos = pos;
	}

	void projection() {

	}
};