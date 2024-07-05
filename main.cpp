#include "app.hpp"
#undef main

#include <float.h>

auto main() -> int {
	//read config first
	//get variables settings
	//then set variables

	//std::cout << substitute("2*x+1-x*x^x/x+1239.0", 'x', 123) << "\n\n";

	//std::cout << (infixToPostfix("0.1+0.1-0.1")) << "\n";
	/*std::cout << (infixToPostfix("0.123+0.123-0.123")) << "\n";
	std::cout << (infixToPostfix("1.2345+1.2345-1.2345")) << "\n";
	std::cout << (infixToPostfix("0.00001+0.00001-0.00001")) << "\n";
	std::cout << (infixToPostfix("9999.999901/2/2")) << "\n";*/

	Window::getWindow();

	readConfigFile("assets/config.cfg");

	//App::getApp()->init(std::any_cast<int>(variables["width"]), std::any_cast<int>(variables["height"]));
	App::getApp();
	bool quit = false;

	while (!quit) {
		quit = App::getApp()->handleEvents();
		App::getApp()->update();
		App::getApp()->render(Window::getWindow()->_renderer);
	}

	//App::getApp()->getGrid()->drawFunction(App::getApp()->renderer, "2*x");
	//while (1) true;

	return 0;
}