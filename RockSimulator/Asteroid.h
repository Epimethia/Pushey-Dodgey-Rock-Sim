#pragma once
//	Library includes.
#include <glm.hpp>


//	Local includes.
#include "Entity.h"


class b2Body;


class Asteroid : public Entity
{
public:
	Asteroid();
	Asteroid(const char* _Filepath);
	~Asteroid();

	//	Process data and update.
	void Initialize();
	void Update();
	void Render();

	void SetSprite(const char* _Filepath);


private:

	float m_fRadius{ 0.0f };
	float m_fVelocity{ 0.0f };
	const float c_fMaxVelocity{ 5.0f };
	const float v_fAcceleration{ 0.05f };

	glm::vec3 m_vForward;
	
	std::shared_ptr<Sprite> m_Sprite;
	glm::vec3 m_Scale;
	glm::vec3 m_RotationAxis;
	float m_fVibrationRate;
	
	// Physics
	b2BodyDef m_bodyDef;
	b2Body* m_body;

};