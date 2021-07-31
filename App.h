#pragma once
#include "Window.h"
#include "WindowTimer.h"
#include <optional>

class App {
public:
	App();
	int Go();
private:
	void DoFrame();
private:
	Window wnd;
	WindowTimer timer;
};