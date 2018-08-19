#include "PlayerCharacter.h"
#include "Sprite.h"
#include "Physics.h"
#include "Dependencies/glm/gtx/string_cast.hpp"
#include "Dependencies/glm/gtx/rotate_vector.hpp"


PlayerCharacter::PlayerCharacter()
{
	m_Sprite = std::make_shared<Sprite>();	
	m_Scale = glm::vec3(10.0f, 10.0f, 1.0f);
	m_RotationAxis = glm::vec3(0.0f, 0.0f, 1.0f);
	m_fVibrationRate = 0.0f;

	// Physics
	b2FixtureDef fixtureDef;
	b2PolygonShape dynamicBox;
	m_bodyDef.type = b2_dynamicBody;
	m_bodyDef.position.Set(200.0f, 112.5f);
	m_body = Physics::GetInstance()->CreateBody(m_bodyDef);
	dynamicBox.SetAsBox(2.0f, 2.0f);
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 0.1f;
	fixtureDef.friction = 0.3f;
	m_body->CreateFixture(&fixtureDef);
}


PlayerCharacter::~PlayerCharacter()
{
}

void PlayerCharacter::Render()
{		
	m_Sprite->Render(
		glm::translate(glm::mat4(), glm::vec3(m_body->GetPosition().x, m_body->GetPosition().y, 0.0f)) *
		glm::rotate(glm::mat4(), m_body->GetAngle(), m_RotationAxis) * 
		glm::scale(glm::mat4(), m_Scale) // might need to change this later, idk what to do 
	);
}

void PlayerCharacter::Update()
{
	// Screen wrapping
	if (m_body->GetPosition().x < -10.0f) m_body->SetTransform(b2Vec2(410.0f, m_body->GetPosition().y), m_body->GetAngle());
	if (m_body->GetPosition().x > 410.0f) m_body->SetTransform(b2Vec2(-10.0f, m_body->GetPosition().y), m_body->GetAngle());
	if (m_body->GetPosition().y < -10.0f) m_body->SetTransform(b2Vec2(m_body->GetPosition().x, 235.0f), m_body->GetAngle());
	if (m_body->GetPosition().y > 235.0f) m_body->SetTransform(b2Vec2(m_body->GetPosition().x, -10.0f), m_body->GetAngle());

	
	b2Vec2 vel = m_body->GetLinearVelocity();
	vel *= 0.999f;
	m_body->SetLinearVelocity(vel);
	m_body->SetAngularVelocity(m_body->GetAngularVelocity() * 0.90f);

	std::cout << m_body->GetPosition().y << std::endl;

	m_fVibrationRate *= 0.90f;
}

//Update Overload
//Moves the player character by the input Translate
void PlayerCharacter::AddVelocity(float _Speed)
{
	m_body->ApplyForceToCenter(
	b2Vec2(m_body->GetWorldVector(b2Vec2(0, 1)).x * _Speed,
		   m_body->GetWorldVector(b2Vec2(0, 1)).y * _Speed), 
		   true);

	m_fVibrationRate = 3.0f;
}

void PlayerCharacter::AddRotation(float _Angle)
{	
	m_body->ApplyTorque(_Angle * 10.0f, true);
}

void PlayerCharacter::SetPosition(b2Vec2 _position)
{
	m_body->SetTransform(_position, m_body->GetAngle());
}

void PlayerCharacter::Initialize()
{
	m_Sprite->Initialize("Resources/Images/Player_Sprite.png");
}
