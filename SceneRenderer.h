#pragma once

class SceneRenderer {
public:
	Game* game = nullptr;
	Galaxy* galaxy = nullptr;
	CanvasCamera* host_canvas_camera = nullptr;
	CanvasCamera* device_canvas_camera = nullptr;

	sf::Image image;
	sf::Texture texture;
	sf::Vertex quad[4];

	int num_pixels;
	Color* pixels = nullptr;

	int* star_image_positions = nullptr;

	SceneRenderer(Game* game, Galaxy* galaxy) {
		this->game = game;
		this->galaxy = galaxy;
		host_canvas_camera = new CanvasCamera;
		device_canvas_camera = allocateDeviceCanvasCamera();
		star_image_positions = new int[galaxy->num_stars];
		initialize();
	}

	~SceneRenderer() {
		delete host_canvas_camera;
		delete[] star_image_positions;
		freeDeviceCanvasCamera(device_canvas_camera);
	}

	void initialize() {
		int w = game->width;
		int h = game->height;
		quad[0] = sf::Vertex(sf::Vector2f(0, 0), sf::Vector2f(0, 0));
		quad[1] = sf::Vertex(sf::Vector2f(w, 0), sf::Vector2f(w, 0));
		quad[2] = sf::Vertex(sf::Vector2f(w, h), sf::Vector2f(w, h));
		quad[3] = sf::Vertex(sf::Vector2f(0, h), sf::Vector2f(0, h));

		num_pixels = game->numPixels();
		image.create(game->width, game->height, sf::Color(11, 22, 33));
		pixels = reinterpret_cast<Color*>(const_cast<sf::Uint8*>(image.getPixelsPtr()));
	}

	void render() {
		int num_stars = galaxy->num_stars;
		Star* host_stars = galaxy->host_stars;
		Star* device_stars = galaxy->device_stars;

		host_canvas_camera->setProperties();
		sendCanvasCameraToDevice(device_canvas_camera, host_canvas_camera);
		deviceStarProjection(device_stars, num_stars, device_canvas_camera);
		copyDeviceStarsToHostStars(host_stars, device_stars, num_stars);

		
		for (int i = 0; i < num_stars; i++) { // TODO: should be done on the gpu
			Star& star = host_stars[i];
			star_image_positions[i] = star.image_position;
		}

		// intialize every pixel to black
		for (int i = 0; i < num_pixels; i++) {
			Color& color = pixels[i];
			color.r = 0;
			color.g = 0;
			color.b = 0;
		}

		// loop through every star-image-position and set her corresponding pixel to pink
		for (int i = 0; i < num_stars; i++) {
			int image_position = host_stars[i].image_position;
			Color& color = pixels[image_position];
			color.r = 255;
			color.b = 255;
		}

		draw();
	}

	void draw() {
		game->window->clear(sf::Color(0, 0, 0));
		texture.loadFromImage(image);
		game->window->draw(&quad[0], 4, sf::Quads, &texture);
		game->window->display();
	}
};