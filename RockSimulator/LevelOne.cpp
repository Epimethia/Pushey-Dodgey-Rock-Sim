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

	// Physics stuff
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(800.0f, 450.0f);
	body = world.CreateBody(&bodyDef);
	dynamicBox.SetAsBox(1.0f, 1.0f);
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	body->CreateFixture(&fixtureDef);
	timeStep = 1.0f / 60.0f;
	velocityIterations = 8;
	positionIterations = 3;
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
	m_PlayerOne->SetPosition(glm::vec2(300.0f, 450.0f));
	m_PlayerVec.push_back(m_PlayerOne);
	m_EntityVec.push_back(m_PlayerOne);

	m_PlayerTwo = std::make_shared<PlayerCharacter>();	
	m_PlayerTwo->SetPosition(glm::vec2(1300.0f, 450.0f));
	m_PlayerVec.push_back(m_PlayerTwo);
	m_EntityVec.push_back(m_PlayerTwo);

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
	world.Step(timeStep, velocityIterations, positionIterations);	m_PlayerOne->SetPosition(glm::vec2(body->GetPosition().x, body->GetPosition().y));
	//Reading inputs
	//PLAYER_0 INPUTS
	auto& p0_Controller = CurrentPlayers[0];
	p0_Controller->Vibrate(0, static_cast<int>(1000.0f * m_PlayerOne->GetVibrateRate()));
	if (Input::KeyState['w'] == INPUT_HOLD || p0_Controller->ControllerButtons[BOTTOM_FACE_BUTTON] == INPUT_HOLD) {
		//m_PlayerOne->AddVelocity(50.0f * _DeltaTick);

		glm::vec2 Forward = glm::vec2(m_PlayerOne->GetForwardVec().x, m_PlayerOne->GetForwardVec().y) * 5000.0f;
		body->ApplyForceToCenter(b2Vec2(Forward.x, Forward.y), true);
	}
	if (Input::KeyState['s'] == INPUT_HOLD || p0_Controller->ControllerButtons[LEFT_FACE_BUTTON] == INPUT_HOLD) {
		m_PlayerOne->Brake();
	}
	if (Input::KeyState['a'] == INPUT_HOLD || p0_Controller->normalizedLX < -0.8f) {
		m_PlayerOne->AddRotation(3.0f * _DeltaTick);
	}
	if (Input::KeyState['d'] == INPUT_HOLD || p0_Controller->normalizedLX > 0.8f) {
		m_PlayerOne->AddRotation(-3.0f * _DeltaTick);
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
		m_PlayerTwo->Brake();
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
}

void LevelOne::RenderObjects()
{
	// Render Background
	m_Background->Render(glm::scale(glm::mat4(), glm::vec3(1600.0f, 900.0f, 0.0f))); // spawn in the center

	// Render Object Vectors (check that the vectors are not empty)
	if (!m_EntityVec.empty())
	{
		for (const auto& it : m_EntityVec) it->Render();
	}
}
