#ifndef __PLAYERCHARACTER_H__
#define __PLAYERCHARACTER_H__
//	Library includes.


//	Local includes.
#include "Entity.h"
#include "Utilities.h"
#include "Projectile.h"
#include "SoundManager.h"

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
	void AddVelocity(const float& _Speed);
	void AddRotation(const float& _Angle);
	void SetPosition(b2Vec2 _position);
	float GetCurrentSpeed();
	void Shoot();
	glm::vec2 GetPosition() { return glm::vec2(m_body->GetPosition().x, m_body->GetPosition().y); }
	float GetVibrateRate() { return m_fVibrationRate; }	;	
	bool GetPlayerDead() { return m_bPlayerDead; }
	void Initialize();
	void InitializeDebugDraw();
	void LinkScore(short* _Deaths);
	void Respawn();
	void ResetPlayer();
	float GetHealth();
	bool& GetPlayerAccelerate() { return m_bPlayerAccelerating; };
	void SetSpawnPosition(glm::vec3 _vec) { m_spawnPosition = _vec; }
	void SetPlayerTexture(const char* _texturePath);

private:
	float m_fVibrationRate;	
	float m_fHealth{ 0.0f };
	short* m_pDeaths{ 0 };	
	Projectile* Bullet;
	glm::vec3 m_spawnPosition;
	bool m_bPlayerDead;
	bool m_bPlayerAccelerating;
	const char* m_kcPlayerTexture{ nullptr };


};

#endif