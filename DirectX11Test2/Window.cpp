#include "Window.h"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, msg, wp, lp);
}

Window::Window(HINSTANCE _hInstance, int _cmdShow, std::string _windowName, int _width, int _height)
	: device({ _hInstance, nullptr, _cmdShow })
	, windowSize({ _width, _height })
	, windowName(_windowName)
{
}

bool Window::init()
{
	WNDCLASSEX wc{
			sizeof(WNDCLASSEX),
			CS_CLASSDC,
			WindowProc,
			0L,
			0L,
			device.hInstance,
			NULL,
			NULL,
			NULL,
			NULL,
			__TEXT("DirectX11 Template"),
			NULL
	};

	if (!RegisterClassEx(&wc)) {
		return false;
	}

	RECT rc{
		0, 0, windowSize.width, windowSize.height
	};

	device.hwnd = CreateWindow(
		wc.lpszClassName,
		wc.lpszClassName,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		rc.right - rc.left,
		rc.bottom - rc.top,
		NULL,
		NULL,
		device.hInstance,
		NULL
	);

	if (!device.hwnd) {
		return false;
	}

	ShowWindow(device.hwnd, device.cmdShow);
	UpdateWindow(device.hwnd);

	return true;
}

const WindowDevice& Window::getWindowDevice() const
{
	return device;
}

const WindowSize& Window::getWindowSize() const
{
	return windowSize;
}
