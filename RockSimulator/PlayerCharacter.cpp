#include "PlayerCharacter.h"
#include "Sprite.h"

#include "Dependencies/glm/gtx/string_cast.hpp"
#include "Dependencies/glm/gtx/rotate_vector.hpp"


PlayerCharacter::PlayerCharacter()
{
	m_Sprite = std::make_shared<Sprite>();
	m_Translate = glm::vec3(800.0f, 450.0f, 0.0f);
	m_RotationAxis = glm::vec3(0.0f, 0.0f, 1.0f);
	m_Scale = glm::vec3(50.0f, 50.0f, 1.0f);
	m_fRotation = 0.0f;
	m_ForwardVector = glm::vec3(0.0f, 1.0f, 0.0f);
	m_fVibrationRate = 0.0f;
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
	if (m_Translate.x < -50.0f) m_Translate.x = 1649.0f;
	if (m_Translate.x > 1650.0f) m_Translate.x = -49.0f;
	if (m_Translate.y < -49.0f) m_Translate.y = 949.0f;
	if (m_Translate.y > 950.0f) m_Translate.y = -49.0f;
	m_Translate += m_Velocity;
	m_fVibrationRate *= 0.90f;
}

//Update Overload
//Moves the player character by the input Translate
void PlayerCharacter::AddVelocity(float _Speed)
{
	m_Velocity *= 0.995f;
	m_Velocity += m_ForwardVector * _Speed * 0.1f;
	m_Velocity = glm::clamp(m_Velocity, glm::vec3(-10.0f), glm::vec3(10.0f));
	m_fVibrationRate = 3.0f;
}

void PlayerCharacter::Brake() {
	m_Velocity *= 0.98f;
	m_fVibrationRate = glm::length(m_Velocity);
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
