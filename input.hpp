#ifndef INPUT_H
#define INPUT_H

#include <SDL.h>
#include <vector>

enum mouse_buttons
{
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

	int _numkeys;
	const Uint8* _keyStates;
	Uint8 _prevKeyStates[SDL_NUM_SCANCODES];

	void onMouseButtonDown(SDL_Event event);
	void onMouseButtonUp(SDL_Event event);
	void onMouseMotion(SDL_Event event);
public:
	Input();
	static Input* getInputHandler();
	void updatePrevKeyStates();
	bool update();
	bool getMouseButtonState(const int buttonNumber) const;
	SDL_Point getMousePosition() const;
	bool isKeyDown(SDL_Scancode event) const;
	bool isKeyReleased(SDL_Scancode key) const;
	bool isMouseKeyReleased(const int buttonNumber) const;
};

#endif