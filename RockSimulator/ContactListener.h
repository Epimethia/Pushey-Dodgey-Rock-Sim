#ifndef __CONTACTLISTENER_H__
#define __CONTACTLISTENER_H__
//	Library includes.
#include <vector>


//	Local includes.
#include "Physics.h"


//	Class prototypes.
class PlayerCharacter;


class MyContactListener : public b2ContactListener
{
public:
	static MyContactListener& GetInstance();
	static void DestroyInstance();
	void SetPlayer(PlayerCharacter* _Player);
	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);
	void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
	void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);


private:
	static MyContactListener* s_pInstance;

	std::vector<PlayerCharacter*> m_vPlayers;


protected:


};

#endif