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
	std::vector<std::shared_ptr<TextLabel>> MenuOptions;
	void ProcessPlayerInput();
};

