#include "Star.h"
#include "kernel.cuh"
#include "SFML/Graphics.hpp"
#include "Game.h"
#include "Galaxy.h"
#include "Renderer.h"
#include "Color.h"
#include "ScreenFrame.h"

int main() {
	Game game(500, 500);

	Renderer renderer;
	renderer.camera();
	renderer.canvas();
	renderer.camera_position.print("Camera Position");
	renderer.canvas_position.print("Canvas Position");
	renderer.canvas_normal.print("Canvas Normal");

	Galaxy galaxy;
	galaxy.initializeHostStars();

	ScreenFrame screen_frame(&game, &galaxy, &renderer);

	while (game.open()) {
		game.eventHandler();
		screen_frame.render();
		screen_frame.draw();
	}

	return 0;
}