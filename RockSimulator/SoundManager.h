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
	FMOD::System* m_audioMgr;
	FMOD::Channel* m_pMusicChannel;		
	FMOD::Channel* m_pEffectChannel;

	FMOD::Channel* m_pPOneEngineChannel;
	FMOD::Channel* m_pPTwoEngineChannel;

	FMOD::Sound* m_pBGMenu;
	FMOD::Sound* m_pBGGame0;
	FMOD::Sound* m_pBGGame1;
	FMOD::Sound* m_pBGGame2;
	FMOD::Sound* m_pBGGame3;
	FMOD::Sound* m_pBGGame4;

	std::vector<FMOD::Sound*> m_vBGMPlaylist;

	FMOD::Sound* m_pEffectPew;
	FMOD::Sound* m_pEffectRocket;
	FMOD::Sound* m_pEffectSpawn;
	FMOD::Sound* m_pEffectPlayerDeath;
	FMOD::Sound* m_pEffectEnemyDeath;
	FMOD::Sound* m_pEffectPowerup;
	FMOD::Sound* m_pEffectMenuMove;
	FMOD::Sound* m_pEffectDamage;
	FMOD::Sound* m_pEffectMenuClose;
};

#endif