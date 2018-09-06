#include "Projectile.h"

Projectile::Projectile() {}

Projectile::Projectile(b2Vec2 _Pos, b2Vec2 _Direction)
{
	m_Sprite = std::make_shared<Sprite>();
	m_Scale = glm::vec3(0.13f, 0.13f, 0.13f);
	m_RotationAxis = glm::vec3(0.0f, 0.0f, 1.0f);
	m_fMaxLifeTime = 300.0f;
	m_fBulletSpeed = 100.0f;

	// Physics
	b2FixtureDef fixtureDef;
	m_bodyDef.type = b2_dynamicBody;
	m_bodyDef.position = _Pos;
	m_body = Physics::GetInstance()->CreateBody(m_bodyDef);
	b2CircleShape dynamicCircle;
	dynamicCircle.m_p.Set(0.0f, 0.0f);
	dynamicCircle.m_radius = 0.1f;
	fixtureDef.shape = &dynamicCircle;
	fixtureDef.density = 10.0f;
	fixtureDef.friction = 0.3f;
	fixtureDef.restitution = 1.0f;
	m_body->CreateFixture(&fixtureDef);

	b2Vec2 dir = _Direction;
	dir.Normalize();
	m_body->ApplyForceToCenter(
		b2Vec2(dir.x * m_fBulletSpeed,
			dir.y * m_fBulletSpeed),
		true);

	m_bValid = true;
	m_Sprite->Initialize("Resources/Images/Wave.png");

}

void Projectile::Initialize() {

}

void Projectile::Update()
{
	if (m_bValid) {
		if (m_fCurrentLifetime >= m_fMaxLifeTime) {
			Physics::GetInstance()->GetWorld()->DestroyBody(m_body);
			m_bValid = false;
		}
		m_fCurrentLifetime += CClock::GetInstance()->GetDeltaTick();
	}
}

void Projectile::Render()
{
	if (m_bValid) {
		m_Sprite->Render(
			glm::translate(glm::mat4(), glm::vec3(m_body->GetPosition().x, m_body->GetPosition().y, 0.0f)) *
			glm::rotate(glm::mat4(), m_body->GetAngle(), m_RotationAxis) *
			glm::scale(glm::mat4(), m_Scale) // might need to change this later, idk what to do 
		);
	}
}
