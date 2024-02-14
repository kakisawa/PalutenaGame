#include "Pause.h"
#include "Game.h"
#include "Pad.h"
#include "DxLib.h"
#include "SoundManager.h"
#include "ColorManager.h"

namespace 
{
	// ポーズ初期位置
	constexpr int PauseBoxX = kScreenWidth * 0.1f;
	constexpr int PauseBoxY = kScreenHeight * 0.5f;
	// ポーズの最大長さ
	constexpr int PauseBoxWight = kScreenWidth * 0.8f;
	constexpr int PauseBoxHeight = kScreenHeight * 0.8f;
}

Pause::Pause(SoundManager* soundManager) :
	m_pSoundManager(soundManager),
	MiniWindowTime(0),
	PauseCount(0),
	m_pause(false)
{
	// 色メモリ確保
	m_pColorManager = new ColorManager;
}

Pause::~Pause()
{
	// 色メモリ解放
	delete m_pColorManager;
	m_pColorManager = nullptr;
}

void Pause::Init()
{
	MiniWindowTime = 0;
	PauseCount = 0;
	m_pause = false;
}

void Pause::Update()
{
	if (Pad::IsTrigger(PAD_INPUT_8))
	{
		m_pause = true;
		PauseCount++;
	}
	if (PauseCount == 2)
	{
		m_pause = false;
		PauseCount = 0;
		MiniWindowTime = 0;
	}
	if (m_pause == true)
	{
		if (MiniWindowTime >= PauseBoxHeight * 0.5f)
		{
			MiniWindowTime = PauseBoxHeight * 0.5f;
		}
		MiniWindowTime += 15;

		m_pSoundManager->ChangeSound();
	}
}

void Pause::Draw()
{
	if (m_pause == true)
	{
		DrawBox(PauseBoxX-3, PauseBoxY - MiniWindowTime-3,
			PauseBoxX + PauseBoxWight+3, PauseBoxY + MiniWindowTime+3,
			m_pColorManager->GetColorWhite(), true);
		DrawBox(PauseBoxX, PauseBoxY - MiniWindowTime,
			PauseBoxX + PauseBoxWight, PauseBoxY + MiniWindowTime,
			m_pColorManager->GetColorBlack(), true);

		if (MiniWindowTime >= PauseBoxHeight * 0.5f)
		{
			m_pSoundManager->Draw();
		}
	}
}