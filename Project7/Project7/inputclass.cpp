////////////////////////////////////////////////////////////////////////////////
// Filename: inputclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "inputclass.h"


InputClass::InputClass()
{
}


InputClass::InputClass(const InputClass& other)
{
}


InputClass::~InputClass()
{
}


bool InputClass::Initialize(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight)
{
	// ���콺 Ŀ���� ��ġ ������ ���� ȭ�� ũ�⸦ �����մϴ�.
	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;

	// Direct Input �������̽��� �ʱ�ȭ �մϴ�.
	HRESULT result = DirectInput8Create(hinstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_directInput, NULL);
	if (FAILED(result))
	{
		return false;
	}

	// Ű������ Direct Input �������̽��� �����մϴ�
	result = m_directInput->CreateDevice(GUID_SysKeyboard, &m_keyboard, NULL);
	if (FAILED(result))
	{
		return false;
	}

	// ������ ������ �����Ͻʽÿ�. �� ��� Ű�����̹Ƿ� ���� ���ǵ� ������ ������ ����� �� �ֽ��ϴ�.
	result = m_keyboard->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(result))
	{
		return false;
	}

	// �ٸ� ���α׷��� �������� �ʵ��� Ű������ ���� ������ �����մϴ�
	result = m_keyboard->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	if (FAILED(result))
	{
		return false;
	}

	// Ű���带 �Ҵ�޴´�
	result = m_keyboard->Acquire();
	if (FAILED(result))
	{
		return false;
	}

	// ���콺 Direct Input �������̽��� �����մϴ�.
	result = m_directInput->CreateDevice(GUID_SysMouse, &m_mouse, NULL);
	if (FAILED(result))
	{
		return false;
	}

	// �̸� ���� �� ���콺 ������ ������ ����Ͽ� ���콺�� ������ ������ �����մϴ�.
	result = m_mouse->SetDataFormat(&c_dfDIMouse);
	if (FAILED(result))
	{
		return false;
	}

	// �ٸ� ���α׷��� ���� �� �� �ֵ��� ���콺�� ���� ������ �����մϴ�.
	result = m_mouse->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	if (FAILED(result))
	{
		return false;
	}

	// ���콺�� �Ҵ�޴´�
	result = m_mouse->Acquire();
	if (FAILED(result))
	{
		return false;
	}

	return true;
}


void InputClass::Shutdown()
{
	// ���콺�� ��ȯ�մϴ�.
	if (m_mouse)
	{
		m_mouse->Unacquire();
		m_mouse->Release();
		m_mouse = 0;
	}

	// Ű���带 ��ȯ�մϴ�.
	if (m_keyboard)
	{
		m_keyboard->Unacquire();
		m_keyboard->Release();
		m_keyboard = 0;
	}

	// m_directInput ��ü�� ��ȯ�մϴ�.
	if (m_directInput)
	{
		m_directInput->Release();
		m_directInput = 0;
	}
}

bool InputClass::Frame()
{
	// Ű������ ���� ���¸� �д´�.
	if (!ReadKeyboard())
	{
		return false;
	}

	// ���콺�� ���� ���¸� �д´�.
	if (!ReadMouse())
	{
		return false;
	}

	// Ű����� ���콺�� ������¸� ó���մϴ�.
	ProcessInput();

	return true;
}

bool InputClass::ReadKeyboard()
{
	// Ű���� ����̽��� ��´�.
	HRESULT result = m_keyboard->GetDeviceState(sizeof(m_keyboardState), (LPVOID)&m_keyboardState);
	if (FAILED(result))
	{
		// Ű���尡 ��Ŀ���� �Ҿ��ų� ȹ����� ���� ��� ��Ʈ���� �ٽ� ���� �´�
		if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
		{
			m_keyboard->Acquire();
		}
		else
		{
			return false;
		}
	}

	return true;
}

bool InputClass::ReadMouse()
{
	// ���콺 ����̽��� ��´�.
	HRESULT result = m_mouse->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&m_mouseState);
	if (FAILED(result))
	{
		// ���콺�� ��Ŀ���� �Ҿ��ų� ȹ����� ���� ��� ��Ʈ���� �ٽ� ���� �´�
		if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
		{
			m_mouse->Acquire();
		}
		else
		{
			return false;
		}
	}

	return true;
}

void InputClass::ProcessInput()
{
	// ������ ���� ���콺 ��ġ�� ������ ������� ���콺 Ŀ���� ��ġ�� ������Ʈ �մϴ�.
	m_mouseX += m_mouseState.lX;
	m_mouseY += m_mouseState.lY;

	// ���콺 ��ġ�� ȭ�� �ʺ� �Ǵ� ���̸� �ʰ����� �ʴ��� Ȯ���Ѵ�.
	if (m_mouseX < 0) { m_mouseX = 0; }
	if (m_mouseY < 0) { m_mouseY = 0; }

	if (m_mouseX > m_screenWidth) { m_mouseX = m_screenWidth; }
	if (m_mouseY > m_screenHeight) { m_mouseY = m_screenHeight; }
}

bool InputClass::IsEscapePressed()
{
	// escape Ű�� ���� �������� �ִ��� bit���� ����Ͽ� Ȯ���Ѵ�.
	if (m_keyboardState[DIK_ESCAPE] & 0x80)
	{
		return true;
	}

	return false;
}


bool InputClass::IsWKeyPressed()
{
	if (m_keyboardState[DIK_W] & 0x80)
	{
		return true;
	}

	return false;
}

bool InputClass::IsAKeyPressed()
{
	if (m_keyboardState[DIK_A] & 0x80)
	{
		return true;
	}

	return false;
}

bool InputClass::IsSKeyPressed()
{
	if (m_keyboardState[DIK_S] & 0x80)
	{
		return true;
	}

	return false;
}

bool InputClass::IsDKeyPressed()
{
	if (m_keyboardState[DIK_D] & 0x80)
	{
		return true;
	}

	return false;
}

bool InputClass::IsUpArrowKeyPressed()
{
	if (m_keyboardState[DIK_UP] & 0x80)
	{
		return true;
	}

	return false;
}

bool InputClass::IsDownArrowKeyPressed()
{
	if (m_keyboardState[DIK_DOWN] & 0x80)
	{
		return true;
	}

	return false;
}

bool InputClass::IsLeftArrowKeyPressed()
{
	if (m_keyboardState[DIK_LEFT] & 0x80)
	{
		return true;
	}

	return false;
}

bool InputClass::IsRightArrowKeyPressed()
{
	if (m_keyboardState[DIK_RIGHT] & 0x80)
	{
		return true;
	}

	return false;
}
