#pragma once
#pragma once
#pragma once
//	Library includes.
#include "Utilities.h"


//	Local includes.


//	Class prototypes.
class Camera;
class Sprite;
class Input;
class TextLabel;
struct Option;

class EndLevel
{
public:
	EndLevel();
	~EndLevel();

	void Init();
	void Render();
	void ProcessLevel();
	void SetWinner(unsigned int _WinningPlayer);
private:

	std::shared_ptr<TextLabel> EndTitle;
	std::shared_ptr<TextLabel> WinnerTitle;
	std::shared_ptr<Option> OptArr[2];
	std::shared_ptr<Sprite> m_pBackground;
	unsigned int CurrentOpt;
};
