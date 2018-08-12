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

#pragma once
#include <memory>
#include "Dependencies\FMOD\fmod.hpp"

class SoundManager
{
#pragma region Singleton
public:
	static std::shared_ptr<SoundManager> GetInstance();
	static void DestroyInstance();
	~SoundManager();
private:
	static std::shared_ptr<SoundManager> s_pSoundManager;
	SoundManager(SoundManager const&);
	void operator=(SoundManager const&);
	SoundManager();
#pragma endregion
public:
	bool Initialize();
	const bool LoadAudio(const char * _path, FMOD::Sound * &_sound, int _mode);
	void ChangeVolume();
	void StartBGM();
	void StopBGM();
	void SoundPew();
	void SoundSpawn();
	void SoundPlayerDeath();
	void SoundEnemyDeath();
	void SoundPowerup();
	
protected:

private:
	float m_fBGMVolume;
	float m_fEffectsVolume;
	FMOD::System* m_audioMgr;
	FMOD::Channel* m_MusicChannel;		
	FMOD::Channel* m_EffectChannel;
	FMOD::Sound* m_BGMusic;
	FMOD::Sound* m_EffectPew;
	FMOD::Sound* m_EffectSpawn;
	FMOD::Sound* m_EffectPlayerDeath;
	FMOD::Sound* m_EffectEnemyDeath;
	FMOD::Sound* m_EffectPowerup;
};

