////////////////////////////////////////////////////////////////////////////////
// Filename: systemclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "systemclass.h"


SystemClass::SystemClass()
{
}


SystemClass::SystemClass(const SystemClass& other)
{
}


SystemClass::~SystemClass()
{
}


bool SystemClass::Initialize()
{
	// Initialize the width and height of the screen to zero before sending the variables into the function.
	int screenWidth = 0;
	int screenHeight = 0;

	// Initialize the windows api.
	InitializeWindows(screenWidth, screenHeight);

	// Create the input object.  This object will be used to handle reading the keyboard input from the user.
	m_Input = new InputClass;
	if(!m_Input)
	{
		return false;
	}

	// Initialize the input object.
	// m_Input ��ü �ʱ�ȭ
	if (!m_Input->Initialize(m_hinstance, m_hwnd, screenWidth, screenHeight))
	{
		MessageBox(m_hwnd, L"Could not initialize the input object.", L"Error", MB_OK);
		return false;
	}

	// Create the graphics object.  This object will handle rendering all the graphics for this application.
	m_Graphics = new GraphicsClass;
	if(!m_Graphics)
	{
		return false;
	}

	// Initialize the graphics object.
	if (!m_Graphics->Initialize(screenWidth, screenHeight, m_hwnd))
	{
		return false;
	}

	// Create the fps object.
	m_Fps = new FpsClass;
	if (!m_Fps)
	{
		return false;
	}

	// Initialize the fps object.
	m_Fps->Initialize();

	// Create the cpu object.
	m_Cpu = new CpuClass;
	if (!m_Cpu)
	{
		return false;
	}

	// Initialize the cpu object.
	m_Cpu->Initialize();


	// Ÿ�̸� ��ü�� ����ϴ�.
	m_Timer = new TimerClass;
	if (!m_Timer)
	{
		return false;
	}

	// Ÿ�̸� ��ü�� �ʱ�ȭ�մϴ�.
	if (!m_Timer->Initialize())
	{
		MessageBox(m_hwnd, L"Could not initialize the Timer object.", L"Error", MB_OK);
		return false;
	}

	// ��ġ ��ü�� �����մϴ�.
	m_Position = new PositionClass;
	if (!m_Position)
	{
		return false;
	}

	return true;

}


void SystemClass::Shutdown()
{
	// ��ġ ��ü ��ȯ
	if (m_Position)
	{
		delete m_Position;
		m_Position = 0;
	}

	// Ÿ�̸� ��ü�� �����մϴ�.
	if (m_Timer)
	{
		delete m_Timer;
		m_Timer = 0;
	}

	// Release the graphics object.
	if(m_Graphics)
	{
		m_Graphics->Shutdown();
		delete m_Graphics;
		m_Graphics = 0;
	}

	// Release the input object.
	if(m_Input)
	{
		m_Input->Shutdown();
		delete m_Input;
		m_Input = 0;
	}

	// Release the cpu object.
	if (m_Cpu)
	{
		m_Cpu->Shutdown();
		delete m_Cpu;
		m_Cpu = 0;
	}

	// Release the fps object.
	if (m_Fps)
	{
		delete m_Fps;
		m_Fps = 0;
	}

	// Shutdown the window.
	ShutdownWindows();
	
	return;
}


void SystemClass::Run()
{// �޽��� ����ü ���� �� �ʱ�ȭ
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	// ����ڷκ��� ���� �޽����� ���������� �޽��������� ���ϴ�
	while (true)
	{
		// ������ �޽����� ó���մϴ�
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			// ���� �޽����� ���� ��� �޽��� ������ Ż���մϴ�
			if (msg.message == WM_QUIT)
				break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			// �� �ܿ��� Frame �Լ��� ó���մϴ�.
			if (!Frame())
			{
				MessageBox(m_hwnd, L"Frame Processing Failed", L"Error", MB_OK);
				break;
			}
		}

		// ����ڰ� ESCŰ�� �������� Ȯ�� �� ���� ó����
		if (m_Input->IsEscapePressed() == true)
		{
			break;
		}
	}
}


bool SystemClass::Frame()
{
	// �ý��� ��踦 ������Ʈ �մϴ�
	m_Timer->Frame();
	m_Fps->Frame();
	m_Cpu->Frame();

	// �Է� ������ ó���� �����մϴ�
	if (!m_Input->Frame())
	{
		return false;
	}

	// ������Ʈ �� ��ġ�� ����ϱ� ���� ������ �ð��� �����մϴ�.
	m_Position->SetFrameTime(m_Timer->GetTime());


	// Move
	bool keyDown = m_Input->IsWKeyPressed();
	m_Position->MoveUp(keyDown);
	keyDown = m_Input->IsAKeyPressed();
	m_Position->MoveDown(keyDown);
	keyDown = m_Input->IsSKeyPressed();
	m_Position->MoveLeft(keyDown);
	keyDown = m_Input->IsDKeyPressed();
	m_Position->MoveRight(keyDown);

	// Turn

	keyDown = m_Input->IsUpArrowKeyPressed();
	m_Position->TurnUp(keyDown);
	keyDown = m_Input->IsDownArrowKeyPressed();
	m_Position->TurnDown(keyDown);
	keyDown = m_Input->IsLeftArrowKeyPressed();
	m_Position->TurnLeft(keyDown);
	keyDown = m_Input->IsRightArrowKeyPressed();
	m_Position->TurnRight(keyDown);

	// ���� �� ����Ʈ ȸ���� �����ɴϴ�.
	float positionX = 0.0f;
	m_Position->GetPositionX(positionX);

	float positionZ = 0.0f;
	m_Position->GetPositionZ(positionZ);

	float rotationX = 0.0f;
	m_Position->GetRotationX(rotationX);

	float rotationY = 0.0f;
	m_Position->GetRotationY(rotationY);


// �׷��� ��ü�� ���� ������ ó���� �����մϴ�.
	if (!m_Graphics->Frame(positionX, positionZ, rotationX,rotationY, m_Fps->GetFps(), m_Cpu->GetCpuPercentage()))
	{
		return false;
	}

	return m_Graphics->Render();
}


LRESULT CALLBACK SystemClass::MessageHandler(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
{
	return DefWindowProc(hwnd, umsg, wparam, lparam);
}


void SystemClass::InitializeWindows(int& screenWidth, int& screenHeight)
{
	// �ܺ� �����͸� �� ��ü�� �����մϴ�
	ApplicationHandle = this;

	// �� ���α׷��� �ν��Ͻ��� �����ɴϴ�
	m_hinstance = GetModuleHandle(NULL);

	// ���α׷� �̸��� �����մϴ�
	m_applicationName = L"Framework";

	// windows Ŭ������ �Ʒ��� ���� �����մϴ�.
	WNDCLASSEX wc;
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = m_hinstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm = wc.hIcon;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = m_applicationName;
	wc.cbSize = sizeof(WNDCLASSEX);

	// windows class�� ����մϴ�
	RegisterClassEx(&wc);

	// ����� ȭ���� �ػ󵵸� �о�ɴϴ�
	screenWidth = GetSystemMetrics(SM_CXSCREEN);
	screenHeight = GetSystemMetrics(SM_CYSCREEN);

	int posX = 0;
	int posY = 0;

	// FULL_SCREEN ���� ���� ���� ȭ���� �����մϴ�.
	if (FULL_SCREEN)
	{
		// Ǯ��ũ�� ���� �����ߴٸ� ����� ȭ�� �ػ󵵸� ����ũ�� �ػ󵵷� �����ϰ� ������ 32bit�� �����մϴ�.
		DEVMODE dmScreenSettings;
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = (unsigned long)screenWidth;
		dmScreenSettings.dmPelsHeight = (unsigned long)screenHeight;
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// Ǯ��ũ������ ���÷��� ������ �����մϴ�.
		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);
	}
	else
	{
		// ������ ����� ��� 1600 * 900 ũ�⸦ �����մϴ�.
		screenWidth = 1600;
		screenHeight = 900;

		// ������ â�� ����, ������ �� ��� ������ �մϴ�.
		posX = (GetSystemMetrics(SM_CXSCREEN) - screenWidth) / 2;
		posY = (GetSystemMetrics(SM_CYSCREEN) - screenHeight) / 2;
	}

	// �����츦 �����ϰ� �ڵ��� ���մϴ�.
	m_hwnd = CreateWindowEx(WS_EX_APPWINDOW, m_applicationName, m_applicationName,
		WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP,
		posX, posY, screenWidth, screenHeight, NULL, NULL, m_hinstance, NULL);

	// �����츦 ȭ�鿡 ǥ���ϰ� ��Ŀ���� �����մϴ�
	ShowWindow(m_hwnd, SW_SHOW);
	SetForegroundWindow(m_hwnd);
	SetFocus(m_hwnd);
}


void SystemClass::ShutdownWindows()
{
	// Ǯ��ũ�� ��忴�ٸ� ���÷��� ������ �ʱ�ȭ�մϴ�.
	if (FULL_SCREEN)
	{
		ChangeDisplaySettings(NULL, 0);
	}

	// â�� �����մϴ�
	DestroyWindow(m_hwnd);
	m_hwnd = NULL;

	// ���α׷� �ν��Ͻ��� �����մϴ�
	UnregisterClass(m_applicationName, m_hinstance);
	m_hinstance = NULL;

	// �ܺ������� ������ �ʱ�ȭ�մϴ�
	ApplicationHandle = NULL;
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam)
{
	switch(umessage)
	{
		// Check if the window is being destroyed.
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}

		// Check if the window is being closed.
		case WM_CLOSE:
		{
			PostQuitMessage(0);		
			return 0;
		}

		// All other messages pass to the message handler in the system class.
		default:
		{
			return ApplicationHandle->MessageHandler(hwnd, umessage, wparam, lparam);
		}
	}
}