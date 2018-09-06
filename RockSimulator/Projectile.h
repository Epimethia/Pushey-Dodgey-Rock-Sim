#pragma once

//Local includes
#include "Entity.h"
#include "Utilities.h"
#include "Sprite.h"
#include "Physics.h"
#include "clock.h"
#include "Dependencies/glm/gtx/string_cast.hpp"
#include "Dependencies/glm/gtx/rotate_vector.hpp"

class Sprite;
class Projectile : public Entity {
public:
	Projectile();
	Projectile(b2Vec2 _Pos, b2Vec2 Direction);
	void Update();
	void Render();
	void Initialize();
	glm::vec2 GetPosition() { return glm::vec2(); };

	bool m_bValid;
private:
	float m_fMaxLifeTime;
	float m_fCurrentLifetime;
	float m_fBulletSpeed;
};