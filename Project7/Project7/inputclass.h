////////////////////////////////////////////////////////////////////////////////
// Filename: inputclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _INPUTCLASS_H_
#define _INPUTCLASS_H_

#include <dinput.h>

////////////////////////////////////////////////////////////////////////////////
// Class name: InputClass
////////////////////////////////////////////////////////////////////////////////
class InputClass
{
public:
	InputClass();
	InputClass(const InputClass&);
	~InputClass();

	void Initialize();

	void KeyDown(unsigned int);
	void KeyUp(unsigned int);
	bool IsKeyDown(unsigned int);


	bool IsWKeyPressed();
	bool IsAKeyPressed();
	bool IsSKeyPressed();
	bool IsDKeyPressed();

	bool IsUpArrowKeyPressed();
	bool IsDownArrowKeyPressed();
	bool IsLeftArrowKeyPressed();
	bool IsRightArrowKeyPressed();

private:
	bool m_keys[256];
	IDirectInputDevice8* m_keyboard = nullptr;

	unsigned char m_keyboardState[256] = { 0, };
};

#endif