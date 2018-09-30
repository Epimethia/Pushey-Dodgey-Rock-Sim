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
	std::cout << "Impact " << std::endl;
	unsigned int iX = 0;
	unsigned int iY = 0;
	while (m_vPlayers.size() > iX)
	{
		if (contact->GetFixtureA()->GetBody() == m_vPlayers[iX]->GetBody())
		{
			std::cout << "Player: " << iX + 1 << std::endl;
			std::cout << "Health: ";
			m_vPlayers[iX]->TakeDamage();
			break;
		}
		iX++;
	}
	
	while (m_vPlayers.size() > iY)
	{
		if (contact->GetFixtureA()->GetBody()->GetContactList()->other == m_vPlayers[iY]->GetBody()
			&& m_vPlayers[iY]->GetBody() != m_vPlayers[iX]->GetBody())
		{
			std::cout << std::endl;
			std::cout << "Impact Player: " << iY + 1 << std::endl;
			std::cout << "Health: ";
			m_vPlayers[iY]->TakeDamage();
			break;
		}
		iY++;
	}
	std::cout << std::endl;
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