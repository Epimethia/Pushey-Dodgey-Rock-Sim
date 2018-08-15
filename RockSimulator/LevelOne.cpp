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

	CurrentPlayers.push_back(std::make_shared<XBOXController>(1));
	CurrentPlayers.push_back(std::make_shared<XBOXController>(2));
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

	auto& Player0Controller = CurrentPlayers[0];

	//Reading inputs
	if (Input::KeyState['w'] == INPUT_HOLD || Player0Controller->ControllerButtons[BOTTOM_FACE_BUTTON] == INPUT_HOLD) {
		m_PlayerOne->AddVelocity(50.0f * _DeltaTick);
	}
	if (Input::KeyState['a'] == INPUT_HOLD || Player0Controller->normalizedLX < -0.9f) {
		m_PlayerOne->AddRotation(3.0f * _DeltaTick);
	}
	if (Input::KeyState['s'] == INPUT_HOLD || Player0Controller->ControllerButtons[LEFT_FACE_BUTTON] == INPUT_HOLD) {
		m_PlayerOne->Brake();
	}
	if (Input::KeyState['d'] == INPUT_HOLD || Player0Controller->normalizedLX > 0.9f) {
		m_PlayerOne->AddRotation(-3.0f * _DeltaTick);

	}
	Input::Update();






	//Updating player controllers
	for (auto it : CurrentPlayers) {
		it->Update();
	}


	m_PlayerOne->Update();
}

void LevelOne::RenderObjects()
{
	// Render Background
	m_Background->Render(glm::scale(glm::mat4(), glm::vec3(1600.0f, 900.0f, 0.0f))); // spawn in the center

	// Render Object Vectors (check that the vectors are not empty)
	if (!m_EntityVec.empty())
	{
		for (unsigned int i = 0; i < m_EntityVec.size(); i++)
		{
			m_EntityVec[i]->Render();
		}
	}
}
