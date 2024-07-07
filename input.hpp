#ifndef INPUT_H
#define INPUT_H

#include <SDL.h>
#include <vector>
#include "window.hpp"

enum mouse_buttons {
	LEFT = 0,
	MIDDLE = 1,
	RIGHT = 2
};

class Input {
private:
	static Input* _input;

	std::vector<bool> _mouseButtonStates;
	std::vector<bool> _prevMouseButtonStates;

	SDL_Point _mPos;

	const Uint8* _keyStates;
	Uint8 _prevKeyStates[SDL_NUM_SCANCODES];
	int _numkeys;

	void onMouseButtonDown(const SDL_Event& event);	// private all these
	void onMouseButtonUp(const SDL_Event& event);
	void onMouseMotion(const SDL_Event& event);
public:
	Input();
	static Input* getInputHandler();
	void updatePrevKeyStates();
	bool update();
	bool getMouseButtonState(const int& buttonNumber) const;
	SDL_Point getMousePosition() const;
	bool isKeyDown(const SDL_Scancode& key) const;
	bool isKeyReleased(const SDL_Scancode& key) const;
	bool isMouseKeyReleased(const int& buttonNumber) const;
};

#endif