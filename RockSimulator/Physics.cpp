//	This include.
#include "Physics.h"


//	Library includes.


//	Local includes.
#include "ContactListener.h"


std::shared_ptr<Physics> Physics::s_pInstance;

std::shared_ptr<Physics> Physics::GetInstance()
{
	if (!s_pInstance)
	{
		s_pInstance = std::shared_ptr<Physics>(new Physics());
	}
	return s_pInstance;
}

void Physics::DestroyInstance()
{
	s_pInstance.reset();
	//s_pSceneManager = nullptr;
}

Physics::Physics()
{
	m_fTimeStep = 1.0f / 60.0f;
	m_iVelocityIterations = 8;
	m_iPositionIterations = 3;
	m_pWorld->SetContactListener(&MyContactListener::GetInstance());
}

void Physics::Process(float _deltaTick)
{
	m_pWorld->Step(m_fTimeStep, m_iVelocityIterations, m_iPositionIterations);

	m_fAccumulator += _deltaTick;
	
	while (m_fAccumulator >= m_fTimeStep)
	{
		m_pWorld->Step(m_fTimeStep, m_iVelocityIterations, m_iPositionIterations);
		m_fAccumulator -= m_fTimeStep;
	}

	m_pWorld->ClearForces();
}

b2Body * Physics::CreateBody(b2BodyDef _bodyDef)
{
	b2Body* body = m_pWorld->CreateBody(&_bodyDef);
	return body;
}

b2World* Physics::GetWorld() const
{
	return m_pWorld;
}

Physics::~Physics()
{
	MyContactListener::GetInstance().DestroyInstance();
	delete m_pWorld;
}
