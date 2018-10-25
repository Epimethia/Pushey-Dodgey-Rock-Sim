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
	m_pPointsSpriteArr[0] = std::make_shared<Sprite>();
	m_pPointsSpriteArr[1] = std::make_shared<Sprite>();

	m_pPOne_OnePoint = std::make_shared<Sprite>();
	m_pPTwo_OnePoint = std::make_shared<Sprite>();
	m_pTwoPoints = std::make_shared<Sprite>();
	m_pZeroPoints = std::make_shared<Sprite>();


	Camera::GetInstance()->SetProj(ki_SCREENWIDTH, ki_SCREENHEIGHT);
	Camera::GetInstance()->Update();

	m_pClock = &(*CClock::GetInstance());

	m_pPlayerOneController = std::make_shared<XBOXController>(1);
	m_pPlayerTwoController = std::make_shared<XBOXController>(2);
	m_fSpawnTime = 0.0f;
	m_fTimeRemaining = 90;
	m_fTimerTick = 0.0f;
}

LevelOne::~LevelOne()
{
	// Clearing Vectors
	m_vpAsteroidVec0.clear();
	m_vpAsteroidVec1.clear();
	m_vpEntityVec.clear();
	
	// Resetting Singular Objects
	m_pPlayerOne.reset();
	m_pPlayerTwo.reset();
	m_pP1HealthBar.reset();
	m_pP2HealthBar.reset();
	m_pPlayerOneController.reset();
	m_pPlayerTwoController.reset();
	m_pBackground.reset();
	m_pCamera.reset();
	m_pHUDFrame.reset();
	m_pPointsSpriteArr[0].reset();
	m_pPointsSpriteArr[1].reset();
	m_pPOne_OnePoint.reset();
	m_pPTwo_OnePoint.reset();
	m_pZeroPoints.reset();
	m_pTimeDisplay.reset();	
	
	// Dealing with raw pointers
	MyContactListener::DestroyInstance();
	
}

void LevelOne::Init()
{
	// Initialize Scene Background	
	m_pBackground->Initialize("Resources/Images/New Background.png");

	//	Initializing the HUD frame
	m_pHUDFrame->Initialize("Resources/Images/HUD/HUD_Frame.png");

	if (!m_pPlayerOne)
	{
		m_pPlayerOne = std::make_shared<PlayerCharacter>();
	}	
	m_pPlayerOne->SetPosition(b2Vec2(3.0f, 4.5f));
	m_pPlayerOne->SetSpawnPosition(glm::vec3(3.0f, 4.5f, 0.0f));
	m_pPlayerOne->SetPlayerTexture("Resources/Images/Player_Sprite.png");
	m_pPlayerOne->LinkScore(&m_sDeathCount[0]);
	m_pPlayerOne->Initialize();
	m_vpEntityVec.push_back(m_pPlayerOne);

	if (!m_pP1HealthBar)
	{
		m_pP1HealthBar = std::make_shared<C_HealthBar>(
			"Resources/Images/HUD/Player_One_Healthbar.png",
			"Resources/Images/HUD/Player_One_Half.png"
			);
	}	
	m_pP1HealthBar->SetPosition(glm::vec3(1.88f, 8.55f, 0.0f));
	m_pP1HealthBar->SetScale(glm::vec3(1.67f, 0.23f, 0.0f));

	if (!m_pPlayerTwo)
	{
		m_pPlayerTwo = std::make_shared<PlayerCharacter>();
	}
	m_pPlayerTwo->SetPosition(b2Vec2(13.0f, 4.5f));
	m_pPlayerTwo->SetSpawnPosition(glm::vec3(13.0f, 4.5f, 0.0f));
	m_pPlayerTwo->SetPlayerTexture("Resources/Images/Player_Sprite2.png");
	m_vpEntityVec.push_back(m_pPlayerTwo);
	m_pPlayerTwo->Initialize();
	m_pPlayerTwo->LinkScore(&m_sDeathCount[1]);

	if (!m_pP2HealthBar)
	{
		m_pP2HealthBar = std::make_shared<C_HealthBar>(
			"Resources/Images/HUD/Player_Two_Healthbar.png",
			"Resources/Images/HUD/Player_Two_Half.png"
			);
	}
	m_pP2HealthBar->SetPosition(glm::vec3(14.11f, 8.55f, 0.0f));
	m_pP2HealthBar->SetScale(glm::vec3(1.67f, 0.23f, 0.0f));

	m_pPOne_OnePoint->Initialize("Resources/Images/HUD/P1_OnePoint.png");
	m_pPTwo_OnePoint->Initialize("Resources/Images/HUD/P2_OnePoint.png");
	m_pTwoPoints->Initialize("Resources/Images/HUD/TwoPoint.png");
	m_pZeroPoints->Initialize("Resources/Images/HUD/ZeroPoint.png");

	m_pPointsSpriteArr[0] = m_pZeroPoints;
	m_pPointsSpriteArr[1] = m_pZeroPoints;

	//	Initializing the timer text to appear at the top of the screen
	if (!m_pTimeDisplay)
	{
		m_pTimeDisplay =
			std::make_shared<TextLabel>(
				"1:30",	//Timer value itself
				"Resources/Fonts/Thirteen-Pixel-Fonts.ttf",				//Font
				glm::vec2(700.0f, 790.0f)								//Position of the timer
				);
	}	
	m_pTimeDisplay->SetScale(1.9f);

	//	Contact listeners to handle collision between Box2D entities
	m_pContactListener = &MyContactListener::GetInstance();
	m_pContactListener->SetPlayer(&(*m_pPlayerOne));
	m_pContactListener->SetPlayer(&(*m_pPlayerTwo));

	//Starting the sound manager to play some music
	SoundManager::GetInstance()->StartLevelBGM();

	/// Checking reference counts
	//std::cout << "\n m_pPlayerOne: " << m_pPlayerOne.use_count();
	//std::cout << "\n m_pPlayerTwo: " << m_pPlayerTwo.use_count();
	//std::cout << "\n m_pP1HealthBar: " << m_pP1HealthBar.use_count();
	//std::cout << "\n m_pP2HealthBar: " << m_pP2HealthBar.use_count();
	//std::cout << "\n m_pPlayerOneController: " << m_pPlayerOneController.use_count();
	//std::cout << "\n m_pPlayerTwoController: " << m_pPlayerTwoController.use_count();
	//std::cout << "\n m_pBackground: " << m_pBackground.use_count();
	//std::cout << "\n m_pCamera: " << m_pCamera.use_count();
	//std::cout << "\n m_pHUDFrame: " << m_pHUDFrame.use_count();
	//std::cout << "\n m_pPointsSpriteArr: " << m_pPointsSpriteArr[0].use_count();
	//std::cout << "\n m_pPointsSpriteArr: " << m_pPointsSpriteArr[1].use_count();
	//std::cout << "\n m_pPOne_OnePoint: " << m_pPOne_OnePoint.use_count();
	//std::cout << "\n m_pPTwo_OnePoint: " << m_pPTwo_OnePoint.use_count();
	//std::cout << "\n m_pZeroPoints: " << m_pZeroPoints.use_count();
	//std::cout << "\n m_pTimeDisplay: " << m_pTimeDisplay.use_count();
}

void LevelOne::ProcessLevel(const float& _DeltaTick)
{
	// Process the timer
	ProcessTimer(_DeltaTick);
	
	//	If the timer has ticked down to 0, check the player health values and award points accordingly
	if (0.0f >= m_fTimeRemaining)
	{
		//	If neither player has died, the game awards a point to the player with the most health.
		//	Returns once processing is finished

		if (m_pPlayerOne->GetHealth() > m_pPlayerTwo->GetHealth())
		{
			// Reset timer
			m_fTimeRemaining = 0;

			// Reset players
			m_pPlayerTwo->Respawn();
			m_pPlayerOne->ResetPlayer();

			// Reset asteroids
			m_vpAsteroidVec0.clear();
			m_vpAsteroidVec1.clear();
			m_fSpawnTime = 0.0f;
		}

		else if (m_pPlayerTwo->GetHealth() > m_pPlayerOne->GetHealth())
		{
			// Reset timer
			m_fTimeRemaining = 0;

			// Reset players
			m_pPlayerOne->Respawn();
			m_pPlayerTwo->ResetPlayer();

			// Reset asteroids
			m_vpAsteroidVec0.clear();
			m_vpAsteroidVec1.clear();
			m_fSpawnTime = 0.0f;

		}	

		//	If both players are still alive but have equivalent health, the game just resets
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
			m_fTimeRemaining = 90;	
		}
		UpdateScoreValues();
		return;
	}

	// Process Physics
	Physics::GetInstance()->Process(_DeltaTick);

	//	Processing the player input
	ProcessPlayerInput(_DeltaTick);

	//	Updating the keyboard input
	Input::Update();

	//	Updating controller input
	m_pPlayerOneController->Update();
	m_pPlayerTwoController->Update();

	//	Updating the players
	m_pPlayerOne->Update();
	m_pPlayerTwo->Update();

	// Checking for player death
	CheckPlayerDeaths(_DeltaTick);

	// Spawn Asteroids
	SpawnAsteroids(_DeltaTick);

	// Move Asteroids
	MoveAsteroids(_DeltaTick);

	// Clean up offscreen asteroids
	OffscreenCleanup();

	//	Process the SoundManager
	SoundManager::GetInstance()->Update();

	// Scene Transition
	if (SceneManager::GetInstance()->GetState())
	{
		// Fade out 
		float fSceneOpacity = SceneManager::GetInstance()->GetOpacity();
		if (0.0f < fSceneOpacity)
		{
			SceneManager::GetInstance()->SetOpacity(fSceneOpacity - (_DeltaTick));
		}
		else
		{
			SceneManager::GetInstance()->SetCurrentScene(END_SCENE);			
			SceneManager::GetInstance()->SetOpacity(1.0f);
			SceneManager::GetInstance()->SetTransitioning(false);
		}
	}
}

void LevelOne::ProcessTimer(const float& _DeltaTick)
{

	//	Increments time by the elapsed time since last frame
	if (1.0f <= m_fTimerTick)
	{
		m_fTimeRemaining--;
		m_fTimerTick = 0.0f;
		SoundManager::GetInstance()->SoundTimerTick(0);

		//	If the timer is above 90 seconds, we need to convert into form M:SS, so we minus 60 from it
		//	and put "1:--" in front of it
		if (70 <= m_fTimeRemaining)
		{
			m_pTimeDisplay->SetText("1:" + std::to_string(static_cast<short>(m_fTimeRemaining - 60)));
		}

		//	If the timer is between 1:00 and 1:10, we need to change it so that it is "1:0-" instead
		else if (70 <= m_fTimeRemaining && 60 < m_fTimeRemaining)
		{
			m_pTimeDisplay->SetText("1:0" + std::to_string(static_cast<short>(m_fTimeRemaining - 60)));
		}

		//	If the timer has less than 60s left, we change the timer to "0:--"
		else if (60 >= m_fTimeRemaining && 10 < m_fTimeRemaining)
		{
			m_pTimeDisplay->SetText("0:" + std::to_string(static_cast<short>(m_fTimeRemaining)));
		}

		//	If the timer has less than 10s left, we change it one final time to "0:0-"
		else
		{
			m_pTimeDisplay->SetText("0:0" + std::to_string(static_cast<short>(m_fTimeRemaining)));
		}
	}
	else
	{
		m_fTimerTick += _DeltaTick;
	}

	
}

void LevelOne::SpawnAsteroids(const float& _DeltaTick)
{
	int vec0Size = m_vpAsteroidVec0.size();
	int vec1Size = m_vpAsteroidVec1.size();

	m_fSpawnTime += _DeltaTick;
	if (1.0f < m_fSpawnTime)
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

				// Unit Testing
				if (kb_UNITTESTS)
				{
					// Checking that spawning asteroids worked
					assert(UnitTests::SizeIncreaseCheck(vec0Size, m_vpAsteroidVec0.size()));
				}
				break;
			}
			case 1:
			{
				// Right to left asteroid
				std::shared_ptr<Asteroid> TempAsteroid = std::make_shared<Asteroid>(static_cast<float>(dis2(gen)));
				TempAsteroid->SetPosition(b2Vec2(17.0f, static_cast<float>(dis(gen))));
				TempAsteroid->Initialize();
				m_vpAsteroidVec1.push_back(TempAsteroid);

				// Unit Testing
				if (kb_UNITTESTS)
				{
					// Checking that spawning asteroids worked				
					assert(UnitTests::SizeIncreaseCheck(vec1Size, m_vpAsteroidVec1.size()));
				}
				break;
			}
			default: break;
		}	
	// increment spawn timer
		m_fSpawnTime = 0.0f;
	}
}

void LevelOne::OffscreenCleanup()
{
	for (unsigned int i = 0; i < m_vpAsteroidVec0.size(); i++)
	{
		if (nullptr != m_vpAsteroidVec0[i])
		{
			if (m_vpAsteroidVec0[i]->GetOffScreenBool())
			{
				m_vpAsteroidVec0.erase(m_vpAsteroidVec0.begin() + i);
			}
		}
	}
	for (unsigned int i = 0; i < m_vpAsteroidVec1.size(); i++)
	{
		if (nullptr != m_vpAsteroidVec1[i])
		{
			if (m_vpAsteroidVec1[i]->GetOffScreenBool())
			{
				m_vpAsteroidVec1.erase(m_vpAsteroidVec1.begin() + i);
			}
		}
	}
}

void LevelOne::MoveAsteroids(const float& _DeltaTick)
{
	// Left to right asteroids
	for (unsigned int i = 0; i < m_vpAsteroidVec0.size(); i++)
	{
		m_vpAsteroidVec0[i]->AddVelocity(b2Vec2(1.0f, 0.0f), 40.0f * _DeltaTick);
		// Destroy asteroid if it goes off screen
		if (20.0f < m_vpAsteroidVec0[i]->GetPosition().x || 20.0f < m_vpAsteroidVec0[i]->GetPosition().y
			|| -20.0f > m_vpAsteroidVec0[i]->GetPosition().x || -20.0f > m_vpAsteroidVec0[i]->GetPosition().y)
		{
			m_vpAsteroidVec0[i]->SetOffScreenBool(true);
		}
	}
	// Right to left asteroids
	for (unsigned int i = 0; i < m_vpAsteroidVec1.size(); i++)
	{
		m_vpAsteroidVec1[i]->AddVelocity(b2Vec2(-1.0f, 0.0f), 40.0f * _DeltaTick);
		// Destroy asteroid if it goes off screen
		if (20.0f < m_vpAsteroidVec1[i]->GetPosition().x || 20.0f < m_vpAsteroidVec1[i]->GetPosition().y
			|| -20.0f > m_vpAsteroidVec1[i]->GetPosition().x || -20.0f > m_vpAsteroidVec1[i]->GetPosition().y)
		{
			m_vpAsteroidVec1[i]->SetOffScreenBool(true);
		}
	}
}

void LevelOne::CheckPlayerDeaths(const float& _DeltaTick)
{
	// Unit Testing
	if (kb_UNITTESTS)
	{
		assert(UnitTests::ValidCheck(m_pPlayerOne.get()));
		assert(UnitTests::ValidCheck(m_pPlayerTwo.get()));
	}

	//	Checks if either player has died
	if (m_pPlayerOne->GetPlayerDead())
	{
		// Reset timer
		m_fTimeRemaining = 0;

		// Reset players
		m_pPlayerOne->Respawn();
		m_pPlayerTwo->ResetPlayer();
		m_pP1HealthBar->SetHealth(HEALTH::FULL);
		m_pP2HealthBar->SetHealth(HEALTH::FULL);

		// Reset asteroids
		m_vpAsteroidVec0.clear();
		m_vpAsteroidVec1.clear();
		m_fSpawnTime = 0.0f;

		// Check for win
		if (2 < m_sDeathCount[0])
		{			
			SceneManager::GetInstance()->SetTransitioning(true);
			SceneManager::GetInstance()->InitializeScene(END_SCENE);
			SceneManager::GetInstance()->SetWinner(1);
			SoundManager::GetInstance()->StopBGM();
		}

		// Check that vectors were cleared properly
		if (kb_UNITTESTS)
		{
			assert(m_vpAsteroidVec0.empty());
			assert(m_vpAsteroidVec1.empty());
		}
	}
	// Checking for player death..
	if (m_pPlayerTwo->GetPlayerDead())
	{
		// Reset timer
		m_fTimeRemaining = 0;

		// Reset players
		m_pPlayerTwo->Respawn();
		m_pPlayerOne->ResetPlayer();
		m_pP2HealthBar->SetHealth(HEALTH::FULL);
		m_pP1HealthBar->SetHealth(HEALTH::FULL);


		// Reset asteroids
		m_vpAsteroidVec0.clear();
		m_vpAsteroidVec1.clear();
		m_fSpawnTime = 0.0f;

		// Increment score

		// Check for win
		if (2 < m_sDeathCount[1])
		{				
			SceneManager::GetInstance()->SetTransitioning(true);
			SceneManager::GetInstance()->InitializeScene(END_SCENE);
			SoundManager::GetInstance()->StopBGM();
			SceneManager::GetInstance()->SetWinner(0);			
		}

		// Check that vectors were cleared properly
		if (kb_UNITTESTS)
		{
			assert(m_vpAsteroidVec0.empty());
			assert(m_vpAsteroidVec1.empty());
		}
	}

	//	Updating score marks
	UpdateScoreValues();
}

void LevelOne::UpdateScoreValues()
{
	//if p1's death count is 1, set p2's score counter to 1 point
	if (1 == m_sDeathCount[0])
	{
		m_pPointsSpriteArr[1] = m_pPTwo_OnePoint;
	}
	//if p1's death count is 2, set p2's score counter to 2 points
	else if (2 == m_sDeathCount[0])
	{
		m_pPointsSpriteArr[1] = m_pTwoPoints;
	}
	//otherwise set it to 0 points
	else		
	{
		m_pPointsSpriteArr[1] = m_pZeroPoints;
	}

	//if p2's death count is 1, set p1's score counter to 1 point
	if (1 == m_sDeathCount[1])
	{
		m_pPointsSpriteArr[0] = m_pPOne_OnePoint;
	}
	//if p2's death count is 2, set p1's score counter to 2 points
	else if (2 == m_sDeathCount[1])
	{
		m_pPointsSpriteArr[0] = m_pTwoPoints;
	}
	//otherwise set it to 0 points
	else		
	{
		m_pPointsSpriteArr[0] = m_pZeroPoints;
	}

}

void LevelOne::ProcessPlayerInput(const float& _DeltaTick)
{
	//Reading inputs
	//PLAYER_1 INPUTS
	auto& p1_Controller = m_pPlayerOneController;
	p1_Controller->Vibrate(0, static_cast<int>(1000.0f * m_pPlayerOne->GetVibrateRate()));

	//accelerate while w key is held
	if (Input::m_iKeyState['w'] == INPUT_HOLD || p1_Controller->ControllerButtons[BOTTOM_FACE_BUTTON] == INPUT_HOLD) {		
		m_pPlayerOne->AddVelocity(40.0f * _DeltaTick);
		SoundManager::GetInstance()->SetEngineVolume(0, m_pPlayerOne->GetCurrentSpeed() / 50.0f);
	}
	//if first press, begin the engine sound
	if (INPUT_FIRST_PRESS == Input::m_iKeyState['w'] || INPUT_FIRST_PRESS == p1_Controller->ControllerButtons[BOTTOM_FACE_BUTTON])
	{
		m_pPlayerOne->GetPlayerAccelerate() = !m_pPlayerOne->GetPlayerAccelerate();
		SoundManager::GetInstance()->ToggleEngineSound(0, m_pPlayerOne->GetPlayerAccelerate());
	}
	//if released, stop the engine sound
	if (INPUT_FIRST_RELEASE == Input::m_iKeyState['w'] || INPUT_FIRST_RELEASE == p1_Controller->ControllerButtons[BOTTOM_FACE_BUTTON])
	{
		m_pPlayerOne->GetPlayerAccelerate() = !m_pPlayerOne->GetPlayerAccelerate();
		SoundManager::GetInstance()->ToggleEngineSound(0, m_pPlayerOne->GetPlayerAccelerate());
	}
	//shoot when spacebar
	if (INPUT_FIRST_PRESS == Input::m_iKeyState[32] || INPUT_FIRST_PRESS == p1_Controller->ControllerButtons[LEFT_FACE_BUTTON])
	{
		m_pPlayerOne->Shoot();
	}

	//turn when a/d
	if (INPUT_HOLD == Input::m_iKeyState['a'] || -0.8f > p1_Controller->normalizedLX)
	{
		m_pPlayerOne->AddRotation(3.0f * _DeltaTick);
	}
	if (INPUT_HOLD == Input::m_iKeyState['d'] || 0.8f < p1_Controller->normalizedLX)
	{
		m_pPlayerOne->AddRotation(-3.0f * _DeltaTick);
	}

	//PLAYER_2 INPUTS
	auto& p2_Controller = m_pPlayerTwoController;
	//Making the controller vibrate
	p2_Controller->Vibrate(0, static_cast<int>(1000.0f * m_pPlayerTwo->GetVibrateRate()));
	//accelerate while 8 key is held
	if (INPUT_HOLD == Input::m_iKeyState['8'] || INPUT_HOLD == p2_Controller->ControllerButtons[BOTTOM_FACE_BUTTON])
	{
		m_pPlayerTwo->AddVelocity(40.0f * _DeltaTick);
		SoundManager::GetInstance()->SetEngineVolume(1, m_pPlayerTwo->GetCurrentSpeed() / 50.0f);
	}
	//if first press, begin the engine sound
	if (INPUT_FIRST_PRESS == Input::m_iKeyState['8'] || INPUT_FIRST_PRESS == p2_Controller->ControllerButtons[BOTTOM_FACE_BUTTON])
	{
		m_pPlayerTwo->GetPlayerAccelerate() = !m_pPlayerTwo->GetPlayerAccelerate();
		SoundManager::GetInstance()->ToggleEngineSound(1, m_pPlayerTwo->GetPlayerAccelerate());
	}
	//if released, stop the engine sound
	if (INPUT_FIRST_RELEASE == Input::m_iKeyState['8'] || INPUT_FIRST_RELEASE == p2_Controller->ControllerButtons[BOTTOM_FACE_BUTTON])
	{
		m_pPlayerTwo->GetPlayerAccelerate() = !m_pPlayerTwo->GetPlayerAccelerate();
		SoundManager::GetInstance()->ToggleEngineSound(1, m_pPlayerTwo->GetPlayerAccelerate());
	}

	if (INPUT_FIRST_PRESS == Input::m_iKeyState['0'] || INPUT_FIRST_PRESS == p2_Controller->ControllerButtons[LEFT_FACE_BUTTON])
	{
		m_pPlayerTwo->Shoot();
	}

	if (INPUT_HOLD == Input::m_iKeyState['4'] && INPUT_HOLD == Input::m_iKeyState['6'])
	{
		//	Do Nothing.
	}
	else if (INPUT_HOLD == Input::m_iKeyState['4'] || -0.8f > p2_Controller->normalizedLX)
	{
		m_pPlayerTwo->AddRotation(3.0f * _DeltaTick);
	}
	else if (INPUT_HOLD == Input::m_iKeyState['6'] || 0.8f < p2_Controller->normalizedLX)
	{
		m_pPlayerTwo->AddRotation(-3.0f * _DeltaTick);
	}

	//If player health is less than or equal to 50%, swap to the 50% sprite
	if (50.0f >= m_pPlayerOne->GetHealth())
	{
		m_pP1HealthBar->SetHealth(HEALTH::HALF);
	}
	
	if (50.0f >= m_pPlayerTwo->GetHealth())
	{
		m_pP2HealthBar->SetHealth(HEALTH::HALF);
	}
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
	
	m_pPointsSpriteArr[0]->Render(glm::translate(glm::mat4(), glm::vec3(5.8f, 8.58f, 0.0f))* glm::scale(glm::mat4(), glm::vec3(0.585f, 0.115f, 0.0f)));
	m_pPointsSpriteArr[1]->Render(glm::translate(glm::mat4(), glm::vec3(10.2f, 8.58f, 0.0f))* glm::scale(glm::mat4(), glm::vec3(0.585f, 0.115f, 0.0f)));

	m_pP1HealthBar->Render();
	m_pP2HealthBar->Render();

	m_pHUDFrame->Render(glm::translate(glm::mat4(), glm::vec3(8.0f, 4.5f, 0.0f)) *  glm::scale(glm::mat4(), glm::vec3(8.0f, 4.5f, 0.0f)));
	m_pTimeDisplay->Render();
}

