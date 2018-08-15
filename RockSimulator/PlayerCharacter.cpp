#include "PlayerCharacter.h"
#include "Sprite.h"

#include "Dependencies/glm/gtx/string_cast.hpp"
#include "Dependencies/glm/gtx/rotate_vector.hpp"


PlayerCharacter::PlayerCharacter()
{
	m_Sprite = std::make_shared<Sprite>();
	m_Translate = glm::vec3(0.0f, 0.0f, 0.0f);
	m_RotationAxis = glm::vec3(0.0f, 0.0f, 1.0f);
	m_Scale = glm::vec3(1.0f, 1.0f, 1.0f);
	m_fRotation = 0.0f;
	m_ForwardVector = glm::vec3(0.0f, 1.0f, 0.0f);
}


PlayerCharacter::~PlayerCharacter()
{
}

void PlayerCharacter::Render()
{
	m_Sprite->Render(
		glm::translate(glm::mat4(), m_Translate) * 
		glm::rotate(glm::mat4(), m_fRotation, m_RotationAxis) * 
		glm::scale(glm::mat4(), m_Scale)
	);
}

void PlayerCharacter::Update()
{
	std::cout << glm::to_string(m_Translate) << std::endl;
	if (m_Translate.x < -10.0f) m_Translate.x = 10.0f;
	if (m_Translate.x > 10.0f) m_Translate.x = -10.0f;
	if (m_Translate.y < -10.0f) m_Translate.y = 10.0f;
	if (m_Translate.y > 10.0f) m_Translate.y = -10.0f;
	m_Translate += m_Velocity;
}

//Update Overload
//Moves the player character by the input Translate
void PlayerCharacter::AddVelocity(float _Speed)
{
	m_Velocity += m_ForwardVector * _Speed * 0.1f;
	m_Velocity = glm::clamp(m_Velocity, glm::vec3(-0.3f), glm::vec3(0.3f));
}

void PlayerCharacter::AddRotation(float _Angle)
{
	m_ForwardVector = glm::rotateZ(m_ForwardVector, _Angle);
	m_fRotation += _Angle;
}

void PlayerCharacter::Initialize()
{
	m_Sprite->Initialize("Resources/Images/AwesomeFace.png");
}
