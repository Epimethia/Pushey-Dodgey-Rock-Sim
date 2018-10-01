#include "Entity.h"
#include "Utilities.h"
#include "Camera.h"
#include "Physics.h"


Entity::Entity()
{

}

Entity::~Entity()
{
	Physics::GetInstance()->GetWorld()->DestroyBody(m_body);
	m_body = nullptr;
}


