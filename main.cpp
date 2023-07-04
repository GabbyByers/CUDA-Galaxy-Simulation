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

	//////////  THE great CASE study

	CanvasCamera cc;
	cc.setProperties();

	std::cout << "camera_depth: " << cc.camera_depth << "\n";
	std::cout << "canvas_depth: " << cc.canvas_depth << "\n";
	std::cout << "theta: " << cc.theta << "\n";
	cc.origin.print("origin");
	cc.vertical.print("vertical");
	cc.camera_position.print("camera_position");
	cc.camera_direction.print("camera_direction");
	cc.camera_horizontal.print("camera_horizontal");
	cc.canvas_position.print("canvas_position");
	cc.canvas_normal.print("canvas_normal");

	Star star;
	star.position = Vec3(-0.5f, -0.5f, -0.5f);
	star.projection(&cc);

	//////////  THE great CASE study

	Color& color = scene_renderer.pixels[star.image_position];
	color.r = 255;
	color.b = 255;

	//for (int i = 0; i < galaxy.num_stars; i++) {
	//	Star& star = galaxy.host_stars[i];
	//	star.position.print();
	//}

	while (game.open()) {
		game.eventHandler();
		scene_renderer.render();
	}

	return 0;
}