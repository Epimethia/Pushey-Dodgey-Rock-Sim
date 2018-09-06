//	This include.
#include "LevelOne.h"


//	Library includes.


//	Local includes.
#include "Sprite.h"
#include "Camera.h"
#include "Utilities.h"
#include "PlayerCharacter.h"
#include "Physics.h"
#include "Asteroid.h"
#include "ContactListener.h"
#include "KeyboardInput.h"
#include "clock.h"


LevelOne::LevelOne()
{
	m_pBackground = std::make_shared<Sprite>();	
	Camera::GetInstance()->SetProj(ki_SCREENWIDTH, ki_SCREENHEIGHT);
	Camera::GetInstance()->Update();

	m_pClock = &(*CClock::GetInstance());

	CurrentPlayers.push_back(std::make_shared<XBOXController>(1));
	CurrentPlayers.push_back(std::make_shared<XBOXController>(2));	
	m_fSpawnTime = 0.0f;
}

LevelOne::~LevelOne()
{

}

void LevelOne::InitializeObjects()
{
	// Initialize Scene Background	
	m_pBackground->Initialize("Resources/Images/Background.png");

	// Initialize Other Objects..
	// Push objects to their appropriate vectors
	m_pPlayerOne = std::make_shared<PlayerCharacter>();	
	m_pPlayerOne->SetPosition(b2Vec2(3.0f, 4.5f));
	m_vpPlayerVec.push_back(m_pPlayerOne);
	m_vpEntityVec.push_back(m_pPlayerOne);
	m_pPlayerOne->LinkScore(&m_sDeathCount[0]);

	m_pPlayerTwo = std::make_shared<PlayerCharacter>();	
	m_pPlayerTwo->SetPosition(b2Vec2(13.0f, 4.5f));
	m_vpPlayerVec.push_back(m_pPlayerTwo);
	m_vpEntityVec.push_back(m_pPlayerTwo);
	m_pPlayerTwo->LinkScore(&m_sDeathCount[1]);

	m_pContactListener = &MyContactListener::GetInstance();
	m_pContactListener->SetPlayer(&(*m_pPlayerOne));
	m_pContactListener->SetPlayer(&(*m_pPlayerTwo));
	// Iterate through the entity vector and initialize all objects
	if (!m_vpEntityVec.empty())
	{
		for (unsigned int i = 0; i < m_vpEntityVec.size(); i++)
		{
			m_vpEntityVec[i]->Initialize();
		}
	}
}

void LevelOne::ProcessLevel(float _DeltaTick) {

	// Process Physics
	Physics::GetInstance()->Process();		

	//Processing the palye rinput
	ProcessPlayerInput(_DeltaTick);

	//Updating the keyboard input
	Input::Update();

	//Updating player controllers
	for (const auto& it : CurrentPlayers) it->Update();

	//Updating the players
	for (const auto& it : m_vpPlayerVec) it->Update();

	// Spawn Asteroids
	m_fSpawnTime += _DeltaTick;
	if (m_fSpawnTime > 1.0f)
	{
		std::shared_ptr<Asteroid> TempAsteroid = std::make_shared<Asteroid>();
		TempAsteroid->SetPosition(b2Vec2(-1.0f, 2.5f));
		TempAsteroid->Initialize();		
		m_vpAsteroidVec.push_back(TempAsteroid);

		// increment spawn timer
		m_fSpawnTime = 0.0f;
	}

	// Move Asteroids
	for (unsigned int i = 0; i < m_vpAsteroidVec.size(); i++)
	{
		m_vpAsteroidVec[i]->AddVelocity(b2Vec2(1.0f, 0.0f), 50.0f * _DeltaTick);
		// Destroy asteroid if it goes off screen
		if (m_vpAsteroidVec[i]->GetPosition().x > 20.0f || m_vpAsteroidVec[i]->GetPosition().y > 20.0f
		 || m_vpAsteroidVec[i]->GetPosition().x < -20.0f || m_vpAsteroidVec[i]->GetPosition().y < -20.0f)
		{
			m_vpAsteroidVec[i]->SetOffScreenBool(true);
		}
	}		

	// Clean up offscreen asteroids
	for (unsigned int i = 0; i < m_vpAsteroidVec.size(); i++)
	{
		if (m_vpAsteroidVec[i] != nullptr)
		{
			if (m_vpAsteroidVec[i]->GetOffScreenBool())
			{
				m_vpAsteroidVec.erase(m_vpAsteroidVec.begin() + i);
			}
		}
	}
}

void LevelOne::ProcessPlayerInput(float _DeltaTick)
{
	//Reading inputs
	//PLAYER_0 INPUTS
	auto& p0_Controller = CurrentPlayers[0];
	p0_Controller->Vibrate(0, static_cast<int>(1000.0f * m_pPlayerOne->GetVibrateRate()));
	if (Input::m_iKeyState['w'] == INPUT_HOLD || p0_Controller->ControllerButtons[BOTTOM_FACE_BUTTON] == INPUT_HOLD) {
		m_pPlayerOne->AddVelocity(40.0f * _DeltaTick);
	}
	if (Input::m_iKeyState['s'] == INPUT_HOLD || p0_Controller->ControllerButtons[LEFT_FACE_BUTTON] == INPUT_HOLD) {
		m_pPlayerOne->AddVelocity(-40.0f * _DeltaTick);
	}
	if (Input::m_iKeyState['a'] == INPUT_HOLD || p0_Controller->normalizedLX < -0.8f) {
		m_pPlayerOne->AddRotation(3.0f * _DeltaTick);
	}
	if (Input::m_iKeyState['d'] == INPUT_HOLD || p0_Controller->normalizedLX > 0.8f) {
		m_pPlayerOne->AddRotation(-3.0f * _DeltaTick);
	}
	if (Input::m_iKeyState['f'] == INPUT_FIRST_PRESS) {
		m_pPlayerOne->Shoot();
	}

	//Reading inputs
	//PLAYER_1 INPUTS
	auto& p1_Controller = CurrentPlayers[1];
	//Making the controller vibrate
	p1_Controller->Vibrate(0, static_cast<int>(1000.0f * m_pPlayerTwo->GetVibrateRate()));
	if (Input::m_iKeyState['8'] == INPUT_HOLD || p1_Controller->ControllerButtons[BOTTOM_FACE_BUTTON] == INPUT_HOLD) {
		m_pPlayerTwo->AddVelocity(40.0f * _DeltaTick);
	}
	if (Input::m_iKeyState['5'] == INPUT_HOLD || p1_Controller->ControllerButtons[LEFT_FACE_BUTTON] == INPUT_HOLD) {
		m_pPlayerTwo->AddVelocity(-40.0f * _DeltaTick);
	}
	if (Input::m_iKeyState['4'] == INPUT_HOLD || p1_Controller->normalizedLX < -0.8f) {
		m_pPlayerTwo->AddRotation(1.0f * _DeltaTick);
	}
	if (Input::m_iKeyState['6'] == INPUT_HOLD || p1_Controller->normalizedLX > 0.8f) {
		m_pPlayerTwo->AddRotation(-1.0f * _DeltaTick);
	}
}

void LevelOne::RenderObjects()
{
	// Render Background
	m_pBackground->Render(glm::scale(glm::mat4(), glm::vec3(16.0f, 9.0f, 0.0f))); // spawn in the center

	// Render Object Vectors (check that the vectors are not empty)
	if (!m_vpEntityVec.empty())
	{
		for (const auto& it : m_vpEntityVec)
		{
			it->Render();
			it->DrawDebug();
		}
	}
	
	if (!m_vpAsteroidVec.empty())
	{
		for (const auto& it : m_vpAsteroidVec)
		{
			it->Render();
			it->DrawDebug();
		}
	}  

	//	Render score.

	//	m_sDeaths[1] + "    -    " + m_sDeaths[0];
	//	m_fTimer;
}
