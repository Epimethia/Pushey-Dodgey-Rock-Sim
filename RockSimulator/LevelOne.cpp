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

void LevelOne::ProcessLevel(float _DeltaTick) {
	//Reading inputs
	if (Input::KeyState['w'] == INPUT_HOLD) {
		m_PlayerOne->AddVelocity(1.0f * _DeltaTick);
	}
	if (Input::KeyState['a'] == INPUT_HOLD) {
		m_PlayerOne->AddRotation(3.0f * _DeltaTick);
	}
	if (Input::KeyState['s'] == INPUT_HOLD) {
		m_PlayerOne->AddVelocity(-3.0f * _DeltaTick);
	}
	if (Input::KeyState['d'] == INPUT_HOLD) {
		m_PlayerOne->AddRotation(-3.0f * _DeltaTick);

	}
	Input::Update();

	m_PlayerOne->Update();
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
