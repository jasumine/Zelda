
#include "PositionClass.h"


PositionClass::PositionClass()
{
}


PositionClass::PositionClass(const PositionClass& other)
{
}


PositionClass::~PositionClass()
{
}


void PositionClass::SetFrameTime(float time)
{
	m_frameTime = time;
}

// Position 
void PositionClass::GetPositionX(float& x)
{
	x = m_positionX;
}

void PositionClass::GetPositionZ(float& z)
{
	z = m_positionZ;
}

// Rotation
void PositionClass::GetRotationX(float& x)
{
	x = m_rotationX;
}

void PositionClass::GetRotationY(float& y)
{
	y = m_rotationY;
}

// Move
void PositionClass::MoveUp(bool keydown)
{
	if (keydown)
	{
		m_positionZ -= 0.5f;
	}

}

void PositionClass::MoveDown(bool keydown)
{
	if (keydown)
	{
		m_positionZ += 0.5f;
	}

}

void PositionClass::MoveLeft(bool keydown)
{
	if (keydown)
	{
		m_positionX -= 0.5f;
	}

}

void PositionClass::MoveRight(bool keydown)
{
	if (keydown)
	{
		m_positionX += 0.5f;
	}

}

// Turn

void PositionClass::TurnUp(bool keydown)
{
	if (keydown)
	{
		m_turnUpSpeed += m_frameTime * 0.005f;

		if (m_turnUpSpeed > (m_frameTime * 0.1f))
		{
			m_turnUpSpeed = m_frameTime * 0.1f;
		}
	}
	else
	{
		m_turnUpSpeed -= m_frameTime * 0.005f;

		if (m_turnUpSpeed < 0.0f)
		{
			m_turnUpSpeed = 0.0f;
		}
	}

	m_rotationX += m_turnUpSpeed;
	if (m_rotationX < 0.0f)
	{
		m_rotationX -= 360.0f;
	}
}

void PositionClass::TurnDown(bool keydown)
{
	if (keydown)
	{
		m_turnDownSpeed += m_frameTime * 0.005f;

		if (m_turnDownSpeed > (m_frameTime * 0.1f))
		{
			m_turnDownSpeed = m_frameTime * 0.1f;
		}
	}
	else
	{
		m_turnDownSpeed -= m_frameTime * 0.005f;

		if (m_turnDownSpeed < 0.0f)
		{
			m_turnDownSpeed = 0.0f;
		}
	}

	m_rotationX -= m_turnDownSpeed;
	if (m_rotationX < 0.0f)
	{
		m_rotationX += 360.0f;
	}
}

void PositionClass::TurnLeft(bool keydown)
{
	// 키를 누르면 카메라가 왼쪽으로 돌아는 속도가 증가합니다. 회전 속도를 늦추지 않으면.
	if (keydown)
	{
		m_turnLeftSpeed += m_frameTime * 0.005f;

		if (m_turnLeftSpeed > (m_frameTime * 0.1f))
		{
			m_turnLeftSpeed = m_frameTime * 0.1f;
		}
	}
	else
	{
		m_turnLeftSpeed -= m_frameTime * 0.005f;

		if (m_turnLeftSpeed < 0.0f)
		{
			m_turnLeftSpeed = 0.0f;
		}
	}

	// 회전 속도를 사용하여 회전을 업데이트합니다.
	m_rotationY -= m_turnLeftSpeed;
	if (m_rotationY < 0.0f)
	{
		m_rotationY += 360.0f;
	}
}

void PositionClass::TurnRight(bool keydown)
{
	// 키를 누르면 카메라가 오른쪽으로 회전하는 속도가 증가합니다. 회전 속도를 늦추지 않으면.
	if (keydown)
	{
		m_turnRightSpeed += m_frameTime * 0.005f;

		if (m_turnRightSpeed > (m_frameTime * 0.1f))
		{
			m_turnRightSpeed = m_frameTime * 0.1f;
		}
	}
	else
	{
		m_turnRightSpeed -= m_frameTime * 0.005f;

		if (m_turnRightSpeed < 0.0f)
		{
			m_turnRightSpeed = 0.0f;
		}
	}

	// 회전 속도를 사용하여 회전을 업데이트합니다.
	m_rotationY += m_turnRightSpeed;
	if (m_rotationY > 360.0f)
	{
		m_rotationY -= 360.0f;
	}
}