//	This include.
#include "Asteroid.h"


//	Library includes.


//	Local includes.
#include "Physics.h"
#include "Sprite.h"
#include "Dependencies\Box2D\Box2D.h"



Asteroid::Asteroid()
{
	Initialize();
}

Asteroid::Asteroid(const char* _Filepath)
{
	Initialize();
	m_Sprite->Initialize(_Filepath);
}

Asteroid::~Asteroid()
{
	
}

void
Asteroid::Initialize()
{
	m_Sprite = std::make_shared<Sprite>();
	m_Scale = glm::vec3(50.0f, 50.0f, 1.0f);
	m_RotationAxis = glm::vec3(0.0f, 0.0f, 1.0f);
	m_fVibrationRate = 0.0f;

	// Physics
	b2FixtureDef fixtureDef;
	b2PolygonShape dynamicBox;
	m_bodyDef.type = b2_dynamicBody;
	m_bodyDef.position.Set(800.0f, 450.0f);
	m_body = Physics::GetInstance()->CreateBody(m_bodyDef);
	dynamicBox.SetAsBox(1.0f, 1.0f);
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	m_body->CreateFixture(&fixtureDef);
}

void
Asteroid::Update()
{
	review functionality
	//
	m_body->ApplyForceToCenter(
		b2Vec2(m_body->GetWorldVector(b2Vec2(0, 1)).x * v_fAcceleration,
			m_body->GetWorldVector(b2Vec2(0, 1)).y * v_fAcceleration),
		true);
}

void
Asteroid::Render()
{

}

void
Asteroid::SetSprite(const char* _Filepath)
{
	m_Sprite->Initialize(_Filepath);
}