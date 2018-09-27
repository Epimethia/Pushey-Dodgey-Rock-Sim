//	This include.
#include "LevelOne.h"


//	Library includes.
#include <iostream>
#include <string>


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
#include "TextLabel.h"
#include "healthbar.h"


LevelOne::LevelOne()
{
	m_pBackground = std::make_shared<Sprite>();	
	Camera::GetInstance()->SetProj(ki_SCREENWIDTH, ki_SCREENHEIGHT);
	Camera::GetInstance()->Update();

	m_pClock = &(*CClock::GetInstance());

	m_pPlayerOneController = std::make_shared<XBOXController>(1);
	m_pPlayerTwoController = std::make_shared<XBOXController>(2);
	m_fSpawnTime = 0.0f;
}

LevelOne::~LevelOne()
{

}

void LevelOne::InitializeObjects()
{
	// Initialize Scene Background	
	m_pBackground->Initialize("Resources/Images/Background.png");

	m_pP1HealthBar = std::make_shared<C_HealthBar>("Resources/Images/HealthBar100.png");
	m_pP1HealthBar->SetPosition(glm::vec3(1.0f, 7.0f, 1.0f));

	m_pP2HealthBar = std::make_shared<C_HealthBar>("Resources/Images/HealthBar100.png");
	m_pP2HealthBar->SetPosition(glm::vec3(15.0f, 7.0f, 1.0f));

	// Initialize Other Objects..
	// Push objects to their appropriate vectors
	m_pPlayerOne = std::make_shared<PlayerCharacter>();	
	m_pPlayerOne->SetPosition(b2Vec2(3.0f, 4.5f));	
	m_vpEntityVec.push_back(m_pPlayerOne);
	m_pPlayerOne->LinkScore(&m_sDeathCount[0]);
	std::string ScoreText1 = "xesrt4574rdyh";//std::to_string(m_sDeathCount[1]);
	m_P1Score = std::make_shared<TextLabel>(std::to_string(m_sDeathCount[1]), "Resources/fonts/arial.ttf", glm::vec2(400.0f, 700.0f));

	m_pPlayerTwo = std::make_shared<PlayerCharacter>();	
	m_pPlayerTwo->SetPosition(b2Vec2(13.0f, 4.5f));	
	m_vpEntityVec.push_back(m_pPlayerTwo);
	m_pPlayerTwo->LinkScore(&m_sDeathCount[1]);
	std::string ScoreText2 = std::to_string(m_sDeathCount[0]);
	m_P2Score = std::make_shared<TextLabel>(std::to_string(m_sDeathCount[0]), "Resources/fonts/arial.ttf", glm::vec2(1200.0f, 700.0f));

	m_pContactListener = &MyContactListener::GetInstance();
	m_pContactListener->SetPlayer(&(*m_pPlayerOne));
	m_pContactListener->SetPlayer(&(*m_pPlayerTwo));

	m_text = std::make_shared<TextLabel>("PLAY", "Resources/Fonts/arial.ttf", glm::vec2(190.0f, 350.0f)); // Play Text	

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
	m_pPlayerOneController->Update();
	m_pPlayerTwoController->Update();

	//Updating the players
	m_pPlayerOne->Update();
	m_pPlayerTwo->Update();

	if (m_pPlayerOne->GetPlayerDead())
	{
		m_pPlayerOne->Respawn();
		m_vpAsteroidVec.clear();
		m_fSpawnTime = 0.0f;
		m_P2Score->SetText(std::to_string(m_sDeathCount[0]));
	}
	if (m_pPlayerTwo->GetPlayerDead())
	{
		m_pPlayerTwo->Respawn();
		m_vpAsteroidVec.clear();
		m_fSpawnTime = 0.0f;
		m_P1Score->SetText(std::to_string(m_sDeathCount[1]));
	}

	// Spawn Asteroids
	m_fSpawnTime += _DeltaTick;
	if (m_fSpawnTime > 1.0f)
	{
		std::random_device rd;  //Will be used to obtain a seed for the random number engine
		std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
		std::uniform_real_distribution<> dis(0.0, 9.0);

		std::shared_ptr<Asteroid> TempAsteroid = std::make_shared<Asteroid>();
		TempAsteroid->SetPosition(b2Vec2(-1.0f, static_cast<float>(dis(gen))));
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
	auto& p0_Controller = m_pPlayerOneController;
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
	auto& p1_Controller = m_pPlayerTwoController;
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

	//	Update Health.
	glm::vec3 TempScale = m_pP1HealthBar->GetScale();
	TempScale.x = 1.0f * (m_pPlayerOne->GetHealth() / 100.0f);
	m_pP1HealthBar->SetScale(TempScale);

	TempScale = m_pP2HealthBar->GetScale();
	TempScale.x = 1.0f * (m_pPlayerTwo->GetHealth() / 100.0f);
	m_pP2HealthBar->SetScale(TempScale);
}

void LevelOne::RenderObjects()
{
	// Render Background
	m_pBackground->Render(glm::scale(glm::mat4(), glm::vec3(16.0f, 9.0f, 0.0f))); // spawn in the center
	m_pP1HealthBar->Render();
	m_pP2HealthBar->Render();

	m_text->Render();
	m_P1Score->Render();
	m_P2Score->Render();

	// Render Object Vectors (check that the vectors are not empty)
	if (!m_vpEntityVec.empty())
	{
		for (const auto& it : m_vpEntityVec)
		{
			it->Render();
			//it->DrawDebug();
		}
	}
	
	if (!m_vpAsteroidVec.empty())
	{
		for (const auto& it : m_vpAsteroidVec)
		{
			it->Render();
			//it->DrawDebug();
		}
	}  




	//	Render score.

	//	m_sDeaths[1] + "    -    " + m_sDeaths[0];
	//	m_fTimer;
}
