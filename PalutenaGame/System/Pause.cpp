#include "Pause.h"
#include "Game.h"
#include "Pad.h"
#include "DxLib.h"
#include "SoundManager.h"
#include "ColorManager.h"

namespace 
{
	// �|�[�Y�����ʒu
	constexpr int PauseBoxX = kScreenWidth * 0.1f;
	constexpr int PauseBoxY = kScreenHeight * 0.5f;
	// �|�[�Y�̍ő咷��
	constexpr int PauseBoxWight = kScreenWidth * 0.8f;
	constexpr int PauseBoxHeight = kScreenHeight * 0.8f;
}

Pause::Pause(SoundManager* soundManager) :
	m_pSoundManager(soundManager),
	m_miniWindowTime(0),
	m_pauseCount(0),
	m_ispause(false)
{
	// �F�������m��
	m_pColorManager = new ColorManager;
}

Pause::~Pause()
{
	// �F���������
	delete m_pColorManager;
	m_pColorManager = nullptr;
}

void Pause::Init()
{
	m_miniWindowTime = 0;
	m_pauseCount = 0;
	m_ispause = false;
}

void Pause::Update()
{
	if (Pad::IsTrigger(PAD_INPUT_8))
	{
		m_ispause = true;
		m_pauseCount++;
	}
	if (m_pauseCount == 2)
	{
		m_ispause = false;
		m_pauseCount = 0;
		m_miniWindowTime = 0;
	}
	if (m_ispause == true)
	{
		if (m_miniWindowTime >= PauseBoxHeight * 0.5f)
		{
			m_miniWindowTime = PauseBoxHeight * 0.5f;
		}
		m_miniWindowTime += 15;

		m_pSoundManager->ChangeSound();
	}
}

void Pause::Draw()
{
	if (m_ispause == true)
	{
		DrawBox(PauseBoxX-3, PauseBoxY - m_miniWindowTime-3,
			PauseBoxX + PauseBoxWight+3, PauseBoxY + m_miniWindowTime+3,
			m_pColorManager->GetColorWhite(), true);
		DrawBox(PauseBoxX, PauseBoxY - m_miniWindowTime,
			PauseBoxX + PauseBoxWight, PauseBoxY + m_miniWindowTime,
			m_pColorManager->GetColorBlack(), true);

		if (m_miniWindowTime >= PauseBoxHeight * 0.5f)
		{
			m_pSoundManager->Draw();
		}
	}
}