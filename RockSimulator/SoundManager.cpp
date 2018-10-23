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

std::shared_ptr<SoundManager> SoundManager::s_pInstance;

std::shared_ptr<SoundManager> SoundManager::GetInstance()
{
	if (!s_pInstance)
	{
		s_pInstance = std::shared_ptr<SoundManager>(new SoundManager());
	}
	return s_pInstance;
}

void SoundManager::DestroyInstance()
{	
	s_pInstance.reset();	
}

SoundManager::~SoundManager()
{
	m_pBGMenu->release();
	m_pBGGame0->release();
	m_pBGGame1->release();
	m_pBGGame2->release();
	m_pBGGame3->release();
	m_pBGGame4->release();
	m_pEffectPew->release();
	m_pEffectSpawn->release();
	m_pEffectPlayerDeath->release();
	m_pEffectEnemyDeath->release();
	m_pEffectPowerup->release();
	m_audioMgr->release();
	m_pMusicChannel->stop();
	m_pEffectChannel->stop();

}

//Name:			    SoundManagerConstructor
//Parameters:		None
//Return Type:		None
//Description:		Sets member variable defaults
//                  
//                  
SoundManager::SoundManager()
{	
	m_fBGMVolume = 0.16f;
	m_fEffectsVolume = 0.8f;	
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

	LoadAudio("Resources/Sounds/Shoot_1.wav", m_pEffectPew, FMOD_DEFAULT);
	LoadAudio("Resources/Sounds/Rocket_Boost.wav", m_pEffectRocket, FMOD_LOOP_NORMAL);
	LoadAudio("Resources/Sounds/Menu_Move.wav", m_pEffectMenuMove, FMOD_DEFAULT);
	LoadAudio("Resources/Sounds/Menu_Close.wav", m_pEffectMenuClose, FMOD_DEFAULT);
	//LoadAudio("Resources/Sounds/spawning.wav", m_EffectSpawn, FMOD_DEFAULT);
	//LoadAudio("Resources/Sounds/death.wav", m_EffectPlayerDeath, FMOD_DEFAULT);
	//LoadAudio("Resources/Sounds/enemydeath.wav", m_EffectEnemyDeath, FMOD_DEFAULT);	
	//LoadAudio("Resources/Sounds/damage.wav", m_EffectDamage, FMOD_DEFAULT);

	LoadAudio("Resources/Sounds/The Day Time Ran Away.mp3", m_pBGMenu, FMOD_LOOP_NORMAL);

	LoadAudio("Resources/Sounds/Facehammer.mp3", m_pBGGame0, FMOD_LOOP_NORMAL);
	LoadAudio("Resources/Sounds/Here Comes the 8-bit Empire.mp3", m_pBGGame1, FMOD_LOOP_NORMAL);
	LoadAudio("Resources/Sounds/Shell Shock Shake.mp3", m_pBGGame2, FMOD_LOOP_NORMAL);
	LoadAudio("Resources/Sounds/Shingle Tingle.mp3", m_pBGGame3, FMOD_LOOP_NORMAL);
	LoadAudio("Resources/Sounds/The Final End.mp3", m_pBGGame4, FMOD_LOOP_NORMAL);

	LoadAudio("Resources/Sounds/Timer_Count0.wav", m_pEffectTimerTick0, FMOD_DEFAULT);
	LoadAudio("Resources/Sounds/Timer_Count1.wav", m_pEffectTimerTick1, FMOD_DEFAULT);
	LoadAudio("Resources/Sounds/Timer_Count2.wav", m_pEffectTimerTick2, FMOD_DEFAULT);


	m_vBGMPlaylist.push_back(m_pBGGame0);
	m_vBGMPlaylist.push_back(m_pBGGame1);
	m_vBGMPlaylist.push_back(m_pBGGame2);
	m_vBGMPlaylist.push_back(m_pBGGame3);
	m_vBGMPlaylist.push_back(m_pBGGame4);

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

void SoundManager::Update()
{
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
	m_audioMgr->playSound(m_pBGMenu, 0, false, &m_pMusicChannel);	
	m_pMusicChannel->setVolume(m_fBGMVolume);	
}

//Name:			    StartLevelBGM
//Parameters:		None
//Return Type:		None
//Description:		Randoms and plays a song from the level playlist
//                  
//   
void SoundManager::StartLevelBGM()
{
	std::random_shuffle(m_vBGMPlaylist.begin(), m_vBGMPlaylist.end());
	m_audioMgr->playSound(m_vBGMPlaylist.back(), 0, false, &m_pMusicChannel);
	m_pMusicChannel->setVolume(m_fBGMVolume);
}

//Name:			    StopBGM
//Parameters:		None
//Return Type:		None
//Description:		stops the background music
//                  
//                  
void SoundManager::StopBGM()
{
	m_pMusicChannel->stop();
}

//Name:			    SoundPew
//Parameters:		None
//Return Type:		None
//Description:		plays the pew sound
//                  
//                  
void SoundManager::SoundPew()
{	
	m_audioMgr->playSound(m_pEffectPew, 0, false, &m_pEffectChannel);	
	m_pEffectChannel->setVolume(m_fEffectsVolume);
}

void
SoundManager::SoundTakeDamage()
{
		//	Add sound for this.
	m_audioMgr->playSound(m_pEffectDamage, 0, false, &m_pEffectChannel);
	m_pEffectChannel->setVolume(m_fEffectsVolume);
}

void SoundManager::SoundMenuMove()
{
	m_audioMgr->playSound(m_pEffectMenuMove, 0, false, &m_pEffectChannel);
	m_pEffectChannel->setVolume(m_fEffectsVolume);
}

void SoundManager::SoundMenuClose()
{
	m_audioMgr->playSound(m_pEffectMenuClose, 0, false, &m_pEffectChannel);
	m_pEffectChannel->setVolume(m_fEffectsVolume);
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
				m_audioMgr->playSound(m_pEffectRocket, 0, false, &m_pPOneEngineChannel);
				m_pPOneEngineChannel->setVolume(0.0f);
				break;
			}
			m_pPOneEngineChannel->stop();
			break;
		}
		case 1: {
			if (_EnablePlayback) {
				m_audioMgr->playSound(m_pEffectRocket, 0, false, &m_pPTwoEngineChannel);
				m_pPTwoEngineChannel->setVolume(0.0f);
				break;
			}
			m_pPTwoEngineChannel->stop();
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
		m_pPOneEngineChannel->setVolume(_Vol);
		break;
	}
	case 1: {
		m_pPTwoEngineChannel->setVolume(_Vol);
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
	m_audioMgr->playSound(m_pEffectSpawn, 0, false, &m_pEffectChannel);	
	m_pEffectChannel->setVolume(m_fEffectsVolume);
}

void SoundManager::SoundTimerTick(int _TickType){
	FMOD::Sound* sound;
	switch (_TickType){
		case 0: sound = m_pEffectTimerTick0; break;
		case 1: sound = m_pEffectTimerTick1; break;
		case 2: sound = m_pEffectTimerTick2; break;
		default:sound = m_pEffectTimerTick0; break;
	}

	m_audioMgr->playSound(sound, 0, false, &m_pEffectChannel);	
	m_pEffectChannel->setVolume(m_fEffectsVolume);
	sound = nullptr;
}

//Name:			    SoundPlayerDeath
//Parameters:		None
//Return Type:		None
//Description:		plays the player death sound
//                  
//                  
void SoundManager::SoundPlayerDeath()
{	
	m_audioMgr->playSound(m_pEffectPlayerDeath, 0, false, &m_pEffectChannel);	
	m_pEffectChannel->setVolume(m_fEffectsVolume);
}

//Name:			    SoundEnemyDeath
//Parameters:		None
//Return Type:		None
//Description:		plays the enemy death sound
//                  
//                  
void SoundManager::SoundEnemyDeath()
{	
	m_audioMgr->playSound(m_pEffectEnemyDeath, 0, false, &m_pEffectChannel);	
	m_pEffectChannel->setVolume(m_fEffectsVolume);
}

//Name:			    SoundPowerup
//Parameters:		None
//Return Type:		None
//Description:		plays the powerup pickup sound
//                  
//                  
void SoundManager::SoundPowerup()
{	
	m_audioMgr->playSound(m_pEffectPowerup, 0, false, &m_pEffectChannel);	
	m_pEffectChannel->setVolume(m_fEffectsVolume);
}
