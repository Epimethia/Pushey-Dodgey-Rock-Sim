// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2018 Media Design School
//
// Author		:	Jasper Lyons
// Email		:	Jasper.Lyo7552@mediadesign.school.nz
// File Name	:	clock.h
// Description	:	Header file defining the clock class
#ifndef _CLOCK_H_
#define _CLOCK_H_
// Library Includes
#include <chrono>
#include <vector>
#include <memory>

// Local Includes

// Types

// Constants

// Prototypes
class CClock
{
public:
	static std::shared_ptr<CClock> GetInstance();
	static void DestroyInstance();
	CClock();
	~CClock();

	bool Initialise();
	void Process();
	float GetDeltaTick();

protected:
	static std::shared_ptr<CClock> s_pInstance;
	CClock(CClock const&) = delete;
	void operator=(CClock const&) = delete;

	double m_fTimeElapsed;
	double m_fDeltaTime;
	std::chrono::high_resolution_clock::time_point m_fLastTime;
	std::chrono::high_resolution_clock::time_point m_fCurrentTime;

	std::vector<double> m_vecTimeHistory;

	long long m_llNumCounts;

private:

};
#endif // 
