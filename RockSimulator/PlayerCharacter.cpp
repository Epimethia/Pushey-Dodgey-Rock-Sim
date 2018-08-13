#include "PlayerCharacter.h"
#include "Sprite.h"


PlayerCharacter::PlayerCharacter()
{
	m_Sprite = std::make_shared<Sprite>();
	m_Translate = glm::vec3(0.0f, 0.0f, 0.0f);
	m_RotationAxis = glm::vec3(0.0f, 0.0f, 1.0f);
	m_Scale = glm::vec3(1.0f, 1.0f, 1.0f);
	m_fRotation = 0.0f;
}


PlayerCharacter::~PlayerCharacter()
{
}

void PlayerCharacter::Render()
{
	m_Sprite->Render(glm::translate(glm::mat4(), m_Translate) 
				   * glm::rotate(glm::mat4(), m_fRotation, m_RotationAxis) 
		           * glm::scale(glm::mat4(), m_Scale));
}

void PlayerCharacter::Update()
{
}

void PlayerCharacter::Initialize()
{
	m_Sprite->Initialize("Resources/Images/AwesomeFace.png");
}
