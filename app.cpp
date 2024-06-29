#include "app.hpp"

App* App::_app = nullptr;

class Button App::keypad[NUM_BUTTONS];

/*
	App is defined within a 640x320 window,
	origin is top left corner
*/
App::App() {
	_width = SCREEN_WIDTH;
	_height = SCREEN_HEIGHT;
	window = nullptr;
	renderer = nullptr;
	_grid = new Grid();
    _startTime = 0;
	_textInput = "";
	_textInputColor = { 0,0,0,255 };
	_bgColor = { 0, 0, 0, 255 };
	_keymap[0] = '(';
	_keymap[1] = ')';
	_keymap[2] = 'x';
	_keymap[3] = '^';
	_keymap[4] = 'c';
	_keymap[5] = 'C';
	_keymap[6] = 'B';
	_keymap[7] = '/';
	_keymap[8] = '7';
	_keymap[9] = '8';
	_keymap[10] = '9';
	_keymap[11] = '*';
	_keymap[12] = '4';
	_keymap[13] = '5';
	_keymap[14] = '6';
	_keymap[15] = '-';
	_keymap[16] = '1';
	_keymap[17] = '2';
	_keymap[18] = '3';
	_keymap[19] = '+';
	_keymap[20] = '~';
	_keymap[21] = '0';
	_keymap[22] = '.';
	_keymap[23] = '=';
}

App::~App() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
	delete _grid;
	window = nullptr;
	renderer = nullptr;
	_grid = nullptr;
}

App* App::getApp() {
	if (_app == nullptr) _app = new App();
	return _app;
}

int App::init(unsigned int width, unsigned int height) {
	_width = width;
	_height = height;
	int errorFlags = 1;

	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0) {
		window = SDL_CreateWindow("SDL2 Grapher", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, _width, _height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
			//std::cout << "Warning: Linear texture filtering not enabled!" << "\n";
			errorFlags = -2;
		}

		if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
			//std::cout << "SDL_image could not initialize! SDL_image Error :" << IMG_GetError() << "\n";
			errorFlags -= 4;
		}

		if (!initFont()) {
			//std::cout << "Init font error SDL_ttf: " << TTF_GetError() << "\n";
			errorFlags -= 8;
		}

		//SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_ADD);

		_setupKeypad();
	}
	else errorFlags = -1;

	return errorFlags;
}

void App::_setupKeypad() {
	for (int i = 0; i < NUM_BUTTONS; i++) {
		keypad[i].setText(std::string(1, _keymap[i]));
		keypad[i].setPosX((33 * (i % KEYPAD_COLS)) + KEYPAD_OFFSET_X);
		keypad[i].setPosY((33 * int(i / KEYPAD_COLS)) + KEYPAD_OFFSET_Y);

		if (isNumber(_keymap[i])) keypad[i].setCallback(numberPressEvent);
		else if (isOperator(_keymap[i])) keypad[i].setCallback(operatorPressEvent);
		else if (_keymap[i] == '(') keypad[i].setCallback(leftParaPressEvent);
		else if (_keymap[i] == ')') keypad[i].setCallback(rightParaPressEvent);
		else if (_keymap[i] == 'x') keypad[i].setCallback(xPressEvent);
		else if (_keymap[i] == 'c') keypad[i].setCallback(clearPressEvent);
		else if (_keymap[i] == 'C') keypad[i].setCallback(clearPressEvent);
		else if (_keymap[i] == 'B') keypad[i].setCallback(backPressEvent);
		else if (_keymap[i] == '~') keypad[i].setCallback(negatePressEvent);
		else if (_keymap[i] == '0') keypad[i].setCallback(zeroPressEvent);
		else if (_keymap[i] == '.') keypad[i].setCallback(decimalPressEvent);
		else if (_keymap[i] == '=') keypad[i].setCallback(equalPressEvent);
	}
}

Grid* App::getGrid() const {
	return _grid;
}

void App::writeScreenshot() const {
	SDL_Surface* sshot = SDL_CreateRGBSurfaceWithFormat(0, _width, _height, 24, SDL_PIXELFORMAT_RGB24);
	SDL_RenderReadPixels(renderer, NULL, SDL_PIXELFORMAT_RGB24, sshot->pixels, sshot->pitch);
	//this only saves 1 screenshot for now...
	SDL_SaveBMP(sshot, "screenshots/filename.bmp");
	SDL_FreeSurface(sshot);
}

bool App::handleEvents() {
	Input::getInputHandler()->updatePrevKeyStates();
	Input::getInputHandler()->update();

	/*if (Input::getInputHandler()->isKeyReleased(SDL_SCANCODE_UP)) {
		_grid->setShifty(_grid->getShifty() + 0.1f);
	}	//cant move up and down at sametime
	else if (Input::getInputHandler()->isKeyReleased(SDL_SCANCODE_DOWN)) {
		_grid->setShifty(_grid->getShifty() - 0.1f);
	}

	if (Input::getInputHandler()->isKeyReleased(SDL_SCANCODE_LEFT)) {
		_grid->setShiftx(_grid->getShiftx() - 0.1f);
	}	//cant move left and right at sametime
	else if (Input::getInputHandler()->isKeyReleased(SDL_SCANCODE_RIGHT)) {
		_grid->setShiftx(_grid->getShiftx() + 0.1f);
	}

	if (Input::getInputHandler()->isKeyReleased(SDL_SCANCODE_EQUALS)) {
		_grid->setZoom(_grid->getZoom() + 0.1f);
	}	//cant move zoom in and out at sametime
	else if (Input::getInputHandler()->isKeyReleased(SDL_SCANCODE_MINUS)) {
		_grid->setZoom(_grid->getZoom() - 0.1f);
	}*/

	if (Input::getInputHandler()->isKeyReleased(SDL_SCANCODE_1)) {
		keypad[16].callback();
	}
	if (Input::getInputHandler()->isKeyReleased(SDL_SCANCODE_2)) {
		keypad[17].callback();
	}
	if (Input::getInputHandler()->isKeyReleased(SDL_SCANCODE_3)) {
		keypad[18].callback();
	}
	if (Input::getInputHandler()->isKeyReleased(SDL_SCANCODE_3)) {
		keypad[19].callback();
	}
	if (Input::getInputHandler()->isKeyReleased(SDL_SCANCODE_O)) {
		_grid->setShiftx(0.0f);
		_grid->setShifty(0.0f);
		_grid->setZoom(1.0f);
	}
	if (Input::getInputHandler()->isKeyDown(SDL_SCANCODE_ESCAPE)) {
		return true;
	}
	return false;
}

void App::update() {
	SDL_Point mpos = Input::getInputHandler()->getMousePosition();

	for (unsigned int i = 0; i < NUM_BUTTONS; i++) {
		if ((mpos.x > keypad[i].getPosX() && mpos.x < keypad[i].getPosX() + keypad[i].getHeight()) 
			&& (mpos.y > keypad[i].getPosY() && mpos.y < keypad[i].getPosY() + keypad[i].getHeight())) {

			keypad[i].setHover(true);

			if (Input::getInputHandler()->isMouseKeyReleased(mouse_buttons::LEFT)) {
				keypad[i].setClick(true);
			}
			else keypad[i].setClick(false);
		}
		else keypad[i].setHover(false);
	}

	for (int i = 0; i < NUM_BUTTONS; i++) {
		if (keypad[i].getClick() == true) {
			keypad[i].callback();
		}
	}

}

void App::render() {
	SDL_SetRenderDrawColor(renderer, _bgColor.r, _bgColor.g, _bgColor.b, _bgColor.a);
	SDL_RenderClear(renderer);

	_grid->draw(renderer);

	drawTextField();

	//keypad
	for (int i = 0; i < NUM_BUTTONS; i++) {
		keypad[i].draw(renderer);
	}
	SDL_RenderPresent(renderer);
}

void App::drawTextField() const {
	//draw expression field
	SDL_Rect rec = { 0 };
	rec.x = TEXTFIELD_OFFSET_X;
	rec.y = TEXTFIELD_OFFSET_Y;
	rec.w = TEXTFIELD_WIDTH;
	rec.h = (int)TEXTSIZE;

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, &rec);
	SDL_SetRenderDrawColor(renderer, 155, 155, 155, 255);
	SDL_RenderDrawRect(renderer, &rec);

	drawString(renderer, _textInput, TEXTFIELD_OFFSET_X, TEXTFIELD_OFFSET_Y, _textInputColor, true);
}

std::string App::getTextInput() const {
	return _textInput;
}


void App::setTextInput(std::string text) {
	_textInput = text;
}

unsigned int App::getHeight() const {
	return _height;
}

unsigned int App::getWidth() const {
	return _width;
}

void App::setHeight(const unsigned int val) {
	_height = val;
}

void App::setWidth(const unsigned int val) {
	_width = val;
}