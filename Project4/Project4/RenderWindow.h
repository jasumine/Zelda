#pragma once
#include "ErrorLogger.h"

class WindowContainer;

using namespace std;

class RenderWindow
{
public:
	bool Initialize(WindowContainer* pWindowContainer, HINSTANCE hInstance, string window_title, string window_class, int widht, int height);
	bool ProcessMessages();
	~RenderWindow();

private:
	void RegisterWindowClass(); // 초기화 함수가 대신 역할한다.
	HWND handle = NULL; // Handle to this window
	HINSTANCE hInstance = NULL; // Handle to application instance
	string window_title = "";
	wstring window_title_wide = L""; // Wide string representation of window title
	string window_class = "";
	wstring window_class_wide = L""; // Wide string representation of window class naem
	int width = 0;
	int height = 0;
};