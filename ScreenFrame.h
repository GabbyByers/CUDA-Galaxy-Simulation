#pragma once

class ScreenFrame {
public:
	Game* game = nullptr;
	Galaxy* galaxy = nullptr;
	Renderer* renderer = nullptr;

	sf::Image image;
	sf::Texture texture;
	sf::Vertex quad[4];

	int num_pixels;
	Color* pixels = nullptr;

	ScreenFrame(Game* game, Galaxy* galaxy, Renderer* renderer) {
		this->game = game;
		this->galaxy = galaxy;
		this->renderer = renderer;
		initialize();
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
		for (int i = 0; i < num_pixels; i++) {
			Color& color = pixels[i];
			color.r = 255;
			color.b = 255;
			//draw();
		}
	}

	void draw() {
		game->window->clear(sf::Color(0, 0, 0));
		texture.loadFromImage(image);
		game->window->draw(&quad[0], 4, sf::Quads, &texture);
		game->window->display();
	}
};