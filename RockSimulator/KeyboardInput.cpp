// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2018 Media Design School
//
// Author		:	Jasper Lyons
// Email		:	Jasper.Lyo7552@mediadesign.school.nz
// File Name	:	Input.cpp
// Description	:	Implimentation for the Input class

#include "KeyboardInput.h"
#include "Utilities.h"
#include "Camera.h"
#include <iostream>

std::shared_ptr<Input> Input::s_pInput;
unsigned int Input::m_iKeyState[256];
unsigned int Input::m_iSpecialKeyState[256];
unsigned int Input::m_iMouseState[3];


//// Prototypes
//void LprocessNormalKeysDown(unsigned char _key, int _x, int _y);
//void LprocessNormalKeysUp(unsigned char _key, int _x, int _y);
//void LprocessSpecialKeysDown(int _key, int _x, int _y);
//void LmouseButton(int _button, int _state, int _x, int _y);
//void LmouseInput(int _x, int _y);

//Name:			    GetInstance
//Parameters:		None
//Return Type:		shared input pointer
//Description:		Returns instance
//                  
//                  
std::shared_ptr<Input> Input::GetInstance()
{
	if (!s_pInput)
	{
		s_pInput = std::shared_ptr<Input>(new Input());
	}
	return s_pInput;
}

//Name:			    DestroyInstance
//Parameters:		None
//Return Type:		None
//Description:		Destroys instance
//                  
//                  
void Input::DestroyInstance()
{
	s_pInput.reset();
}

//Name:			    Input destructor
//Parameters:		None
//Return Type:		None
//Description:		Input destructor
//                  
//                  
Input::~Input()
{

}

//Name:			    Input constructor
//Parameters:		None
//Return Type:		None
//Description:		Input constructor
//                  
//                  
Input::Input()
{
}

//Name:			    Initialize
//Parameters:		None
//Return Type:		None
//Description:		Initialize glut input functions
//                  
//                  
void Input::Initialize()
{
	glutSetCursor(GLUT_CURSOR_CROSSHAIR);
	for (int i = 0; i < 256; ++i) {
		m_iKeyState[i] = INPUT_RELEASED;
	}
	for (int i = 0; i < 256; ++i) {
		m_iSpecialKeyState[i] = INPUT_RELEASED;
	}
	for (int i = 0; i < 3; ++i) {
		m_iMouseState[i] = INPUT_RELEASED;
	}
}

//Name:			    Update
//Parameters:		None
//Return Type:		None
//Description:		Updates the keystate array
//                  
//                  
void Input::Update()
{
	//Running the OpenGL input functions
	glutKeyboardFunc(ProcessNormalKeysDown);
	glutKeyboardUpFunc(ProcessNormalKeysUp);
	glutSpecialFunc(ProcessSpecialKeyDown);
	glutSpecialUpFunc(ProcessSpecialKeyUp);
	
	//glutPassiveMotionFunc(LprocessNormalKeysDown);
	//glutMotionFunc(LmouseInput);
	//glutMouseFunc(LmouseButton);

	//Processing all of the keys
	for (int i = 0; i < 256; i++)
	{
		if (m_iKeyState[i] == INPUT_FIRST_PRESS)
		{
			m_iKeyState[i] = INPUT_HOLD;
		}
		else if (m_iKeyState[i] == INPUT_FIRST_RELEASE) {
			m_iKeyState[i] = INPUT_RELEASED;
		}
	}

	//Processing all of the special keys
	for (int i = 0; i < 256; i++)
	{
		if (m_iSpecialKeyState[i] == INPUT_FIRST_PRESS)
		{
			m_iSpecialKeyState[i] = INPUT_HOLD;
		}
		else if (m_iSpecialKeyState[i] == INPUT_FIRST_RELEASE) {
			m_iSpecialKeyState[i] = INPUT_RELEASED;
		}
	}

	// Processing mouse buttons
	for (int i = 0; i < 3; i++)
	{
		if (m_iMouseState[i] == INPUT_FIRST_PRESS)
		{
			m_iMouseState[i] = INPUT_HOLD;
		}
	}
}

//Name:			    ProcessNormalKeysDown
//Parameters:		uchar key, int x and y
//Return Type:		None
//Description:		Processes normal key down states
//                  
//                  
void Input::ProcessNormalKeysDown(unsigned char _key, int _x, int _y)
{
	m_iKeyState[_key] = INPUT_FIRST_PRESS;
}

//Name:			    ProcessNormalKeysUp
//Parameters:		uchar key, x and y
//Return Type:		None
//Description:		Processes normal key up states
//                  
//                  
void Input::ProcessNormalKeysUp(unsigned char _key, int _x, int _y)
{
	m_iKeyState[_key] = INPUT_FIRST_RELEASE;
}

//Name:			    ProcessSpecialKeys
//Parameters:		int key, x and y
//Return Type:		None
//Description:		Processes special key states
//                  
//                  
void Input::ProcessSpecialKeyDown(int _key, int _x, int _y)
{
	m_iSpecialKeyState[_key] = INPUT_FIRST_PRESS;
}

void Input::ProcessSpecialKeyUp(int _key, int _x, int _y)
{
	m_iSpecialKeyState[_key] = INPUT_FIRST_RELEASE;
}

//Name:			    MouseButton
//Parameters:		int button, state, x and y
//Return Type:		None
//Description:		Processes the mouse button down and up states
//                  
//                  
void Input::MouseButton(int _button, int _state, int _x, int _y)
{
	if (_button < 3)
	{
		if (_state == GLUT_DOWN)
		{
			m_iMouseState[_button] = INPUT_FIRST_PRESS;
		}
		else if (_state == GLUT_UP)
		{
			m_iMouseState[_button] = INPUT_RELEASED;
		}
	}
}

//Name:			    SetCursor
//Parameters:		int cursor setting
//Return Type:		None
//Description:		Sets the cursor visibility state
//                  
//                  
void Input::SetCursor(int _cursorSetting)
{
	glutSetCursor(_cursorSetting);
}

//Name:			    GetMousePos
//Parameters:		None
//Return Type:		glm::vec2
//Description:		Returns the mouse pos vector2
//                  
//                  
glm::vec2 Input::GetMousePos()
{
	// Converts XY to NDC and returns
	glm::vec2 NDC = glm::vec2();
	NDC.x = (2.0f * m_vMousePos.x) / static_cast<float>(ki_SCREENWIDTH) - 1.0f;
	NDC.y = 1.0f - (2.0f * m_vMousePos.y) / static_cast<float>(ki_SCREENHEIGHT);
	return NDC;
}

glm::vec2 Input::GetMouseWorldPos()
{
	//screen pos
	glm::vec2 normalizedScreenPos = glm::vec2((2.0f * m_vMousePos.x) / static_cast<float>(ki_SCREENWIDTH) - 1.0f,
		1.0f - (2.0f * m_vMousePos.y) / static_cast<float>(ki_SCREENHEIGHT));

	//screenpos to Proj Space
	glm::vec4 clipCoords = glm::vec4(normalizedScreenPos.x, normalizedScreenPos.y, -1.0f, 1.0f);

	//Proj Space to eye space
	glm::mat4 invProjMat = glm::inverse(Camera::GetInstance()->GetProj());
	glm::vec4 eyeCoords = invProjMat * clipCoords;
	eyeCoords = glm::vec4(eyeCoords.x, eyeCoords.y, -1.0f, 0.0f);

	//eyespace to world space
	glm::mat4 invViewMat = glm::inverse(Camera::GetInstance()->GetView());
	glm::vec4 rayWorld = invViewMat * eyeCoords;
	glm::vec3 rayDirection = glm::normalize(glm::vec3(rayWorld));

	return glm::vec2(rayWorld.x, rayWorld.y);
}