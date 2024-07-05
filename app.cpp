#include "app.hpp"

App* App::_app = nullptr;

class Button App::_keypad[NUM_BUTTONS];

App::App() {
	_grid = new Grid();
    _startTime = 0;
	_textInput = "";
	_inputHistory = "";
	_textInputColor = { 0, 0, 0, 255 };
	_bgColor = { 0, 0, 0, 255 };
	TEXTFIELD_OFFSET_X = (Window::getWindow()->_width / 2);
	TEXTFIELD_OFFSET_Y = 32;
	TEXTFIELD_WIDTH = (Window::getWindow()->_width / 2);
	KEYPAD_OFFSET_X = 0;
	KEYPAD_OFFSET_Y = 0;
	_setupKeypad();
}

App::~App() {
	delete _grid;
	_grid = nullptr;
}

App* App::getApp() {
	if (_app == nullptr) _app = new App();
	return _app;
}

void App::setInputHistory(const std::string& text) {
	_inputHistory = text;
}

void App::_setupKeypad() {
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

	for (int i = 0; i < NUM_BUTTONS; i++) {
		_keypad[i].setText(std::string(1, _keymap[i]));
		_keypad[i].setPosX(((Window::getWindow()->_height / 10) * (i % KEYPAD_COLS)));
		_keypad[i].setPosY(((Window::getWindow()->_height / 10) * int(i / KEYPAD_COLS)));
		_keypad[i].setHeight(32);
		_keypad[i].setWidth(32);

		if (_keymap[i] == '0') _keypad[i].setCallback(zeroPressEvent);
		else if (isNumber(_keymap[i])) _keypad[i].setCallback(numberPressEvent);
		else if (isOperator(_keymap[i])) _keypad[i].setCallback(operatorPressEvent);
		else if (_keymap[i] == '(') _keypad[i].setCallback(leftParaPressEvent);
		else if (_keymap[i] == ')') _keypad[i].setCallback(rightParaPressEvent);
		else if (_keymap[i] == 'x') _keypad[i].setCallback(xPressEvent);
		else if (_keymap[i] == 'c') _keypad[i].setCallback(CEPressEvent);
		else if (_keymap[i] == 'C') _keypad[i].setCallback(clearPressEvent);
		else if (_keymap[i] == 'B') _keypad[i].setCallback(backPressEvent);
		else if (_keymap[i] == '~') _keypad[i].setCallback(negatePressEvent);
		else if (_keymap[i] == '.') _keypad[i].setCallback(decimalPressEvent);
		else if (_keymap[i] == '=') _keypad[i].setCallback(equalPressEvent);
	}
}

Grid* App::getGrid() const {
	return _grid;
}

void App::writeScreenshot(SDL_Renderer* renderer) const {
	SDL_Surface* sshot = SDL_CreateRGBSurfaceWithFormat(0, Window::getWindow()->_width, Window::getWindow()->_height, 24, SDL_PIXELFORMAT_RGB24);
	SDL_RenderReadPixels(renderer, NULL, SDL_PIXELFORMAT_RGB24, sshot->pixels, sshot->pitch);
	//this only saves 1 screenshot for now...
	SDL_SaveBMP(sshot, "screenshots/filename.bmp");
	SDL_FreeSurface(sshot);
}

int App::_findKey(const char& ch) const {
	for (auto it = _keymap.begin(); it != _keymap.end(); ++it) {
		if (it->second == ch) return it->first;
	}
	return -1;
}

bool App::handleEvents() {
	Input::getInputHandler()->updatePrevKeyStates();
	if (Input::getInputHandler()->update() == true) {	//return bool handles window exit
		return true;
	}

	if (Input::getInputHandler()->isKeyReleased(SDL_SCANCODE_UP)) {
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

	if (Input::getInputHandler()->isKeyReleased(SDL_SCANCODE_F1)) {
		_grid->setZoom(_grid->getZoom() + 0.1f);
	}	//cant move zoom in and out at sametime
	else if (Input::getInputHandler()->isKeyReleased(SDL_SCANCODE_F2)) {
		_grid->setZoom(_grid->getZoom() - 0.1f);
	}

	if (Input::getInputHandler()->isKeyReleased(SDL_SCANCODE_O)) {
		_grid->setShiftx(0.0f);
		_grid->setShifty(0.0f);
		_grid->setZoom(1.0f);
	}

	for (int i = 1; i < 10; i++) {
		if (Input::getInputHandler()->isKeyReleased(SDL_Scancode(SDL_SCANCODE_1 + i - 1))) {
			_keypad[_findKey(i + '0')].callback();
		}
	}
	if (Input::getInputHandler()->isKeyReleased(SDL_SCANCODE_0)) {
		_keypad[_findKey('0')].callback();
	}
	if (Input::getInputHandler()->isKeyReleased(SDL_SCANCODE_MINUS)) {
		_keypad[_findKey('-')].callback();
	}
	if (Input::getInputHandler()->isKeyReleased(SDL_SCANCODE_KP_PLUS)) {
		_keypad[_findKey('+')].callback();
	}
	if (Input::getInputHandler()->isKeyReleased(SDL_SCANCODE_EQUALS)) {
		_keypad[_findKey('=')].callback();
	}
	if (Input::getInputHandler()->isKeyReleased(SDL_SCANCODE_LEFTBRACKET)) {
		_keypad[_findKey('(')].callback();
	}
	if (Input::getInputHandler()->isKeyReleased(SDL_SCANCODE_RIGHTBRACKET)) {
		_keypad[_findKey(')')].callback();
	}
	if (Input::getInputHandler()->isKeyReleased(SDL_SCANCODE_X)) {
		_keypad[_findKey('x')].callback();
	}
	if (Input::getInputHandler()->isKeyReleased(SDL_SCANCODE_PERIOD)) {
		_keypad[_findKey('.')].callback();
	}
	if (Input::getInputHandler()->isKeyReleased(SDL_SCANCODE_KP_DIVIDE)) {
		_keypad[_findKey('/')].callback();
	}
	if (Input::getInputHandler()->isKeyReleased(SDL_SCANCODE_GRAVE)) {
		_keypad[_findKey('~')].callback();
	}
	if (Input::getInputHandler()->isKeyReleased(SDL_SCANCODE_0)) {
		_keypad[_findKey('0')].callback();
	}
	if (Input::getInputHandler()->isKeyDown(SDL_SCANCODE_ESCAPE)) {
		return true;
	}
	return false;
}

void App::update() {
	SDL_Point mpos = Input::getInputHandler()->getMousePosition();

	getGrid()->setHeight(Window::getWindow()->_height);
	getGrid()->setWidth(Window::getWindow()->_width / 2);
	TEXTFIELD_OFFSET_X = (Window::getWindow()->_width / 2);
	TEXTFIELD_OFFSET_Y = 32;
	TEXTFIELD_WIDTH = (Window::getWindow()->_width / 2);
	KEYPAD_OFFSET_X = (Window::getWindow()->_width / 2) + (Window::getWindow()->_width / 8);
	KEYPAD_OFFSET_Y = (Window::getWindow()->_height / 4);

	for (unsigned int i = 0; i < NUM_BUTTONS; i++) {
		_keypad[i].setWidth(32);
		_keypad[i].setHeight(32);

		if ((mpos.x > _keypad[i].getPosX() + KEYPAD_OFFSET_X && mpos.x < _keypad[i].getPosX() + _keypad[i].getWidth() + KEYPAD_OFFSET_X)
			&& (mpos.y > _keypad[i].getPosY() + KEYPAD_OFFSET_Y && mpos.y < _keypad[i].getPosY() + _keypad[i].getHeight() + KEYPAD_OFFSET_Y)) {

			_keypad[i].setHover(true);

			if (Input::getInputHandler()->isMouseKeyReleased(mouse_buttons::LEFT)) {
				_keypad[i].setClick(true);
			}
			else _keypad[i].setClick(false);
		}
		else _keypad[i].setHover(false);
	}

	for (int i = 0; i < NUM_BUTTONS; i++) {
		if (_keypad[i].getClick() == true) {
			_keypad[i].callback();
		}
	}
}

void App::render(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, _bgColor.r, _bgColor.g, _bgColor.b, _bgColor.a);
	SDL_RenderClear(renderer);

	_grid->draw(renderer);
	if (!_textInput.empty() && _textInput.find('x') != std::string::npos && !isOperator(_textInput.back())) {
		_grid->drawFunction(renderer, _textInput);
	}

	_drawTextField(renderer);

	//_keypad
	for (int i = 0; i < NUM_BUTTONS; i++) {
		_keypad[i].draw(renderer, KEYPAD_OFFSET_X, KEYPAD_OFFSET_Y);
	}
	SDL_RenderPresent(renderer);
}

void App::_drawTextField(SDL_Renderer* renderer) const {
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

	drawString(renderer, _textInput, TEXTFIELD_OFFSET_X, TEXTFIELD_OFFSET_Y, _textInputColor, Window::getWindow()->_width / 26, true);
	drawString(renderer, _inputHistory, TEXTFIELD_OFFSET_X, 0, {255,255,255,255}, Window::getWindow()->_width / 26, true);
}

std::string App::getTextInput() const {
	return _textInput;
}

std::string App::getInputHistory() const {
	return _inputHistory;
}

void App::setTextInput(const std::string& text) {
	_textInput = text;
}