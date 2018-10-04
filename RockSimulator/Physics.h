#ifndef __PHYSICS_H__
#define __PHYSICS_H__
//	Library includes.


//	Local includes.
#include "Utilities.h"


class Physics
{
public:
	static std::shared_ptr<Physics> GetInstance();
	static void DestroyInstance();
	Physics();
	~Physics();

	void Process();
	b2Body* CreateBody(b2BodyDef _bodyDef);
	b2World* GetWorld() const;


private:
	static std::shared_ptr<Physics> s_pInstance;
	Physics(Physics const&) = delete;
	void operator=(Physics const&) = delete;

	b2Vec2 m_vGravity = b2Vec2(0.0f, 0.0f);
	b2World* m_pWorld = new b2World(m_vGravity);
	float32 m_fTimeStep;
	int32 m_iVelocityIterations;
	int32 m_iPositionIterations;
};

#endif