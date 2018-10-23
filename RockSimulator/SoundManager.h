// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2018 Media Design School
//
// Author		:	Jasper Lyons
// Email		:	Jasper.Lyo7552@mediadesign.school.nz
// File Name	:	SoundManager.h
// Description	:	Header file defining the SoundManager class
#ifndef __SOUNDMANAGER_H__
#define __SOUNDMANAGER_H__
//	Library includes.
#include <memory>
#include <vector>


//	Local includes.
#include "Dependencies\FMOD\fmod.hpp"


class SoundManager
{
public:
	static std::shared_ptr<SoundManager> GetInstance();
	static void DestroyInstance();
	SoundManager();
	~SoundManager();

	bool Initialize();
	const bool LoadAudio(const char * _path, FMOD::Sound * &_sound, int _mode);
	void Update();
	void ChangeVolume();
	void StartMenuBGM();
	void StartLevelBGM();
	void StopBGM();
	void SoundPew();
	void SoundSpawn();
	void SoundTimerTick(int _TickType);
	void SoundPlayerDeath();
	void SoundEnemyDeath();
	void SoundPowerup();
	void SoundTakeDamage();
	void SoundMenuMove();
	void SoundMenuClose();

	//engine functions
	void ToggleEngineSound(unsigned int _PlayerIndex, bool _EnablePlayback);
	void SetEngineVolume(unsigned int _PlayerIndex, float _Vol);

protected:

private:
	static std::shared_ptr<SoundManager> s_pInstance;
	SoundManager(SoundManager const&) = delete;
	void operator=(SoundManager const&) = delete;

	float m_fBGMVolume;
	float m_fEffectsVolume;
	FMOD::System* m_audioMgr{ nullptr };
	FMOD::Channel* m_pMusicChannel{ nullptr };
	FMOD::Channel* m_pEffectChannel{ nullptr };

	FMOD::Channel* m_pPOneEngineChannel{ nullptr };
	FMOD::Channel* m_pPTwoEngineChannel{ nullptr };

	FMOD::Sound* m_pBGMenu{ nullptr };
	FMOD::Sound* m_pBGGame0{ nullptr };
	FMOD::Sound* m_pBGGame1{ nullptr };
	FMOD::Sound* m_pBGGame2{ nullptr };
	FMOD::Sound* m_pBGGame3{ nullptr };
	FMOD::Sound* m_pBGGame4{ nullptr };

	std::vector<FMOD::Sound*> m_vBGMPlaylist;

	FMOD::Sound* m_pEffectPew{ nullptr };
	FMOD::Sound* m_pEffectRocket{ nullptr };
	FMOD::Sound* m_pEffectSpawn{ nullptr };
	FMOD::Sound* m_pEffectPlayerDeath{ nullptr };
	FMOD::Sound* m_pEffectEnemyDeath{ nullptr };
	FMOD::Sound* m_pEffectPowerup{ nullptr };
	FMOD::Sound* m_pEffectMenuMove{ nullptr };
	FMOD::Sound* m_pEffectDamage{ nullptr };
	FMOD::Sound* m_pEffectMenuClose{ nullptr };
	FMOD::Sound* m_pEffectTimerTick0{ nullptr };
	FMOD::Sound* m_pEffectTimerTick1{ nullptr };
	FMOD::Sound* m_pEffectTimerTick2{ nullptr };
};

#endif