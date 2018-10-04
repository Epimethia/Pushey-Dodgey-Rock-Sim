// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2018 Media Design School
//
// Author		:	Jasper Lyons
// Email		:	Jasper.Lyo7552@mediadesign.school.nz
// File Name	:	Input.h
// Description	:	Header file defining the Input class
#ifndef __KEYBOARDINPUT_H__
#define __KEYBOARDINPUT_H__
//	Library includes.
#include <vector>
#include <memory>


//	Local includes.
#include "Dependencies\glm\glm.hpp"
#include "Dependencies\glm\gtc\matrix_transform.hpp"
#include "Dependencies\glm\gtc\type_ptr.hpp"


enum InputState
{
	INPUT_FIRST_RELEASE, // First frame of Up state
	INPUT_RELEASED, // Default state (up)
	INPUT_FIRST_PRESS, // First frame of down state
	INPUT_HOLD // Key is held down
};

enum InputMouse
{
	MOUSE_LEFT,
	MOUSE_MIDDLE,
	MOUSE_RIGHT
};

class Input
{
public:
	static std::shared_ptr<Input> GetInstance();
	static void DestroyInstance();
	Input();
	~Input();

	static unsigned char m_iKeyState[256];
	static unsigned char m_iSpecialKeyState[256];
	static unsigned char m_iMouseState[3];

	// Setters
	void SetCursor(int _cursorSetting);

	// Getters
	glm::vec2 GetMousePos();
	glm::vec2 GetMouseWorldPos();

	// Other Functions
	static void Initialize();
	static void Update();
	static void ProcessNormalKeysDown(unsigned char _key, int _x, int _y);
	static void ProcessNormalKeysUp(unsigned char _key, int _x, int _y);
	static void ProcessSpecialKeyDown(int _key, int _x, int _y);
	static void ProcessSpecialKeyUp(int _key, int _x, int _y);
	static void MouseButton(int _button, int _state, int _x, int _y);
	static void MouseInput(int _x, int _y);

private:
	static std::shared_ptr<Input> s_pInstance;
	Input(Input const&) = delete;
	void operator=(Input const&) = delete;

	glm::vec2 m_vMousePos;
};

#endif