//	This include.
#include "healthbar.h"


//	Library includes.


//	Local includes.
#include "Sprite.h"


C_HealthBar::C_HealthBar()
{
	m_Sprite = std::make_shared<Sprite>();
}

C_HealthBar::~C_HealthBar()
{

}

C_HealthBar::C_HealthBar(const char* _Filepath)
{
	m_Sprite = std::make_shared<Sprite>();
	m_Sprite->Initialize(_Filepath);
}

void
C_HealthBar::SetSprite(const char* _Filepath)
{
	m_Sprite->Initialize(_Filepath);
}

void
C_HealthBar::SetPosition(glm::vec3& _Position)
{
	m_vPosition = _Position;
}

void
C_HealthBar::SetScale(glm::vec3& _Scale)
{
	m_vScale = _Scale;
}

void
C_HealthBar::SetRotation(float& _Angle)
{
	m_fRotationAngle = _Angle;
}

void
C_HealthBar::SetRotation(glm::vec3& _Axis)
{
	m_vRotationAxis = _Axis;
}

void
C_HealthBar::SetRotation(float& _Angle, glm::vec3& _Axis)
{
	m_fRotationAngle = _Angle;
	m_vRotationAxis = _Axis;
}

glm::vec3&
C_HealthBar::GetScale()
{
	return m_vScale;
}

void
C_HealthBar::Render()
{
	m_Sprite->Render(
		glm::translate(glm::mat4(), m_vPosition) *
		glm::rotate(glm::mat4(), 0.0f, m_vRotationAxis) *
		glm::scale(glm::mat4(), m_vScale));
}