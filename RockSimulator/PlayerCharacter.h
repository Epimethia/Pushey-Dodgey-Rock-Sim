#pragma once
//	Library includes.


//	Local includes.
#include "Entity.h"
#include "Utilities.h"


class Sprite;
class PlayerCharacter :
	public Entity
{
public:
	PlayerCharacter();
	~PlayerCharacter();
	void TakeDamage();
	b2Body* GetBody() const;
	

	// Virtual Functions
	void Render();
	void Update();
	void AddVelocity(float _Speed);
	void AddRotation(float _Angle);
	void SetPosition(b2Vec2 _position);
	glm::vec2 GetPosition() { return glm::vec2(m_body->GetPosition().x, m_body->GetPosition().y); }
	float GetVibrateRate() { return m_fVibrationRate; };	
	void Initialize();
	void LinkScore(short* _Deaths);
	void Respawn();


private:
	float m_fVibrationRate;	
	float m_fHealth{ 0.0f };

	short* m_pDeaths{ 0 };


};

