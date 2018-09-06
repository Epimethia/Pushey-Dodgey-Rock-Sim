#include "PlayerCharacter.h"
#include "Sprite.h"
#include "Physics.h"
#include "Dependencies/glm/gtx/string_cast.hpp"
#include "Dependencies/glm/gtx/rotate_vector.hpp"


PlayerCharacter::PlayerCharacter()
{
	m_Sprite = std::make_shared<Sprite>();	
	m_Scale = glm::vec3(0.3f, 0.3f, 0.0f);
	m_RotationAxis = glm::vec3(0.0f, 0.0f, 1.0f);
	m_fVibrationRate = 0.0f;
	m_fHealth = 100.0f;

	// Physics
	b2FixtureDef fixtureDef;	
	m_bodyDef.type = b2_dynamicBody;
	m_bodyDef.position.Set(8.0f, 4.5f);
	m_body = Physics::GetInstance()->CreateBody(m_bodyDef);
	m_shape.SetAsBox(0.2f, 0.25f);
	fixtureDef.shape = &m_shape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	fixtureDef.restitution = 20.0f;
	m_body->CreateFixture(&fixtureDef);

	Bullet = nullptr;

}


PlayerCharacter::~PlayerCharacter()
{

	//CLEAR UP ALL THE POINTERS
	delete Bullet;
	Bullet = nullptr;
}

void PlayerCharacter::TakeDamage()
{
	SoundManager::GetInstance()->SoundTakeDamage();
	m_fHealth -= 5.0f;
	std::cout << m_fHealth << std::endl;
	if (0.0f > m_fHealth)
	{
		Respawn();
	}
}

b2Body * PlayerCharacter::GetBody() const
{
	return m_body;
}

void PlayerCharacter::Render()
{		
	m_Sprite->Render(
		glm::translate(glm::mat4(), glm::vec3(m_body->GetPosition().x, m_body->GetPosition().y, 0.0f)) *
		glm::rotate(glm::mat4(), m_body->GetAngle(), m_RotationAxis) * 
		glm::scale(glm::mat4(), m_Scale) // might need to change this later, idk what to do 
	);
	if (Bullet) {
		Bullet->Render();
	};
}

void PlayerCharacter::Update()
{
	// Screen wrapping
	if (m_body->GetPosition().x < -0.4f) m_body->SetTransform(b2Vec2(16.5f, m_body->GetPosition().y), m_body->GetAngle());
	if (m_body->GetPosition().x > 16.5f) m_body->SetTransform(b2Vec2(-0.4f, m_body->GetPosition().y), m_body->GetAngle());
	if (m_body->GetPosition().y < -0.4f) m_body->SetTransform(b2Vec2(m_body->GetPosition().x, 9.4f), m_body->GetAngle());
	if (m_body->GetPosition().y > 9.5f) m_body->SetTransform(b2Vec2(m_body->GetPosition().x, -0.4f), m_body->GetAngle());

	m_fVibrationRate *= 0.90f;
	m_body->SetLinearVelocity(0.98f * m_body->GetLinearVelocity());
	m_body->SetAngularVelocity(0.975f * m_body->GetAngularVelocity());

	if (Bullet != nullptr) {
		if (Bullet->m_bValid) {
			Bullet->Update();
		}
		else {
			Bullet = nullptr;
		};
	};

}

//Update Overload
//Moves the player character by the input Translate
void PlayerCharacter::AddVelocity(float _Speed)
{
	m_body->ApplyForceToCenter(
	b2Vec2(m_body->GetWorldVector(b2Vec2(0, 1)).x * _Speed,
		   m_body->GetWorldVector(b2Vec2(0, 1)).y * _Speed),
		   true);

	// Limit/Clamp velocity
	b2Vec2 LinearVelocity = m_body->GetLinearVelocity();
	m_body->SetLinearVelocity(b2Vec2(glm::clamp(LinearVelocity.x, -4.1f, 4.1f), glm::clamp(LinearVelocity.y, -4.1f, 4.1f)));

	m_fVibrationRate = 3.0f;
}

//	Radians or Degrees?
void PlayerCharacter::AddRotation(float _Angle)
{	
	m_body->ApplyTorque(_Angle, true);
}

void PlayerCharacter::SetPosition(b2Vec2 _position)
{
	m_body->SetTransform(_position, m_body->GetAngle());
}

void PlayerCharacter::Shoot()
{

	//getting the position of the bullet spawn
	if (Bullet == nullptr) {
		b2Vec2 Direction = m_body->GetWorldVector(b2Vec2(0, 1));
		Direction.Normalize();
		Direction *= 0.7f;
		b2Vec2 pos = m_body->GetPosition() + Direction;
		Bullet = new Projectile(pos, Direction);
		SoundManager::GetInstance()->SoundPew();
	}
}


void PlayerCharacter::Initialize()
{
	m_Sprite->Initialize("Resources/Images/Player_Sprite.png");
}

void PlayerCharacter::LinkScore(short * _Deaths)
{
	m_pDeaths = _Deaths;
}

void PlayerCharacter::Respawn()
{		
	*m_pDeaths += 1;

	m_RotationAxis = glm::vec3(0.0f, 0.0f, 1.0f);
	m_body->SetTransform(b2Vec2(3.0f, 4.5f), m_body->GetAngle());
	m_fHealth = 100.0f;
}
