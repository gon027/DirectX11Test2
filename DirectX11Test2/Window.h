#pragma once

#include <Windows.h>
#include <string>

struct WindowSize {
	int width;
	int height;
};

struct WindowDevice {
	HINSTANCE hInstance;
	HWND hwnd;
	int cmdShow;
};

class Window {
public:
	Window(HINSTANCE _hInstance, int _cmdShow, std::string _windowName,int _width, int _height);
	~Window() = default;

	bool init();

	// ウインドウデバイスを取得
	const WindowDevice& getWindowDevice() const;

	// ウインドウサイズを取得
	const WindowSize& getWindowSize() const;

private:
	WindowDevice device;
	WindowSize windowSize;
	std::string windowName;
};