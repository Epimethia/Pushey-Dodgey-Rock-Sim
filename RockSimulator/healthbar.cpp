//	This include.
#include "healthbar.h"


//	Library includes.


//	Local includes.
#include "Sprite.h"


C_HealthBar::C_HealthBar()
{
	m_HealthBarFull = std::make_shared<Sprite>();
	m_HealthBarHalf = std::make_shared<Sprite>();
	m_Sprite = m_HealthBarFull;

}

C_HealthBar::~C_HealthBar()
{
	m_HealthBarFull.reset();
	m_HealthBarHalf.reset();
	m_Sprite.reset();
}

C_HealthBar::C_HealthBar(const char * _Filepath_Full, const char*  _Filepath_Half)
{
	m_HealthBarFull = std::make_shared<Sprite>();
	m_HealthBarHalf = std::make_shared<Sprite>();
	m_HealthBarFull->Initialize(_Filepath_Full);
	m_HealthBarHalf->Initialize(_Filepath_Half);
	m_Sprite = m_HealthBarFull;

}

void
C_HealthBar::SetHealth(HEALTH _HealthVal)
{
	switch (_HealthVal)
	{
		case FULL:
			m_Sprite = m_HealthBarFull;
			break;
		case HALF:
			m_Sprite = m_HealthBarHalf;
			break;
		default:break;
	}
	
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
C_HealthBar::Render()
{
	m_Sprite->Render(
		glm::translate(glm::mat4(), m_vPosition) *
		glm::scale(glm::mat4(), m_vScale));
}