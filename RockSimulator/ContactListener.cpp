//	This include.
#include "ContactListener.h"


//	Library includes.
#include <iostream>


//	Local includes.
#include "PlayerCharacter.h"


//	Static variables.
MyContactListener* MyContactListener::s_pInstance = 0;


MyContactListener&
MyContactListener::GetInstance()
{
	if (0 == s_pInstance)
	{
		s_pInstance = new MyContactListener();
	}
	return *s_pInstance;
}

void
MyContactListener::DestroyInstance()
{
	delete s_pInstance;
	s_pInstance = 0;
}

void
MyContactListener::SetPlayer(PlayerCharacter* _Player)
{
	m_vPlayers.push_back(_Player);
}

void
MyContactListener::BeginContact(b2Contact* contact)
{
	std::cout << "Impact" << std::endl;
	unsigned int iX = 0;
	while (m_vPlayers.size() > iX)
	{
		if (contact->GetFixtureA()->GetBody() == m_vPlayers[iX]->GetBody())
		{
			m_vPlayers[iX]->TakeDamage();
			break;
		}
		iX++;
	}
}

void
MyContactListener::EndContact(b2Contact* contact)
{

}

void
MyContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{

}

void
MyContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{

}