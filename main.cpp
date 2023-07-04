#include "Star.h"
#include "kernel.cuh"
#include "SFML/Graphics.hpp"
#include "Game.h"
#include "Galaxy.h"
#include "CanvasCamera.h"
#include "Color.h"
#include "SceneRenderer.h"

int main() {
	Game game(500, 500);
	Galaxy galaxy;
	SceneRenderer scene_renderer(&game, &galaxy);

	while (game.open()) {
		game.eventHandler();
		scene_renderer.render();
	}

	return 0;
}