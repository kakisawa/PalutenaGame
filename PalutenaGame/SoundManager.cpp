#include "SoundManager.h"
#include "DxLib.h"

void SoundManager::Init()
{
	// SE/BGM�̃��[�h
	m_soundSelect= LoadSoundMem("data/Sound/button.mp3");	// �Z���N�g�T�E���h
	m_soundButton=LoadSoundMem("data/Sound/select.mp3");	// �{�^���T�E���h
	m_soundJump = LoadSoundMem("data/Sound/jump.mp3");		//�W�����v�T�E���h
	m_soundAttack = LoadSoundMem("data/Sound/fire.mp3");	// �U���T�E���h
}

void SoundManager::End()
{
	DeleteSoundMem(m_soundSelect);
	DeleteSoundMem(m_soundButton);
	DeleteSoundMem(m_soundAttack);
	DeleteSoundMem(m_soundJump);
}

void SoundManager::SoundSelect()
{
	PlaySoundMem(m_soundSelect, DX_PLAYTYPE_BACK, true);
}

void SoundManager::SoundButton()
{
	PlaySoundMem(m_soundButton, DX_PLAYTYPE_BACK, true);
}

void SoundManager::SoundJump()
{
	PlaySoundMem(m_soundJump, DX_PLAYTYPE_BACK, true);
}

void SoundManager::SoudndAttack()
{
	PlaySoundMem(m_soundAttack, DX_PLAYTYPE_BACK, true);

}