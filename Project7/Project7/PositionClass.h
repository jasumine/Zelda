#pragma once

class PositionClass
{
public:
	PositionClass();
	PositionClass(const PositionClass&);
	~PositionClass();

	void SetFrameTime(float);
	void GetPositionX(float&);
	void GetPositionZ(float&);
	
	void GetRotationX(float&);
	void GetRotationY(float&);

	void MoveUp(bool);
	void MoveDown(bool);
	void MoveLeft(bool);
	void MoveRight(bool);

	void TurnUp(bool);
	void TurnDown(bool);
	void TurnLeft(bool);
	void TurnRight(bool);

private:
	float m_frameTime = 0.0f;

	float m_positionX = 0.0f;
	float m_positionZ = 0.0f;

	float m_rotationX = 0.0f;
	float m_rotationY = 0.0f;

	float m_moveUpSpeed = 0.0f;
	float m_moveDownSpeed = 0.0f;
	float m_moveLeftSpeed = 0.0f;
	float m_moveRightSpeed = 0.0f;

	float m_turnUpSpeed = 0.0f;
	float m_turnDownSpeed = 0.0f;
	float m_turnLeftSpeed = 0.0f;
	float m_turnRightSpeed = 0.0f;
};