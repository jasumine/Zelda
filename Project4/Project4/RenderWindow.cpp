#include "RenderWindow.h"

bool RenderWindow::Initialize(HINSTANCE hInstance, string window_title, string window_class, int width, int height)
{
	this->hInstance = hInstance;
	this->width = width;
	this->height = height;
	this->window_title = window_title;
	this->window_title_wide = StringConverter::StringToWide(this->window_title);
	this->window_class = window_class;
	this->window_class_wide = StringConverter::StringToWide(this->window_class); // wide string represent of class

	this->RegisterWindowClass();

	this->handle = CreateWindowEx(0, // Extended Windows style - we are using the default,.
		this->window_class_wide.c_str(), // Window class name
		this->window_title_wide.c_str(), // Window title
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, // Windows sytle
		0, // Window X Positon
		0, // Window Y Positon
		this->width, // Window width
		this->height, // Window height
		NULL, // Handle to parent of this window. Since this is the first window, it has no parent window.
		NULL, // Handle to menu or chile windo widentifier. Can be set to NULL and use menu in WindowClassEX ~~
		this->hInstance, // Handle to the instance of module to be used with this window
		nullptr); // Param to create window

	if (this->handle == NULL)
	{
		ErrorLogger::Log(GetLastError(), "CreateWindowEx failed for window: " + this->window_title);
		return false;
	}

	// Bring the window up on the screen and set it as main focus.
	ShowWindow(this->handle, SW_SHOW);
	SetForegroundWindow(this->handle);
	SetFocus(this->handle);

	return true;
}

// 실행중이면 true, quit하면 false를 반환
bool RenderWindow::ProcessMessages()
{
	// Handle the windows messages.
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG)); // Initialize the message structur.

	if (PeekMessage(&msg, // Where to store message (if one exists) 
		this->handle, // Handle to window we are checking messages for
		0, // Minimum Filter Msg Value - We are not filtering for specific messages, but the min/max could be used.
		0, // Maximum Filter Masg Value
		PM_REMOVE)) // Remove message after cpturing it via PeekMessage. For mor argument options, 
	{
		TranslateMessage(&msg); // Translate message from virtul key messages into character messages
		DispatchMessage(&msg); // Dispatch message to our Window Proc for this window. 
	}

	// Check if the window was closed
	if (msg.message == WM_QUIT)
	{
		if (!IsWindow(this->handle))
		{
			this->handle = NULL; // Message processing loop takes care of destroying this window
			UnregisterClass(this->window_class_wide.c_str(), this->hInstance);
			return false;
		}
	}

	return true;
}


RenderWindow::~RenderWindow()
{
	// create window 면 실행함
	if (this->handle != NULL)
	{
		UnregisterClass(this->window_class_wide.c_str(), this->hInstance);
		DestroyWindow(handle);
	}
}



void RenderWindow::RegisterWindowClass()
{
	WNDCLASSEX wc; // our window class (this has to be filed before our window can be created)
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC; // Flags [Redraw on width/height change from resize/movemend]
	wc.lpfnWndProc = DefWindowProc; // Pointer to window Proce function ofr handling messages from this window
	wc.cbClsExtra = 0; // # of extra bytes to allocate following the window-class structure. we are no currently using this
	wc.cbWndExtra = 0; // # of extra bytes to allocate following the window instance. we are no currently using this
	wc.hInstance = this->hInstance; // handle to the instance that contains the window procedure
	wc.hIcon = NULL; // handle to the class icon. must be a handle to an icon resource.
	wc.hIconSm = NULL; // handle to small icon for this class.
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); // Default Cursor - If we leave this null, we have to explicitly set ~~
	wc.hbrBackground = NULL; // Handle to the class backgrouond brush for the window's backgroudn color
	wc.lpszMenuName = NULL; // Pointer to a null terminated character string for the menu
	wc.lpszClassName = this->window_class_wide.c_str(); // Pointer to null terminated string of our class name for this ~~
	wc.cbSize = sizeof(WNDCLASSEX); // Need to fill in the size of our struct for cbSize
	RegisterClassEx(&wc); // Register the class so that it is usable.

}