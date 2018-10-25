#ifndef __OPTIONS_MENU_H__
#define __OPTIONS_MENU_H__
//	Library includes.


//	Local includes.
#include "Utilities.h"
#include "XboxControllerInput.h"

//	Class prototypes.
class Camera;
class Sprite;
class Input;
class TextLabel;
struct Option;

class OptionsMenu
{
public:
	OptionsMenu();
	~OptionsMenu();

	void Init();
	void Render();
	void ProcessLevel();

private:
	std::shared_ptr<TextLabel> m_pOptionTitle;
	std::shared_ptr<Sprite> m_pControlsTutorial;
	std::shared_ptr<TextLabel> m_pBGMLevel;
	std::shared_ptr<TextLabel> m_pEffectLevel;
	std::shared_ptr<Option> m_pOptionArr[4];
	std::shared_ptr<Sprite> m_pBackground;
	unsigned int m_iCurrentOpt;

	bool m_bControllerMoved = false;
	bool m_bViewingTutorial = false;
	std::shared_ptr<XBOXController> m_pPlayerOneController;
};

#endif