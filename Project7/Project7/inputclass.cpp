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


void InputClass::Initialize()
{
	int i;
	

	// Initialize all the keys to being released and not pressed.
	for(i=0; i<256; i++)
	{
		m_keys[i] = false;
	}

	return;
}


void InputClass::KeyDown(unsigned int input)
{
	// If a key is pressed then save that state in the key array.
	m_keys[input] = true;
	return;
}


void InputClass::KeyUp(unsigned int input)
{
	// If a key is released then clear that state in the key array.
	m_keys[input] = false;
	return;
}


bool InputClass::IsKeyDown(unsigned int key)
{
	// Return what state the key is in (pressed/not pressed).
	return m_keys[key];
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
