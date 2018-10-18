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
	Asteroid();
	~Asteroid();

	// Virtual Functions
	void Render();
	void Update();	
	void Initialize();
	void InitializeDebugDraw();
	glm::vec2 GetPosition() { return glm::vec2(m_body->GetPosition().x, m_body->GetPosition().y); }

	void SetPosition(b2Vec2 _position);
	void AddRotation(float _Angle);
	void AddVelocity(b2Vec2 _direction, float _Speed);
	bool GetOffScreenBool() { return m_bOffScreen; }
	void SetOffScreenBool(bool _bool) { m_bOffScreen = _bool; }
	

private:
	float m_fVibrationRate;
	bool m_bOffScreen;


};

#endif