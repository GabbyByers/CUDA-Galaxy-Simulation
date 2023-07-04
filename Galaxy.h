#pragma once

class Galaxy {
public:
	int num_stars = 2187;
	Star* host_stars = nullptr;
	Star* device_stars = nullptr;

	Galaxy() {
		initializeHostStars();
	}

	void initializeHostStars() {
		host_stars = new Star[num_stars];
		int cube_root = static_cast<int>(pow(num_stars, (1.0f / 3.0f)));
		cube_root++;

		int index = 0;
		for (int i = 0; i < cube_root; i++) {
			for (int j = 0; j < cube_root; j++) {
				for (int k = 0; k < cube_root; k++) {

					index++;
					if (index == num_stars) {
						goto Exit;
					}

					float x = (2.0f * (static_cast<float>(i) / static_cast<float>(cube_root))) - 1.0f;
					float y = (2.0f * (static_cast<float>(j) / static_cast<float>(cube_root))) - 1.0f;
					float z = (2.0f * (static_cast<float>(k) / static_cast<float>(cube_root))) - 1.0f;

					Star star(Vec3(x, y, z));
					host_stars[i] = star;
				}
			}
		}
	Exit:
		device_stars = allocateDeviceStars(host_stars, num_stars);
	}

	~Galaxy() {
		delete[] host_stars;
		freeDeviceStars(device_stars);
	}
};