// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2018 Media Design School
//
// Author		:	Jasper Lyons
// Email		:	Jasper.Lyo7552@mediadesign.school.nz
// File Name	:	SoundManager.cpp
// Description	:	Implimentation for the SoundManager class

#include "SoundManager.h"
#include <algorithm>

std::shared_ptr<SoundManager> SoundManager::s_pSoundManager;

std::shared_ptr<SoundManager> SoundManager::GetInstance()
{
	if (!s_pSoundManager)
	{
		s_pSoundManager = std::shared_ptr<SoundManager>(new SoundManager());
	}
	return s_pSoundManager;
}

void SoundManager::DestroyInstance()
{	
	s_pSoundManager.reset();	
}

SoundManager::~SoundManager()
{
	m_BGMenu->release();
	m_BGGame0->release();
	m_BGGame1->release();
	m_BGGame2->release();
	m_BGGame3->release();
	m_BGGame4->release();
	m_EffectPew->release();
	m_EffectSpawn->release();
	m_EffectPlayerDeath->release();
	m_EffectEnemyDeath->release();
	m_EffectPowerup->release();
	m_audioMgr->release();
	m_MusicChannel->stop();
	m_EffectChannel->stop();

}

//Name:			    SoundManagerConstructor
//Parameters:		None
//Return Type:		None
//Description:		Sets member variable defaults
//                  
//                  
SoundManager::SoundManager()
{	
	m_fBGMVolume = 0.08f;
	m_fEffectsVolume = 1.0f;	
}

//Name:			    Initialize
//Parameters:		None
//Return Type:		bool
//Description:		Initializes and loads audio 
//                  
//                  
bool SoundManager::Initialize()
{
	FMOD_RESULT result;
	result = FMOD::System_Create(&m_audioMgr);
	if (result != FMOD_OK)
	{
		return false;
	}

	result = m_audioMgr->init(50, FMOD_INIT_NORMAL, 0);
	if (result != FMOD_OK)
	{
		return false;
	}

	//LoadAudio("Resources/Sounds/powerup.wav", m_EffectPowerup, FMOD_DEFAULT);
	LoadAudio("Resources/Sounds/Shoot_1.wav", m_EffectPew, FMOD_DEFAULT);
	LoadAudio("Resources/Sounds/Rocket_Boost.wav", m_EffectRocket, FMOD_LOOP_NORMAL);
	//LoadAudio("Resources/Sounds/spawning.wav", m_EffectSpawn, FMOD_DEFAULT);
	//LoadAudio("Resources/Sounds/death.wav", m_EffectPlayerDeath, FMOD_DEFAULT);
	//LoadAudio("Resources/Sounds/enemydeath.wav", m_EffectEnemyDeath, FMOD_DEFAULT);	
	//LoadAudio("Resources/Sounds/damage.wav", m_EffectDamage, FMOD_DEFAULT);

	LoadAudio("Resources/Sounds/The Day Time Ran Away.mp3", m_BGMenu, FMOD_LOOP_NORMAL);

	LoadAudio("Resources/Sounds/Facehammer.mp3", m_BGGame0, FMOD_LOOP_NORMAL);
	LoadAudio("Resources/Sounds/Here Comes the 8-bit Empire.mp3", m_BGGame1, FMOD_LOOP_NORMAL);
	LoadAudio("Resources/Sounds/Shell Shock Shake.mp3", m_BGGame2, FMOD_LOOP_NORMAL);
	LoadAudio("Resources/Sounds/Shingle Tingle.mp3", m_BGGame3, FMOD_LOOP_NORMAL);
	LoadAudio("Resources/Sounds/The Final End.mp3", m_BGGame4, FMOD_LOOP_NORMAL);

	BGMPlaylist.push_back(m_BGGame0);
	BGMPlaylist.push_back(m_BGGame1);
	BGMPlaylist.push_back(m_BGGame2);
	BGMPlaylist.push_back(m_BGGame3);
	BGMPlaylist.push_back(m_BGGame4);

	return true;
}

//Name:			    LoadAudio
//Parameters:		char* path, sound, int mode
//Return Type:		const bool
//Description:		Loads specified sound
//                  
//                  
const bool SoundManager::LoadAudio(const char * _path, FMOD::Sound * &_sound, int _mode)
{
	FMOD_RESULT result;

	result = m_audioMgr->createSound(_path,
		FMOD_DEFAULT, 0, &_sound);
	if (result != FMOD_OK) {
		return false;
	}
	_sound->setMode(_mode);

	return true;
}

void SoundManager::Update() {
	m_audioMgr->update();
}

//Name:			    ChangeVolume
//Parameters:		None
//Return Type:		None
//Description:		Toggles volume
//                  
//                  
void SoundManager::ChangeVolume()
{
	if (m_fBGMVolume != 0.0f)
	{
		m_fBGMVolume = 0.0f;
		m_fEffectsVolume = 0.0f;
	}
	else
	{
		m_fBGMVolume = 0.04f;
		m_fEffectsVolume = 0.5f;
	}		
}

//Name:			    StartBGM
//Parameters:		None
//Return Type:		None
//Description:		Starts the background music playing
//                  
//                  
void SoundManager::StartMenuBGM()
{			
	m_audioMgr->playSound(m_BGMenu, 0, false, &m_MusicChannel);	
	m_MusicChannel->setVolume(m_fBGMVolume);	
}

//Name:			    StartLevelBGM
//Parameters:		None
//Return Type:		None
//Description:		Randoms and plays a song from the level playlist
//                  
//   
void SoundManager::StartLevelBGM()
{
	std::random_shuffle(BGMPlaylist.begin(), BGMPlaylist.end());
	m_audioMgr->playSound(BGMPlaylist.back(), 0, false, &m_MusicChannel);
	m_MusicChannel->setVolume(m_fBGMVolume);
}

//Name:			    StopBGM
//Parameters:		None
//Return Type:		None
//Description:		stops the background music
//                  
//                  
void SoundManager::StopBGM()
{
	m_MusicChannel->stop();
}

//Name:			    SoundPew
//Parameters:		None
//Return Type:		None
//Description:		plays the pew sound
//                  
//                  
void SoundManager::SoundPew()
{	
	m_audioMgr->playSound(m_EffectPew, 0, false, &m_EffectChannel);	
	m_EffectChannel->setVolume(m_fEffectsVolume);
}

void
SoundManager::SoundTakeDamage()
{
		//	Add sound for this.
	m_audioMgr->playSound(m_EffectDamage, 0, false, &m_EffectChannel);
	m_EffectChannel->setVolume(m_fEffectsVolume);
}

//Name:			    ToggleEngineSound
//Parameters:		unsigned int, bool
//Return Type:		None
//Description:		Toggles the engine sound loop for the specified player index
//                  
//      
void SoundManager::ToggleEngineSound(unsigned int _PlayerIndex, bool _EnablePlayback) {
	switch (_PlayerIndex)
	{
		case 0: {
			if (_EnablePlayback) {
				m_audioMgr->playSound(m_EffectRocket, 0, false, &m_POneEngineChannel);
				m_POneEngineChannel->setVolume(0.0f);
				break;
			}
			m_POneEngineChannel->stop();
			break;
		}
		case 1: {
			if (_EnablePlayback) {
				m_audioMgr->playSound(m_EffectRocket, 0, false, &m_PTwoEngineChannel);
				m_PTwoEngineChannel->setVolume(0.0f);
				break;
			}
			m_PTwoEngineChannel->stop();
			break;
		}
	default:break;
	}

}

//Name:			    SetEngineVolume
//Parameters:		unsinged int, float
//Return Type:		None
//Description:		Sets the volume for the specified channel
//                  
//      
void SoundManager::SetEngineVolume(unsigned int _PlayerIndex, float _Vol)
{
	switch (_PlayerIndex)
	{
	case 0: {
		m_POneEngineChannel->setVolume(_Vol);
		break;
	}
	case 1: {
		m_PTwoEngineChannel->setVolume(_Vol);
		break;
	}
	default:
		break;
	}
}

//Name:			    SoundSpawn
//Parameters:		None
//Return Type:		None
//Description:		plays the spawner sound
//                  
//                  
void SoundManager::SoundSpawn()
{	
	m_audioMgr->playSound(m_EffectSpawn, 0, false, &m_EffectChannel);	
	m_EffectChannel->setVolume(m_fEffectsVolume);
}

//Name:			    SoundPlayerDeath
//Parameters:		None
//Return Type:		None
//Description:		plays the player death sound
//                  
//                  
void SoundManager::SoundPlayerDeath()
{	
	m_audioMgr->playSound(m_EffectPlayerDeath, 0, false, &m_EffectChannel);	
	m_EffectChannel->setVolume(m_fEffectsVolume);
}

//Name:			    SoundEnemyDeath
//Parameters:		None
//Return Type:		None
//Description:		plays the enemy death sound
//                  
//                  
void SoundManager::SoundEnemyDeath()
{	
	m_audioMgr->playSound(m_EffectEnemyDeath, 0, false, &m_EffectChannel);	
	m_EffectChannel->setVolume(m_fEffectsVolume);
}

//Name:			    SoundPowerup
//Parameters:		None
//Return Type:		None
//Description:		plays the powerup pickup sound
//                  
//                  
void SoundManager::SoundPowerup()
{	
	m_audioMgr->playSound(m_EffectPowerup, 0, false, &m_EffectChannel);	
	m_EffectChannel->setVolume(m_fEffectsVolume);
}
