#ifndef __ENDLEVEL_H__
#define __ENDLEVEL_H__
//	Library includes.


//	Local includes.
#include "Utilities.h"


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
	unsigned int GetWinner();


private:

	std::shared_ptr<TextLabel> m_pEndTitle;
	std::shared_ptr<TextLabel> m_pWinnerTitle;
	std::shared_ptr<Option> m_pOptArr[2];
	std::shared_ptr<Sprite> m_pBackground;
	unsigned int m_iCurrentOpt;
	unsigned int m_iWinner;
};

#endif