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
unsigned int Input::m_iKeyState[255];
unsigned int Input::m_iMouseState[3];


// Prototypes
void LprocessNormalKeysDown(unsigned char _key, int _x, int _y);
void LprocessNormalKeysUp(unsigned char _key, int _x, int _y);
void LprocessSpecialKeys(int _key, int _x, int _y);
void LmouseButton(int _button, int _state, int _x, int _y);
void LmouseInput(int _x, int _y);

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
	for (int i = 0; i < 255; ++i) {
		m_iKeyState[i] = INPUT_RELEASED;
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
	glutKeyboardFunc(LprocessNormalKeysDown);
	glutKeyboardUpFunc(LprocessNormalKeysUp);
	glutSpecialFunc(LprocessSpecialKeys);
	glutPassiveMotionFunc(LmouseInput);
	glutMotionFunc(LmouseInput);
	glutMouseFunc(LmouseButton);

	//Processing all of the keys
	for (int i = 0; i < 255; i++)
	{
		if (m_iKeyState[i] == INPUT_FIRST_PRESS)
		{
			m_iKeyState[i] = INPUT_HOLD;
		}
		else if (m_iKeyState[i] == INPUT_FIRST_RELEASE) {
			m_iKeyState[i] = INPUT_RELEASED;
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
void Input::ProcessSpecialKeys(int _key, int _x, int _y)
{
	switch (_key)
	{
	case GLUT_KEY_UP:
	{

		break;
	}
	case GLUT_KEY_DOWN:
	{

		break;
	}
	case GLUT_KEY_LEFT:
	{

		break;
	}
	case GLUT_KEY_RIGHT:
	{

		break;
	}
	}
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

//Name:			    MouseInput
//Parameters:		int x and y
//Return Type:		None
//Description:		Sets the mouseposition 
//                  
//                  
void Input::MouseInput(int _x, int _y)
{
	m_vMousePos = glm::vec2(_x, _y);
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

//Name:			    LprocessNormalKeysDown
//Parameters:		uchar key, x and y
//Return Type:		None
//Description:		Description
//                  
//                  
void LprocessNormalKeysDown(unsigned char _key, int _x, int _y)
{
	Input::GetInstance()->ProcessNormalKeysDown(_key, _x, _y);
}

//Name:			    LprocessNormalKeysUp
//Parameters:		uchar key, int x and y
//Return Type:		None
//Description:		Description
//                  
//                  
void LprocessNormalKeysUp(unsigned char _key, int _x, int _y)
{
	Input::GetInstance()->ProcessNormalKeysUp(_key, _x, _y);
}

//Name:			    LprocessSpecialKeys
//Parameters:		int key, x and y
//Return Type:		None
//Description:		Description
//                  
//                  
void LprocessSpecialKeys(int _key, int _x, int _y)
{
	Input::GetInstance()->ProcessSpecialKeys(_key, _x, _y);
}

//Name:			    LmouseButton
//Parameters:		int button, state, x and y
//Return Type:		None
//Description:		Description
//                  
//                  
void LmouseButton(int _button, int _state, int _x, int _y)
{
	Input::GetInstance()->MouseButton(_button, _state, _x, _y);
}

//Name:			    LmouseInput
//Parameters:		int x and y
//Return Type:		None
//Description:		Description
//                  
//                  
void LmouseInput(int _x, int _y)
{
	Input::GetInstance()->MouseInput(_x, _y);
}

