#include "app.hpp"

App* App::_app = nullptr;

class Button App::_keypad[NUM_BUTTONS];

App::App() {
	_grid = new Grid();
    _startTime = 0;
	_textInput = "";
	_inputHistory.push_back("");
	_textInputColor = { 0, 0, 0, 255 };
	_bgColor = { 0, 0, 0, 255 };
	_funcColor = { 255,0,0,255 };
	_tf_offset_x = (Window::getWindow()->getWidth() / 2);
	_tf_offset_y = 32;
	_tf_width = (Window::getWindow()->getWidth() / 2);
	_keypad_offset_x = 0;
	_keypad_offset_y = 0;
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

void App::setInputHistory(const std::string& text, const unsigned int& at) {
	if (at < _inputHistory.size()) {
		_inputHistory[at] = text;
	}
	else {
		_inputHistory.push_back(text);
	}
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

	_keypad_offset_x = (Window::getWindow()->getWidth() / 2.0f);
	_keypad_offset_y = (Window::getWindow()->getHeight() / 4.0f);

	for (unsigned int i = 0; i < NUM_BUTTONS; i++) {
		_keypad[i]._text = (std::string(1, _keymap[i]));
		_keypad[i]._posx = (32.0f * float(Window::getWindow()->getWidth() / 320.0f) * float(i % KEYPAD_COLS));
		_keypad[i]._posy = (32.0f * float(Window::getWindow()->getHeight() / 320.0f) * float(i / KEYPAD_COLS));
		_keypad[i]._width = (32.0f * float(Window::getWindow()->getWidth() / 320.0f));
		_keypad[i]._height = (32.0f * float(Window::getWindow()->getHeight() / 320.0f));

		if (_keymap[i] == '0') _keypad[i]._callback = zeroPressEvent;
		else if (_keymap[i] == 'x') _keypad[i]._callback = xPressEvent;
		else if (isNumber(_keymap[i]) && _keymap[i] != 'x') _keypad[i]._callback = numberPressEvent;
		else if (isOperator(_keymap[i])) _keypad[i]._callback = operatorPressEvent;
		else if (_keymap[i] == '(') _keypad[i]._callback = leftParaPressEvent;
		else if (_keymap[i] == ')') _keypad[i]._callback = rightParaPressEvent;
		else if (_keymap[i] == 'c') _keypad[i]._callback = CEPressEvent;
		else if (_keymap[i] == 'C') _keypad[i]._callback = clearPressEvent;
		else if (_keymap[i] == 'B') _keypad[i]._callback = backPressEvent;
		else if (_keymap[i] == '~') _keypad[i]._callback = negatePressEvent;
		else if (_keymap[i] == '.') _keypad[i]._callback = decimalPressEvent;
		else if (_keymap[i] == '=') _keypad[i]._callback = equalPressEvent;
	}
}

Grid* App::getGrid() const {
	return _grid;
}

void App::_nextFuncColor(const unsigned int& seq) {
	char n = (seq % 7) + 1;		// skips (0,0,0)

	_funcColor.r = (n & 1)*255;
	_funcColor.g = (n & 2)*255;
	_funcColor.b = (n & 4)*255;
}

void App::writeScreenshot(SDL_Renderer* renderer) const {
	SDL_Surface* sshot = SDL_CreateRGBSurfaceWithFormat(0, Window::getWindow()->getWidth(), Window::getWindow()->getHeight(), 24, SDL_PIXELFORMAT_RGB24);
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
	SDL_Point mpos = Input::getInputHandler()->getMousePosition();
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

	for (unsigned int i = 1; i < 10; i++) {
		if (Input::getInputHandler()->isKeyReleased(SDL_Scancode(SDL_SCANCODE_1 + i - 1))) {
			_keypad[_findKey(i + '0')]._callback(i + '0');
		}
	}
	if (Input::getInputHandler()->isKeyReleased(SDL_SCANCODE_0)) {
		_keypad[_findKey('0')]._callback('0');
	}
	if (Input::getInputHandler()->isKeyReleased(SDL_SCANCODE_MINUS)) {
		_keypad[_findKey('-')]._callback('-');
	}
	if (Input::getInputHandler()->isKeyReleased(SDL_SCANCODE_KP_PLUS)) {
		_keypad[_findKey('+')]._callback('+');
	}
	if (Input::getInputHandler()->isKeyReleased(SDL_SCANCODE_EQUALS)) {
		_keypad[_findKey('=')]._callback('=');
	}
	if (Input::getInputHandler()->isKeyReleased(SDL_SCANCODE_LEFTBRACKET)) {
		_keypad[_findKey('(')]._callback('(');
	}
	if (Input::getInputHandler()->isKeyReleased(SDL_SCANCODE_RIGHTBRACKET)) {
		_keypad[_findKey(')')]._callback(')');
	}
	if (Input::getInputHandler()->isKeyReleased(SDL_SCANCODE_X)) {
		_keypad[_findKey('x')]._callback('x');
	}
	if (Input::getInputHandler()->isKeyReleased(SDL_SCANCODE_PERIOD)) {
		_keypad[_findKey('.')]._callback('.');
	}
	if (Input::getInputHandler()->isKeyReleased(SDL_SCANCODE_KP_DIVIDE)) {
		_keypad[_findKey('/')]._callback('/');
	}
	if (Input::getInputHandler()->isKeyReleased(SDL_SCANCODE_GRAVE)) {
		_keypad[_findKey('~')]._callback('~');
	}
	if (Input::getInputHandler()->isKeyDown(SDL_SCANCODE_ESCAPE)) {
		return true;
	}

	for (unsigned int i = 0; i < NUM_BUTTONS; i++) {
		if ((mpos.x > _keypad[i]._posx + _keypad_offset_x && mpos.x < _keypad[i]._posx + _keypad[i]._width + _keypad_offset_x)
			&& (mpos.y > _keypad[i]._posy + _keypad_offset_y && mpos.y < _keypad[i]._posy + _keypad[i]._height + _keypad_offset_y)) {

			_keypad[i]._hover = (true);

			if (Input::getInputHandler()->isMouseKeyReleased(mouse_buttons::LEFT)) {
				_keypad[i]._click = (true);
			}
			else _keypad[i]._click = (false);
		}
		else _keypad[i]._hover = (false);
	}

	for (unsigned int i = 0; i < NUM_BUTTONS; i++) {
		if (_keypad[i]._click == true) {
			_keypad[i]._callback(_keymap[i]);
		}
	}

	return false;
}

void App::update() {
	getGrid()->setHeight(Window::getWindow()->getHeight());
	getGrid()->setWidth(Window::getWindow()->getWidth() / 2);
	_tf_offset_x = (Window::getWindow()->getWidth() / 2);
	_tf_offset_y = 32;
	_tf_width = (Window::getWindow()->getWidth() / 2);
	_keypad_offset_x = (Window::getWindow()->getWidth() / 2.0f) + (Window::getWindow()->getWidth() / 16.0f);
	_keypad_offset_y = (Window::getWindow()->getHeight() / 4.0f);

	for (unsigned int i = 0; i < NUM_BUTTONS; i++) {
		_keypad[i]._posx = (32.0f * float(Window::getWindow()->getWidth() / 320.0f) * float(i % KEYPAD_COLS));
		_keypad[i]._posy = (32.0f * float(Window::getWindow()->getHeight() / 320.0f) * float(i / KEYPAD_COLS));
		_keypad[i]._width = (32.0f * float(Window::getWindow()->getWidth() / 320.0f));
		_keypad[i]._height = (32.0f * float(Window::getWindow()->getHeight() / 320.0f));
	}
}

void App::render(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, _bgColor.r, _bgColor.g, _bgColor.b, _bgColor.a);
	SDL_RenderClear(renderer);

	_grid->draw(renderer);
	for (unsigned i = 0; i < _inputHistory.size(); i++) {
		if (isValidEquation(_inputHistory[i])) {
			_nextFuncColor(i);
			SDL_SetRenderDrawColor(renderer, _funcColor.r, _funcColor.g, _funcColor.b, 255);
			_grid->drawFunction(renderer, _inputHistory[i]);
		}
	}

	_drawTextField(renderer);

	//_keypad
	for (unsigned i = 0; i < NUM_BUTTONS; i++) {
		_keypad[i].draw(renderer, _keypad_offset_x, _keypad_offset_y);
	}
	SDL_RenderPresent(renderer);
}

void App::_drawTextField(SDL_Renderer* renderer) const {
	//draw expression field
	SDL_FRect rec = { 0 };
	rec.x = (float)_tf_offset_x;
	rec.y = (float)_tf_offset_y;
	rec.w = (float)_tf_width;
	rec.h = (float)TEXTSIZE;

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRectF(renderer, &rec);
	SDL_SetRenderDrawColor(renderer, 155, 155, 155, 255);
	SDL_RenderDrawRectF(renderer, &rec);

	drawString(renderer, _textInput, _tf_offset_x, _tf_offset_y, _textInputColor, Window::getWindow()->getWidth() / 26, true);
	drawString(renderer, _inputHistory[0], _tf_offset_x, 0, {255,255,255,255}, Window::getWindow()->getWidth() / 26, true);
}

const std::string& App::getTextInput() const {
	return _textInput;
}

const std::vector<std::string>& App::getInputHistory() const {
	return _inputHistory;
}

void App::setTextInput(const std::string& text) {
	_textInput = text;
}