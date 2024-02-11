#include "SoundManager.h"
#include "DxLib.h"

void SoundManager::Init()
{
	// SE/BGM�̃��[�h
	m_soundSelect = LoadSoundMem("data/Sound/SE/button.mp3");	// �Z���N�g�T�E���h
	m_soundButton = LoadSoundMem("data/Sound/SE/select.mp3");	// �{�^���T�E���h
	m_soundJump = LoadSoundMem("data/Sound/SE/jump.mp3");		// �W�����v�T�E���h
	m_soundAttack = LoadSoundMem("data/Sound/SE/fire.mp3");		// �U���T�E���h
	m_soundDamage = LoadSoundMem("data/Sound/SE/damage.mp3");	// ��_���T�E���h
}

void SoundManager::End()
{
	DeleteSoundMem(m_soundSelect);
	DeleteSoundMem(m_soundButton);
	DeleteSoundMem(m_soundAttack);
	DeleteSoundMem(m_soundJump);
	DeleteSoundMem(m_soundDamage);

	DeleteSoundMem(m_bgmDefo);
	DeleteSoundMem(m_bgmButtle);
	DeleteSoundMem(m_bgmGameClear);
	DeleteSoundMem(m_bgmGameOver);
	DeleteSoundMem(m_bgmExplanation);
}

void SoundManager::SoundSelect()
{
	PlaySoundMem(m_soundSelect, DX_PLAYTYPE_BACK, true);
}

void SoundManager::SoundButton()
{
	PlaySoundMem(m_soundButton, DX_PLAYTYPE_BACK, true);
}

void SoundManager::SoundDamage()
{
	PlaySoundMem(m_soundDamage, DX_PLAYTYPE_BACK, true);
}

void SoundManager::SoundJump()
{
	PlaySoundMem(m_soundJump, DX_PLAYTYPE_BACK, true);
}

void SoundManager::SoudndAttack()
{
	PlaySoundMem(m_soundAttack, DX_PLAYTYPE_BACK, true);
}



void SoundManager::BGMDefo()
{
	m_bgmDefo = LoadSoundMem("data/Sound/BGM/BGM_Defo.mp3");		// �f�t�HBGM
	PlaySoundMem(m_bgmDefo, DX_PLAYTYPE_LOOP, true);
}

void SoundManager::BGMButtle()
{
	m_bgmButtle = LoadSoundMem("data/Sound/BGM/BGM-Buttle.mp3");		// �퓬BGM
	PlaySoundMem(m_bgmButtle, DX_PLAYTYPE_LOOP, true);
}

void SoundManager::BGMGameClear()
{
	m_bgmGameClear = LoadSoundMem("data/Sound/BGM/BGM_GameClear.mp3");	// �Q�[���N���ABGM
	PlaySoundMem(m_bgmGameClear, DX_PLAYTYPE_LOOP, true);
}

void SoundManager::BGMGameOver()
{
	m_bgmGameOver = LoadSoundMem("data/Sound/BGM/BGM_GameOver.mp3");	// �Q�[���I�[�o�[BGM
	PlaySoundMem(m_bgmGameOver, DX_PLAYTYPE_LOOP, true);
}

void SoundManager::BGMExplanation()
{
	m_bgmExplanation = LoadSoundMem("data/Sound/BGM/BGM_Explanation.mp3");// ����������BGM
	PlaySoundMem(m_bgmExplanation, DX_PLAYTYPE_LOOP, true);
}
