#pragma once
//	Library includes.


//	Local includes.
#include "Utilities.h"


class Physics
{
#pragma region Singleton
public:
	static std::shared_ptr<Physics> GetInstance();
	static void DestroyInstance();
	~Physics();
private:
	static std::shared_ptr<Physics> s_pPhysics;
	Physics(Physics const&);
	void operator=(Physics const&);
	Physics();
#pragma endregion

public:
	void Process();
	b2Body* CreateBody(b2BodyDef _bodyDef);
	b2World* GetWorld() const;


private:
	b2Vec2 m_vGravity = b2Vec2(0.0f, 0.0f);
	b2World* m_pWorld = new b2World(m_vGravity);
	float32 m_fTimeStep;
	int32 m_iVelocityIterations;
	int32 m_iPositionIterations;
};

