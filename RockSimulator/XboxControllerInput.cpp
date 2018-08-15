// This Includes //
#include "XboxControllerInput.h"

// Engine Includes //

#include <iostream>

XBOXController::XBOXController(int playerNumber)
{
	// Set the Controller Number
	_controllerNum = playerNumber - 1;
	std::fill(ControllerButtons, ControllerButtons + 14, InputState::INPUT_RELEASED);

	normalizedLX = 0.0f;
}

XINPUT_STATE XBOXController::GetState()
{
	// Zeroise the state
	ZeroMemory(&_controllerState, sizeof(XINPUT_STATE));

	// Get the state
	XInputGetState(_controllerNum, &_controllerState);

	return _controllerState;
}

bool XBOXController::IsConnected()
{
	// Zeroise the state
	ZeroMemory(&_controllerState, sizeof(XINPUT_STATE));

	// Get the state
	DWORD Result = XInputGetState(_controllerNum, &_controllerState);

	if(Result == ERROR_SUCCESS)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void XBOXController::Vibrate(int leftVal, int rightVal)
{
	// Create a Vibraton State
	XINPUT_VIBRATION Vibration;

	// Zeroise the Vibration
	ZeroMemory(&Vibration, sizeof(XINPUT_VIBRATION));

	// Set the Vibration Values
	Vibration.wLeftMotorSpeed = leftVal;
	Vibration.wRightMotorSpeed = rightVal;

	// Vibrate the controller
	XInputSetState(_controllerNum, &Vibration);
}

void XBOXController::Update()
{
	int iCurrentButton = 0;
	for (int i = XINPUT_GAMEPAD_DPAD_UP; i <= XINPUT_GAMEPAD_RIGHT_SHOULDER; i *= 2)
	{
		if (GetState().Gamepad.wButtons & i)
		{
			if (ControllerButtons[iCurrentButton] == InputState::INPUT_FIRST_PRESS)
			{
				ControllerButtons[iCurrentButton] = InputState::INPUT_HOLD;
			}
			else if (ControllerButtons[iCurrentButton] != InputState::INPUT_HOLD)
			{
				ControllerButtons[iCurrentButton] = InputState::INPUT_FIRST_PRESS;
				std::cout << iCurrentButton << " Pressed\n";
			}
		}
		else
		{
			if (ControllerButtons[iCurrentButton] == InputState::INPUT_HOLD)
			{
				ControllerButtons[iCurrentButton] = InputState::INPUT_FIRST_RELEASE;
			}
			else if (ControllerButtons[iCurrentButton] == InputState::INPUT_FIRST_RELEASE)
			{
				ControllerButtons[iCurrentButton] = InputState::INPUT_RELEASED;
			}
		}
		iCurrentButton++;
	}
	for (int i = XINPUT_GAMEPAD_A; i <= XINPUT_GAMEPAD_Y; i *= 2)
	{
		if (GetState().Gamepad.wButtons & i)
		{
			if (ControllerButtons[iCurrentButton] == InputState::INPUT_FIRST_PRESS)
			{
				ControllerButtons[iCurrentButton] = InputState::INPUT_HOLD;
			}
			else if (ControllerButtons[iCurrentButton] != InputState::INPUT_HOLD)
			{
				ControllerButtons[iCurrentButton] = InputState::INPUT_FIRST_PRESS;
			}
		}
		else
		{
			if (ControllerButtons[iCurrentButton] == InputState::INPUT_HOLD)
			{
				ControllerButtons[iCurrentButton] = InputState::INPUT_FIRST_RELEASE;
			}
			else if (ControllerButtons[iCurrentButton] == InputState::INPUT_FIRST_RELEASE)
			{
				ControllerButtons[iCurrentButton] = InputState::INPUT_RELEASED;
			}
		}
		iCurrentButton++;
	}

#pragma region LEFT THUMBSTICK
	float LX = _controllerState.Gamepad.sThumbLX;
	float LY = _controllerState.Gamepad.sThumbLY;

	//determine how far the controller is pushed
	float Lmagnitude = sqrt(LX*LX + LY*LY);

	//determine the direction the controller is pushed
	normalizedLX = LX / Lmagnitude;

	float normalizedLMagnitude = 0;

	//check if the controller is outside a circular dead zone
	if (Lmagnitude > 20000)
	{
		//clip the magnitude at its expected maximum value
		if (Lmagnitude > 32767) Lmagnitude = 32767;

		//adjust magnitude relative to the end of the dead zone
		Lmagnitude -= 20000;

		//optionally normalize the magnitude with respect to its expected range
		//giving a magnitude value of 0.0 to 1.0
		normalizedLMagnitude = Lmagnitude / (32767 - 20000);
	}
	else //if the controller is in the deadzone zero out the magnitude
	{
		Lmagnitude = 0.0;
		normalizedLMagnitude = 0.0;
	}



#pragma endregion
}
