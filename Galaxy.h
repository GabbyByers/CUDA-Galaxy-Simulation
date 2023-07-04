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

					float x = 1.0f;
					float y = 1.0f;
					float z = 1.0f;

					Star& star = host_stars[i];
					star.position = Vec3(x, y, z);
				}
			}
		}



	Exit:

		for (int i = 0; i < num_stars; i++) {
			Star& star = host_stars[i];
			star.position.print();
		}


		device_stars = allocateDeviceStars(host_stars, num_stars);
	}

	~Galaxy() {
		delete[] host_stars;
		freeDeviceStars(device_stars);
	}
};