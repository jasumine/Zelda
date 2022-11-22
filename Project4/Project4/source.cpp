#include "RenderWindow.h"
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "DirectXTK.lib")

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR lpCmdLine,
	_In_ int nCmdShow)
{
	RenderWindow rw;
	rw.Initialize(hInstance, "Title", "MyWindowClass", 800, 600);
	while (rw.ProcessMessages() == true)
	{
		
	}

/*	messagebox 쓰는 방법
	HRESULT hr = S_OK;;
	if (SUCCEEDED(hr))
	{
		MessageBoxA(NULL, "SUCCESS", "SUCCESS", NULL);
	}
	if (FAILED(hr))
	{
		ErrorLogger::Log(hr, "FAILURE");
	}*/
	return 0;
}
