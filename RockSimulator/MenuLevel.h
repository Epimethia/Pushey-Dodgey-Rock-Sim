#pragma once
#pragma once
//	Library includes.
#include "Utilities.h"
#include "XboxControllerInput.h"


//	Local includes.


//	Class prototypes.
class Camera;
class Sprite;
class Input;
class TextLabel;
struct Option;

class MainMenu
{
public:
	MainMenu();
	~MainMenu();

	void Init();
	void Render();
	void Process();

	void AddOption();

private:

	std::shared_ptr<TextLabel> MenuTitle;

	std::shared_ptr<Option> OptArr[3];
	void ProcessPlayerInput();
	std::shared_ptr<Sprite> m_pBackground;
	unsigned int CurrentOpt;
};
