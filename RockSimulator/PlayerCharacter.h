#pragma once
//	Library includes.


//	Local includes.
#include "Entity.h"
#include "Utilities.h"
#include "Projectile.h"


class Sprite;
class PlayerCharacter :
	public Entity
{
public:
	PlayerCharacter();
	~PlayerCharacter();
	

	// Virtual Functions
	void Render();
	void Update();
	void AddVelocity(float _Speed);
	void AddRotation(float _Angle);
	void SetPosition(b2Vec2 _position);
	void Shoot();
	glm::vec2 GetPosition() { return glm::vec2(m_body->GetPosition().x, m_body->GetPosition().y); }
	float GetVibrateRate() { return m_fVibrationRate; };	
	void Initialize();

private:	
	float m_fVibrationRate;	
	Projectile* Bullet;
};

