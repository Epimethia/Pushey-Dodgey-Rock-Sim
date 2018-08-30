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


LevelOne::LevelOne()
{
	m_Background = std::make_shared<Sprite>();	
	Camera::GetInstance()->SetProj(ki_SCREENWIDTH, ki_SCREENHEIGHT);
	Camera::GetInstance()->Update();

	CurrentPlayers.push_back(std::make_shared<XBOXController>(1));
	CurrentPlayers.push_back(std::make_shared<XBOXController>(2));	
	m_SpawnTime = 0.0f;
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
	m_PlayerOne->SetPosition(b2Vec2(3.0f, 4.5f));
	m_PlayerVec.push_back(m_PlayerOne);
	m_EntityVec.push_back(m_PlayerOne);

	m_PlayerTwo = std::make_shared<PlayerCharacter>();	
	m_PlayerTwo->SetPosition(b2Vec2(13.0f, 4.5f));
	m_PlayerVec.push_back(m_PlayerTwo);
	m_EntityVec.push_back(m_PlayerTwo);	
	m_pContactListener = &MyContactListener::GetInstance();
	m_pContactListener->SetPlayer(&(*m_PlayerOne));
	m_pContactListener->SetPlayer(&(*m_PlayerTwo));
	// Iterate through the entity vector and initialize all objects
	if (!m_EntityVec.empty())
	{
		for (unsigned int i = 0; i < m_EntityVec.size(); i++)
		{
			m_EntityVec[i]->Initialize();
		}
	}
}

void LevelOne::ProcessLevel(float _DeltaTick) {

	// Process Physics
	Physics::GetInstance()->Process();		

	//Reading inputs
	//PLAYER_0 INPUTS
	auto& p0_Controller = CurrentPlayers[0];
	p0_Controller->Vibrate(0, static_cast<int>(1000.0f * m_PlayerOne->GetVibrateRate()));
	if (Input::KeyState['w'] == INPUT_HOLD || p0_Controller->ControllerButtons[BOTTOM_FACE_BUTTON] == INPUT_HOLD) {
		m_PlayerOne->AddVelocity(15.0f * _DeltaTick);		
	}
	if (Input::KeyState['s'] == INPUT_HOLD || p0_Controller->ControllerButtons[LEFT_FACE_BUTTON] == INPUT_HOLD) {
		m_PlayerOne->AddVelocity(-15.0f * _DeltaTick);
	}
	if (Input::KeyState['a'] == INPUT_HOLD || p0_Controller->normalizedLX < -0.8f) {
		m_PlayerOne->AddRotation(1.0f * _DeltaTick);
	}
	if (Input::KeyState['d'] == INPUT_HOLD || p0_Controller->normalizedLX > 0.8f) {
		m_PlayerOne->AddRotation(-1.0f * _DeltaTick);
	}

	//Reading inputs
	//PLAYER_1 INPUTS
	auto& p1_Controller = CurrentPlayers[1];
	//Making the controller vibrate
	p1_Controller->Vibrate(0, static_cast<int>(1000.0f * m_PlayerOne->GetVibrateRate()));
	if (Input::KeyState['8'] == INPUT_HOLD || p1_Controller->ControllerButtons[BOTTOM_FACE_BUTTON] == INPUT_HOLD) {
		m_PlayerTwo->AddVelocity(50.0f * _DeltaTick);
	}
	if (Input::KeyState['5'] == INPUT_HOLD || p1_Controller->ControllerButtons[LEFT_FACE_BUTTON] == INPUT_HOLD) {
		m_PlayerOne->AddVelocity(-50.0f * _DeltaTick);
	}	
	if (Input::KeyState['4'] == INPUT_HOLD || p1_Controller->normalizedLX < -0.9f) {
		m_PlayerTwo->AddRotation(3.0f * _DeltaTick);
	}
	if (Input::KeyState['6'] == INPUT_HOLD || p1_Controller->normalizedLX > 0.9f) {
		m_PlayerTwo->AddRotation(-3.0f * _DeltaTick);
	}

	//Updating the keyboard input
	Input::Update();

	//Updating player controllers
	for (const auto& it : CurrentPlayers) it->Update();

	//Updating the players
	for (const auto& it : m_PlayerVec) it->Update();

	// Spawn Asteroids
	m_SpawnTime += _DeltaTick;
	if (m_SpawnTime > 1.0f)
	{
		std::shared_ptr<Asteroid> TempAsteroid = std::make_shared<Asteroid>();
		TempAsteroid->SetPosition(b2Vec2(-1.0f, 2.5f));
		TempAsteroid->Initialize();		
		m_AsteroidVec.push_back(TempAsteroid);

		// increment spawn timer
		m_SpawnTime = 0.0f;
	}

	// Move Asteroids
	for (unsigned int i = 0; i < m_AsteroidVec.size(); i++)
	{
		m_AsteroidVec[i]->AddVelocity(b2Vec2(1.0f, 0.0f), 50.0f * _DeltaTick);
		// Destroy asteroid if it goes off screen
		if (m_AsteroidVec[i]->GetPosition().x > 20.0f || m_AsteroidVec[i]->GetPosition().y > 20.0f
		 || m_AsteroidVec[i]->GetPosition().x < -20.0f || m_AsteroidVec[i]->GetPosition().y < -20.0f)
		{
			m_AsteroidVec[i]->SetOffScreenBool(true);
		}
	}		

	// Clean up offscreen asteroids
	for (unsigned int i = 0; i < m_AsteroidVec.size(); i++)
	{
		if (m_AsteroidVec[i] != nullptr)
		{
			if (m_AsteroidVec[i]->GetOffScreenBool())
			{
				m_AsteroidVec.erase(m_AsteroidVec.begin() + i);
			}
		}
	}
}

void LevelOne::RenderObjects()
{
	// Render Background
	m_Background->Render(glm::scale(glm::mat4(), glm::vec3(16.0f, 9.0f, 0.0f))); // spawn in the center

	// Render Object Vectors (check that the vectors are not empty)
	if (!m_EntityVec.empty())
	{
		for (const auto& it : m_EntityVec)
		{
			it->Render();
			it->DrawDebug();
		}
	}
	
	if (!m_AsteroidVec.empty())
	{
		for (const auto& it : m_AsteroidVec)
		{
			it->Render();
			it->DrawDebug();
		}
	}  
}
