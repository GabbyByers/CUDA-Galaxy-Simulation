#pragma once

class Color {
public:
	unsigned char r, g, b, a;

	void print() {
		std::cout << "r: " << (unsigned)r << " g: " << (unsigned)g << " b: " << (unsigned)b << " a: " << (unsigned)a << "\n";
	}
};