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

	// �E�C���h�E�f�o�C�X���擾
	const WindowDevice& getWindowDevice() const;

	// �E�C���h�E�T�C�Y���擾
	const WindowSize& getWindowSize() const;

private:
	WindowDevice device;
	WindowSize windowSize;
	std::string windowName;
};