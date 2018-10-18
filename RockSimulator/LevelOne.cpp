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
#include "SceneManager.h"

LevelOne::LevelOne()
{
	m_pBackground = std::make_shared<Sprite>();	
	m_pHUDFrame = std::make_shared<Sprite>();

	Camera::GetInstance()->SetProj(ki_SCREENWIDTH, ki_SCREENHEIGHT);
	Camera::GetInstance()->Update();
	SoundManager::GetInstance()->Initialize();

	m_pClock = &(*CClock::GetInstance());

	m_pPlayerOneController = std::make_shared<XBOXController>(1);
	m_pPlayerTwoController = std::make_shared<XBOXController>(2);
	m_fSpawnTime = 0.0f;
}

LevelOne::~LevelOne()
{
	m_vpAsteroidVec0.clear();
	m_vpAsteroidVec1.clear();
	m_vpEntityVec.clear();
	m_pPlayerOne.reset();
	m_pPlayerTwo.reset();
	m_pP1HealthBar.reset();
	m_pP2HealthBar.reset();
	m_pPlayerOneController.reset();
	m_pPlayerTwoController.reset();
	m_pBackground.reset();	
	m_pP1Score.reset();
	m_pP2Score.reset();
	m_pTimeDisplay.reset();
}

void LevelOne::InitializeObjects()
{
	// Initialize Scene Background	
	m_pBackground->Initialize("Resources/Images/New Background.png");
	m_pHUDFrame->Initialize("Resources/Images/HUD/HUD_Frame.png");

	m_pP1HealthBar = std::make_shared<C_HealthBar>("Resources/Images/HUD/Player_One_Healthbar.png");
	m_pP1HealthBar->SetPosition(glm::vec3(1.88f, 8.55f, 0.0f));
	m_pP1HealthBar->SetScale(glm::vec3(1.67f, 0.23f, 0.0f));

	m_pP2HealthBar = std::make_shared<C_HealthBar>("Resources/Images/HUD/Player_Two_Healthbar.png");
	m_pP2HealthBar->SetPosition(glm::vec3(14.11f, 8.55f, 0.0f));
	m_pP2HealthBar->SetScale(glm::vec3(1.67f, 0.23f, 0.0f));


	// Initialize Other Objects..
	// Push objects to their appropriate vectors
	m_pPlayerOne = std::make_shared<PlayerCharacter>();	
	m_pPlayerOne->SetPosition(b2Vec2(3.0f, 4.5f));	
	m_pPlayerOne->SetSpawnPosition(glm::vec3(3.0f, 4.5f, 0.0f));
	m_pPlayerOne->SetPlayerTexture("Resources/Images/Player_Sprite.png");
	m_vpEntityVec.push_back(m_pPlayerOne);
	m_pPlayerOne->LinkScore(&m_sDeathCount[0]);
	std::string ScoreText1 = "xesrt4574rdyh";//std::to_string(m_sDeathCount[1]);
	m_pP1Score = std::make_shared<TextLabel>(std::to_string(m_sDeathCount[1]), "Resources/fonts/arial.ttf", glm::vec2(400.0f, 700.0f));

	m_pPlayerTwo = std::make_shared<PlayerCharacter>();	
	m_pPlayerTwo->SetPosition(b2Vec2(13.0f, 4.5f));	
	m_pPlayerTwo->SetSpawnPosition(glm::vec3(13.0f, 4.5f, 0.0f));
	m_pPlayerTwo->SetPlayerTexture("Resources/Images/Player_Sprite2.png");
	m_vpEntityVec.push_back(m_pPlayerTwo);
	m_pPlayerTwo->LinkScore(&m_sDeathCount[1]);
	std::string ScoreText2 = std::to_string(m_sDeathCount[0]);
	m_pP2Score = std::make_shared<TextLabel>(std::to_string(m_sDeathCount[0]), "Resources/fonts/arial.ttf", glm::vec2(1200.0f, 700.0f));

	m_pTimeDisplay = std::make_shared<TextLabel>(std::to_string(m_fTimer), "Resources/fonts/arial.ttf", glm::vec2(800.0f, 800.0f));

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
	SoundManager::GetInstance()->StartLevelBGM();
}

void LevelOne::ProcessLevel(float _DeltaTick) {
	// Increment timer
	m_fTimer += _DeltaTick;
	m_pTimeDisplay->SetText(std::to_string(static_cast<unsigned int>(m_fTimer)));
	if (m_fTimer >= 99.0f)
	{
		if (m_pPlayerOne->GetHealth() > m_pPlayerTwo->GetHealth())
		{
			// Reset timer
			m_fTimer = 0.0f;

			// Reset players
			m_pPlayerTwo->Respawn();
			m_pPlayerOne->ResetPlayer();

			// Reset asteroids
			m_vpAsteroidVec0.clear();
			m_vpAsteroidVec1.clear();
			m_fSpawnTime = 0.0f;

			// Increment score
			m_pP1Score->SetText(std::to_string(m_sDeathCount[1]));

			// Check for win
			if (m_sDeathCount[1] > 2)
			{
				SceneManager::GetInstance()->InitializeScene(END_SCENE);
				SceneManager::GetInstance()->SetWinner(0);
				SceneManager::GetInstance()->SetCurrentScene(END_SCENE);
			}
		}
		else if (m_pPlayerTwo->GetHealth() > m_pPlayerOne->GetHealth())
		{
			// Reset timer
			m_fTimer = 0.0f;

			// Reset players
			m_pPlayerOne->Respawn();
			m_pPlayerTwo->ResetPlayer();

			// Reset asteroids
			m_vpAsteroidVec0.clear();
			m_vpAsteroidVec1.clear();
			m_fSpawnTime = 0.0f;

			// Increment score
			m_pP2Score->SetText(std::to_string(m_sDeathCount[0]));

			// Check for win
			if (m_sDeathCount[0] > 2)
			{
				SceneManager::GetInstance()->InitializeScene(END_SCENE);
				SceneManager::GetInstance()->SetWinner(1);
				SceneManager::GetInstance()->SetCurrentScene(END_SCENE);
			}
		}	
		else
		{
			// Reset players
			m_pPlayerOne->ResetPlayer();
			m_pPlayerTwo->ResetPlayer();

			// Reset asteroids
			m_vpAsteroidVec0.clear();
			m_vpAsteroidVec1.clear();
			m_fSpawnTime = 0.0f;

			// Reset timer
			m_fTimer = 0.0f;			
		}
	}

	// Process Physics
	Physics::GetInstance()->Process();	

	//Process SoundManager
	SoundManager::GetInstance()->Update();

	//Processing the player input
	ProcessPlayerInput(_DeltaTick);

	//Updating the keyboard input
	Input::Update();

	//Updating player controllers
	m_pPlayerOneController->Update();
	m_pPlayerTwoController->Update();

	//Updating the players
	m_pPlayerOne->Update();
	m_pPlayerTwo->Update();

	// Checking for player death..
	CheckPlayerDeaths(); 

	// Spawn Asteroids
	SpawnAsteroids(_DeltaTick);

	// Move Asteroids
	MoveAsteroids(_DeltaTick);

	// Clean up offscreen asteroids
	OffscreenCleanup();
}

void LevelOne::SpawnAsteroids(float _DeltaTick)
{
	m_fSpawnTime += _DeltaTick;
	if (m_fSpawnTime > 1.0f)
	{
		std::random_device rd;  //Will be used to obtain a seed for the random number engine
		std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
		std::uniform_real_distribution<> dis(0.0, 9.0);
		std::uniform_real_distribution<> dis2(0.1, 0.5);
		std::uniform_int_distribution<> dis3(0, 1);

		switch (dis3(gen))
		{
		case 0:
		{
			// Left to right asteroid
			std::shared_ptr<Asteroid> TempAsteroid = std::make_shared<Asteroid>(static_cast<float>(dis2(gen)));
			TempAsteroid->SetPosition(b2Vec2(-1.0f, static_cast<float>(dis(gen))));
			TempAsteroid->Initialize();
			m_vpAsteroidVec0.push_back(TempAsteroid);
			break;
		}
		case 1:
		{
			// Right to left asteroid
			std::shared_ptr<Asteroid> TempAsteroid = std::make_shared<Asteroid>(static_cast<float>(dis2(gen)));
			TempAsteroid->SetPosition(b2Vec2(17.0f, static_cast<float>(dis(gen))));
			TempAsteroid->Initialize();
			m_vpAsteroidVec1.push_back(TempAsteroid);
			break;
		}
		}

		// increment spawn timer
		m_fSpawnTime = 0.0f;
	}
}

void LevelOne::OffscreenCleanup()
{
	for (unsigned int i = 0; i < m_vpAsteroidVec0.size(); i++)
	{
		if (m_vpAsteroidVec0[i] != nullptr)
		{
			if (m_vpAsteroidVec0[i]->GetOffScreenBool())
			{
				m_vpAsteroidVec0.erase(m_vpAsteroidVec0.begin() + i);
			}
		}
	}
	for (unsigned int i = 0; i < m_vpAsteroidVec1.size(); i++)
	{
		if (m_vpAsteroidVec1[i] != nullptr)
		{
			if (m_vpAsteroidVec1[i]->GetOffScreenBool())
			{
				m_vpAsteroidVec1.erase(m_vpAsteroidVec1.begin() + i);
			}
		}
	}
}

void LevelOne::MoveAsteroids(float _DeltaTick)
{
	// Left to right asteroids
	for (unsigned int i = 0; i < m_vpAsteroidVec0.size(); i++)
	{
		m_vpAsteroidVec0[i]->AddVelocity(b2Vec2(1.0f, 0.0f), 40.0f * _DeltaTick);
		// Destroy asteroid if it goes off screen
		if (m_vpAsteroidVec0[i]->GetPosition().x > 20.0f || m_vpAsteroidVec0[i]->GetPosition().y > 20.0f
			|| m_vpAsteroidVec0[i]->GetPosition().x < -20.0f || m_vpAsteroidVec0[i]->GetPosition().y < -20.0f)
		{
			m_vpAsteroidVec0[i]->SetOffScreenBool(true);
		}
	}
	// Right to left asteroids
	for (unsigned int i = 0; i < m_vpAsteroidVec1.size(); i++)
	{
		m_vpAsteroidVec1[i]->AddVelocity(b2Vec2(-1.0f, 0.0f), 40.0f * _DeltaTick);
		// Destroy asteroid if it goes off screen
		if (m_vpAsteroidVec1[i]->GetPosition().x > 20.0f || m_vpAsteroidVec1[i]->GetPosition().y > 20.0f
			|| m_vpAsteroidVec1[i]->GetPosition().x < -20.0f || m_vpAsteroidVec1[i]->GetPosition().y < -20.0f)
		{
			m_vpAsteroidVec1[i]->SetOffScreenBool(true);
		}
	}
}


void LevelOne::CheckPlayerDeaths()
{
	if (m_pPlayerOne->GetPlayerDead())
	{
		// Reset timer
		m_fTimer = 0.0f;

		// Reset players
		m_pPlayerOne->Respawn();
		m_pPlayerTwo->ResetPlayer();
		m_pP1HealthBar->SetSprite("Resources/Images/HUD/Player_One_Healthbar.png");
		m_pP2HealthBar->SetSprite("Resources/Images/HUD/Player_Two_Healthbar.png");

		// Reset asteroids
		m_vpAsteroidVec0.clear();
		m_vpAsteroidVec1.clear();
		m_fSpawnTime = 0.0f;

		// Increment score
		m_pP2Score->SetText(std::to_string(m_sDeathCount[0]));

		// Check for win
		if (m_sDeathCount[0] > 2)
		{
			SceneManager::GetInstance()->InitializeScene(END_SCENE);
			SceneManager::GetInstance()->SetWinner(1);
			SceneManager::GetInstance()->SetCurrentScene(END_SCENE);			
		}
	}
	// Checking for player death..
	if (m_pPlayerTwo->GetPlayerDead())
	{
		// Reset timer
		m_fTimer = 0.0f;

		// Reset players
		m_pPlayerTwo->Respawn();
		m_pPlayerOne->ResetPlayer();
		m_pP2HealthBar->SetSprite("Resources/Images/HUD/Player_Two_Healthbar.png");
		m_pP1HealthBar->SetSprite("Resources/Images/HUD/Player_One_Healthbar.png");


		// Reset asteroids
		m_vpAsteroidVec0.clear();
		m_vpAsteroidVec1.clear();
		m_fSpawnTime = 0.0f;

		// Increment score
		m_pP1Score->SetText(std::to_string(m_sDeathCount[1]));

		// Check for win
		if (m_sDeathCount[1] > 2)
		{			
			SceneManager::GetInstance()->InitializeScene(END_SCENE);
			SceneManager::GetInstance()->SetWinner(0);
			SceneManager::GetInstance()->SetCurrentScene(END_SCENE);			
		}
	}
}

void LevelOne::ProcessPlayerInput(float _DeltaTick)
{
	//Reading inputs
	//PLAYER_0 INPUTS
	auto& p1_Controller = m_pPlayerOneController;
	p1_Controller->Vibrate(0, static_cast<int>(1000.0f * m_pPlayerOne->GetVibrateRate()));

	//accelerate while w key is held
	if (Input::m_iKeyState['w'] == INPUT_HOLD || p1_Controller->ControllerButtons[BOTTOM_FACE_BUTTON] == INPUT_HOLD) {
		m_pPlayerOne->AddVelocity(40.0f * _DeltaTick);
		SoundManager::GetInstance()->SetEngineVolume(0, m_pPlayerOne->GetCurrentSpeed() / 50.0f);
	}
	//if first press, begin the engine sound
	if (Input::m_iKeyState['w'] == INPUT_FIRST_PRESS || p1_Controller->ControllerButtons[BOTTOM_FACE_BUTTON] == INPUT_FIRST_PRESS) {
		m_pPlayerOne->GetPlayerAccelerate() = !m_pPlayerOne->GetPlayerAccelerate();
		SoundManager::GetInstance()->ToggleEngineSound(0, m_pPlayerOne->GetPlayerAccelerate());
	}
	//if released, stop the engine sound
	if (Input::m_iKeyState['w'] == INPUT_FIRST_RELEASE || p1_Controller->ControllerButtons[BOTTOM_FACE_BUTTON] == INPUT_FIRST_RELEASE) {
		m_pPlayerOne->GetPlayerAccelerate() = !m_pPlayerOne->GetPlayerAccelerate();
		SoundManager::GetInstance()->ToggleEngineSound(0, m_pPlayerOne->GetPlayerAccelerate());
	}
	//shoot when spacebar
	if (Input::m_iKeyState[32] == INPUT_FIRST_PRESS || p1_Controller->ControllerButtons[LEFT_FACE_BUTTON] == INPUT_FIRST_PRESS) {
		m_pPlayerOne->Shoot();
	}

	//turn when a/d
	if (Input::m_iKeyState['a'] == INPUT_HOLD || p1_Controller->normalizedLX < -0.8f) {
		m_pPlayerOne->AddRotation(3.0f * _DeltaTick);
	}
	if (Input::m_iKeyState['d'] == INPUT_HOLD || p1_Controller->normalizedLX > 0.8f) {
		m_pPlayerOne->AddRotation(-3.0f * _DeltaTick);
	}

	//PLAYER_1 INPUTS
	auto& p2_Controller = m_pPlayerTwoController;
	//Making the controller vibrate
	p2_Controller->Vibrate(0, static_cast<int>(1000.0f * m_pPlayerTwo->GetVibrateRate()));
	//accelerate while 8 key is held
	if (Input::m_iKeyState['8'] == INPUT_HOLD || p2_Controller->ControllerButtons[BOTTOM_FACE_BUTTON] == INPUT_HOLD) {
		m_pPlayerTwo->AddVelocity(40.0f * _DeltaTick);
		SoundManager::GetInstance()->SetEngineVolume(1, m_pPlayerTwo->GetCurrentSpeed() / 50.0f);
	}
	//if first press, begin the engine sound
	if (Input::m_iKeyState['8'] == INPUT_FIRST_PRESS || p2_Controller->ControllerButtons[BOTTOM_FACE_BUTTON] == INPUT_FIRST_PRESS) {
		m_pPlayerTwo->GetPlayerAccelerate() = !m_pPlayerTwo->GetPlayerAccelerate();
		SoundManager::GetInstance()->ToggleEngineSound(1, m_pPlayerTwo->GetPlayerAccelerate());
	}
	//if released, stop the engine sound
	if (Input::m_iKeyState['8'] == INPUT_FIRST_RELEASE || p2_Controller->ControllerButtons[BOTTOM_FACE_BUTTON] == INPUT_FIRST_RELEASE) {
		m_pPlayerTwo->GetPlayerAccelerate() = !m_pPlayerTwo->GetPlayerAccelerate();
		SoundManager::GetInstance()->ToggleEngineSound(1, m_pPlayerTwo->GetPlayerAccelerate());
	}

	if (Input::m_iKeyState['0'] == INPUT_FIRST_PRESS || p2_Controller->ControllerButtons[LEFT_FACE_BUTTON] == INPUT_FIRST_PRESS) {
		m_pPlayerTwo->Shoot();
	}

	if (Input::m_iKeyState['4'] == INPUT_HOLD || p2_Controller->normalizedLX < -0.8f) {
		m_pPlayerTwo->AddRotation(3.0f * _DeltaTick);
	}
	if (Input::m_iKeyState['6'] == INPUT_HOLD || p2_Controller->normalizedLX > 0.8f) {
		m_pPlayerTwo->AddRotation(-3.0f * _DeltaTick);
	}


	//	Update Health.
	//glm::vec3 TempScale = m_pP1HealthBar->GetScale();
	//TempScale.x = 1.0f * (m_pPlayerOne->GetHealth() / 100.0f);
	//m_pP1HealthBar->SetScale(TempScale);
	if (m_pPlayerOne->GetHealth() <= 50.0f) {
		m_pP1HealthBar->SetSprite("Resources/Images/HUD/Player_One_Half.png");
	}
	
	if (m_pPlayerTwo->GetHealth() <= 50.0f) {
		m_pP2HealthBar->SetSprite("Resources/Images/HUD/Player_Two_Half.png");
	}
	//TempScale = m_pP2HealthBar->GetScale();
	//TempScale.x = 1.0f * (m_pPlayerTwo->GetHealth() / 100.0f);
	//m_pP2HealthBar->SetScale(TempScale);
}

void LevelOne::RenderObjects()
{
	// Render Background
	m_pBackground->Render(glm::translate(glm::mat4(), glm::vec3(8.0f, 4.5f, 0.0f)) *  glm::scale(glm::mat4(), glm::vec3(8.0f, 4.5f, 0.0f))); // spawn in the middle

	// Render Object Vectors (check that the vectors are not empty)
	if (!m_vpEntityVec.empty())
	{
		for (const auto& it : m_vpEntityVec)
		{
			it->Render();
		}
	}
	
	if (!m_vpAsteroidVec0.empty())
	{
		for (const auto& it : m_vpAsteroidVec0)
		{
			it->Render();
		}
	}

	if (!m_vpAsteroidVec1.empty())
	{
		for (const auto& it : m_vpAsteroidVec1)
		{
			it->Render();
		}
	}
	
	m_pTimeDisplay->Render();
	m_pP1Score->Render();
	m_pP2Score->Render();
	m_pP1HealthBar->Render();
	m_pP2HealthBar->Render();

	m_pHUDFrame->Render(glm::translate(glm::mat4(), glm::vec3(8.0f, 4.5f, 0.0f)) *  glm::scale(glm::mat4(), glm::vec3(8.0f, 4.5f, 0.0f)));
  
	
	//	Render score.
	//	m_sDeaths[1] + "    -    " + m_sDeaths[0];
	//	m_fTimer;
}

