#pragma once

//Local includes
#include "Entity.h"
#include "Utilities.h"
#include "Physics.h"
#include "Dependencies/glm/gtx/string_cast.hpp"
#include "Dependencies/glm/gtx/rotate_vector.hpp"


class Projectile : public Entity {
public:
	Projectile();
	Projectile(b2Vec2 _Pos, b2Vec2 Direction, const float& _Angle);
	void Update();
	void Render();
	void Initialize();
	void InitializeDebugDraw();
	glm::vec2 GetPosition() { return glm::vec2(); };

	bool m_bValid;


private:
	float m_fMaxLifeTime;
	float m_fCurrentLifetime;
	float m_fBulletSpeed;


};