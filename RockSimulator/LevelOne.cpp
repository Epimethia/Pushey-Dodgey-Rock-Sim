#include "LevelOne.h"
#include "Sprite.h"
#include "Camera.h"
#include "Utilities.h"
#include "PlayerCharacter.h"

LevelOne::LevelOne()
{
	m_Background = std::make_shared<Sprite>();	
	Camera::GetInstance()->SetProj(ki_SCREENWIDTH, ki_SCREENHEIGHT);
	Camera::GetInstance()->Update();
}

LevelOne::~LevelOne()
{
}

void LevelOne::InitializeObjects()
{
	// Initialize Scene Background	
	m_Background->Initialize("Resources/Images/Background.png");

	// Initialize Other Objects..
	// Push objects to their appropriate vectors
	m_PlayerOne = std::make_shared<PlayerCharacter>();	
	m_PlayerVec.push_back(m_PlayerOne);
	m_EntityVec.push_back(m_PlayerOne);

	// Itterate through the entity vector and initialize all objects
	if (!m_EntityVec.empty())
	{
		for (unsigned int i = 0; i < m_EntityVec.size(); i++)
		{
			m_EntityVec[i]->Initialize();
		}
	}
}

void LevelOne::RenderObjects()
{
	// Render Background
	m_Background->Render(glm::scale(glm::mat4(), glm::vec3(25.0f, 25.0f, 0.0f))); // spawn in the center

	// Render Object Vectors (check that the vectors are not empty)
	if (!m_EntityVec.empty())
	{
		for (unsigned int i = 0; i < m_EntityVec.size(); i++)
		{
			m_EntityVec[i]->Render();
		}
	}
}
