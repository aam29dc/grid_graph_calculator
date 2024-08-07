#include "app.hpp"
#undef main

#include <iostream>
#include <float.h>

auto main() -> int {
	//read config first
	//get variables settings
	//then set variables

	Window::getWindow();

	//readConfigFile("assets/config.cfg");

	//App::getApp()->init(std::any_cast<int>(variables["width"]), std::any_cast<int>(variables["height"]));
	App::getApp();
	bool quit = false;

	//std::cout << convertUnaryToBinary("-0.5-(0.5)");

	while (!quit) {
		quit = App::getApp()->handleEvents();
		App::getApp()->update();
		App::getApp()->render(Window::getWindow()->_renderer);
	}

	return 0;
}