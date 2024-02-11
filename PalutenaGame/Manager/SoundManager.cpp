#include "SoundManager.h"
#include "Pause.h"
#include "DxLib.h"

SoundManager::SoundManager()
{
	m_pPause = new Pause(this);
}

SoundManager::~SoundManager()
{
	delete m_pPause;
	m_pPause = nullptr;
}

void SoundManager::Init()
{
	// SEのロード
	m_soundSelect = LoadSoundMem("data/Sound/SE/button.mp3");	// セレクトサウンド
	m_soundButton = LoadSoundMem("data/Sound/SE/select.mp3");	// ボタンサウンド
	m_soundJump = LoadSoundMem("data/Sound/SE/jump.mp3");		// ジャンプサウンド
	m_soundAttack = LoadSoundMem("data/Sound/SE/fire.mp3");		// 攻撃サウンド
	m_soundDamage = LoadSoundMem("data/Sound/SE/damage.mp3");	// 被ダメサウンド

	SeVolume = m_pPause->SetSeVolume();	
	BgmVolume = m_pPause->SetBgmVolume();
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
	m_bgmDefo = LoadSoundMem("data/Sound/BGM/BGM_Defo.mp3");		// デフォBGM
	PlaySoundMem(m_bgmDefo, DX_PLAYTYPE_LOOP, true);
}

void SoundManager::BGMButtle()
{
	m_bgmButtle = LoadSoundMem("data/Sound/BGM/BGM-Buttle.mp3");		// 戦闘BGM
	PlaySoundMem(m_bgmButtle, DX_PLAYTYPE_LOOP, true);
}

void SoundManager::BGMGameClear()
{
	m_bgmGameClear = LoadSoundMem("data/Sound/BGM/BGM_GameClear.mp3");	// ゲームクリアBGM
	PlaySoundMem(m_bgmGameClear, DX_PLAYTYPE_LOOP, true);
}

void SoundManager::BGMGameOver()
{
	m_bgmGameOver = LoadSoundMem("data/Sound/BGM/BGM_GameOver.mp3");	// ゲームオーバーBGM
	PlaySoundMem(m_bgmGameOver, DX_PLAYTYPE_LOOP, true);
}

void SoundManager::BGMExplanation()
{
	m_bgmExplanation = LoadSoundMem("data/Sound/BGM/BGM_Explanation.mp3");// 操作説明画面BGM
	PlaySoundMem(m_bgmExplanation, DX_PLAYTYPE_LOOP, true);
}

void SoundManager::ChangeBGMVolume(int volume)
{
	BgmVolume = volume;
}

void SoundManager::ChangeSEVolume(int volume)
{
	SeVolume = volume;
}

void SoundManager::SetBgmVolume()
{
	ChangeVolumeSoundMem(BgmVolume, m_bgmDefo);
	ChangeVolumeSoundMem(BgmVolume, m_bgmButtle);
	ChangeVolumeSoundMem(BgmVolume, m_bgmGameClear);
	ChangeVolumeSoundMem(BgmVolume, m_bgmGameOver);
	ChangeVolumeSoundMem(BgmVolume, m_bgmExplanation);
}

void SoundManager::SetSeVolume()
{
	ChangeVolumeSoundMem(SeVolume, m_soundSelect);
	ChangeVolumeSoundMem(SeVolume, m_soundButton);
	ChangeVolumeSoundMem(SeVolume, m_soundJump);
	ChangeVolumeSoundMem(SeVolume, m_soundAttack);
	ChangeVolumeSoundMem(SeVolume, m_soundDamage);
}
