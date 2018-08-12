#include "LevelOne.h"
#include "Sprite.h"
#include "Camera.h"
#include "Utilities.h"

LevelOne::LevelOne()
{
	m_Background = std::make_shared<Sprite>();
	m_Camera = std::make_shared<Camera>();
	m_Camera->SetProj(ki_SCREENWIDTH, ki_SCREENHEIGHT);
	m_Camera->Update();
}

LevelOne::~LevelOne()
{
}

void LevelOne::InitializeObjects()
{
	// Initialize Scene Background	
	m_Background->Initialize("Resources/Images/Rayman.jpg");

	// Initialize Other Objects..
}

void LevelOne::RenderObjects()
{
	// Render Background
	m_Background->Render();

	// Render Object Vectors (check that the vectors are not empty)
	
}
