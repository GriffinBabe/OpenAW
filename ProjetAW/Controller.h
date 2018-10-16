#pragma once
#include "window.h"

class Controller {
	/*
		Will read the inputs (mouse and keyboard) and call the right functions in the model
	*/

private:
	Window* window;
public:
	Controller(Window* w);
};