#ifndef __MENULEVEL_H__
#define __MENULEVEL_H__
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


class MainMenu
{
public:
	MainMenu();
	~MainMenu();

	void Init();
	void Render();
	void ProcessLevel();

private:
	std::shared_ptr<TextLabel> m_pMenuTitle;
	std::shared_ptr<Option> m_pOptionArr[3];
	std::shared_ptr<Sprite> m_pBackground;
	unsigned int m_iCurrentOpt;
	bool m_bControllerMoved = false;
	std::shared_ptr<XBOXController> m_pPlayerOneController;
};

#endif