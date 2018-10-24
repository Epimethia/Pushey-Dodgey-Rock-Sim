#include "Asteroid.h"
#include "Sprite.h"
#include "Physics.h"
#include "Dependencies/glm/gtx/string_cast.hpp"
#include "Dependencies/glm/gtx/rotate_vector.hpp"


Asteroid::Asteroid(float _scale)
{
	m_Sprite = std::make_shared<Sprite>();
	m_Scale = glm::vec3(_scale, _scale, _scale);
	m_RotationAxis = glm::vec3(0.0f, 0.0f, 1.0f);
	m_bOffScreen = false;

	// Physics
	b2FixtureDef fixtureDef;
	m_bodyDef.type = b2_dynamicBody;
	m_bodyDef.position.Set(8.0f, 4.5f);
	m_body = Physics::GetInstance()->CreateBody(m_bodyDef);
	b2CircleShape dynamicCircle;
	dynamicCircle.m_p.Set(0.0f, 0.0f);
	dynamicCircle.m_radius = _scale;
	fixtureDef.shape = &dynamicCircle;
	fixtureDef.density = 3.0f * _scale;
	fixtureDef.friction = 0.3f;
	fixtureDef.restitution = 1.0f;
	m_body->CreateFixture(&fixtureDef);
}


Asteroid::~Asteroid()
{

}

void Asteroid::Render()
{
	m_Sprite->Render(
		glm::translate(glm::mat4(), glm::vec3(m_body->GetPosition().x, m_body->GetPosition().y, 0.0f)) *
		glm::rotate(glm::mat4(), m_body->GetAngle(), m_RotationAxis) *
		glm::scale(glm::mat4(), m_Scale) // might need to change this later, idk what to do 
	);
}

void Asteroid::Update()
{
	// Screen wrapping
	if (m_body->GetPosition().x < -0.4f) m_body->SetTransform(b2Vec2(16.5f, m_body->GetPosition().y), m_body->GetAngle());
	else if (m_body->GetPosition().x > 16.5f) m_body->SetTransform(b2Vec2(-0.4f, m_body->GetPosition().y), m_body->GetAngle());
	if (m_body->GetPosition().y < -0.4f) m_body->SetTransform(b2Vec2(m_body->GetPosition().x, 9.4f), m_body->GetAngle());
	else if (m_body->GetPosition().y > 9.5f) m_body->SetTransform(b2Vec2(m_body->GetPosition().x, -0.4f), m_body->GetAngle());
}

//Update Overload
//Moves the asteroid by the input Translate
void Asteroid::AddVelocity(b2Vec2 _direction, const float& _Speed)
{
	m_body->ApplyForceToCenter(
		b2Vec2((_direction.x * _Speed) * m_body->GetMass(),
			   (_direction.y * _Speed) * m_body->GetMass()),
		true);

	// Limit/Clamp velocity
	b2Vec2 LinearVelocity = m_body->GetLinearVelocity();
	m_body->SetLinearVelocity(b2Vec2(glm::clamp(LinearVelocity.x, -2.1f, 2.1f), glm::clamp(LinearVelocity.y, -2.1f, 2.1f)));

}

void Asteroid::AddRotation(const float& _AngularForce)
{
	m_body->ApplyTorque(_AngularForce, true);
}

void Asteroid::SetPosition(b2Vec2 _position)
{
	m_body->SetTransform(_position, m_body->GetAngle());
}


void Asteroid::Initialize()
{
	//randomizing the asteroid sprite
	int spriteIndex = rand() % 7;
	m_Sprite->Initialize(std::string("Resources/Images/Asteroids/Asteroid_" + std::to_string(spriteIndex) + ".png").c_str());
}

void Asteroid::InitializeDebugDraw()
{
}
