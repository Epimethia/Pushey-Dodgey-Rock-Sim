#ifndef __ASTEROID_H__
#define __ASTEROID_H__
//	Library includes.


//	Local includes.
#include "Entity.h"
#include "Utilities.h"


class Sprite;


class Asteroid : public Entity
{
public:
	Asteroid(float _scale);
	~Asteroid();

	// Virtual Functions
	void Render();
	void Update();	
	void Initialize();
	void InitializeDebugDraw();
	glm::vec2 GetPosition() { return glm::vec2(m_body->GetPosition().x, m_body->GetPosition().y); }

	void SetPosition(const b2Vec2& _position);
	void AddRotation(const float& _Angle);
	void AddVelocity(const b2Vec2& _direction, const float& _Speed);
	bool GetOffScreenBool() { return m_bOffScreen; }
	void SetOffScreenBool(bool _bool) { m_bOffScreen = _bool; }
	

private:
	float m_fVibrationRate;
	bool m_bOffScreen;


};

#endif