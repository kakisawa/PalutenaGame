#include "SoundManager.h"
#include "DxLib.h"

void SoundManager::Init()
{
	// SE/BGMのロード
	m_soundSelect= LoadSoundMem("data/Sound/button.mp3");	// セレクトサウンド
	m_soundButton=LoadSoundMem("data/Sound/select.mp3");	// ボタンサウンド
	m_soundJump = LoadSoundMem("data/Sound/jump.mp3");		//ジャンプサウンド
	m_soundAttack = LoadSoundMem("data/Sound/fire.mp3");	// 攻撃サウンド
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