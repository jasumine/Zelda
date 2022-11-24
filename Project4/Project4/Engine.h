#pragma once
#include "WindowContainer.h"

class Engine : WindowContainer
{
public:
	bool Initialize(HINSTANCE hInstance, string window_title, string window_class, int widht, int height);
	bool ProcessMessages(); // render window
};

