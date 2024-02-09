#include "Sound.h"
#include "DxLib.h"
#include "Pad.h"

namespace {
	constexpr int UnderBoxX = 100;
	constexpr int UnderBoxY = 300;

	constexpr int UnderBoxWidth = 255;
	constexpr int UnderBoxHeight = 20;

	constexpr int UpBoxX = 100;
	constexpr int UpBoxY = 300;

	constexpr int UpBoxWidth = 100;
	constexpr int UpBoxHeight = 20;

	constexpr int PauseBoxX = 70;
	constexpr int PauseBoxY = 50;

	constexpr int OriginY = 250;

	constexpr int PauseBoxWight = 500;
	constexpr int PauseBoxHeight = 350;

	constexpr int MaxVolume = 255;
}

Sound::Sound():
	Volume(MaxVolume*0.5f),
	MiniWindowTime(0),
	PauseCount(0),
	m_pause(false)
{
}

Sound::~Sound()
{
	DeleteSoundMem(m_bgmDefo);
}

void Sound::Init()
{
	BGMDefo();

	Volume = MaxVolume * 0.5f;
	MiniWindowTime = 0;
	PauseCount = 0;
	m_pause = false;
}

void Sound::Update()
{
	Pad::Update();

	Pause();
	ChangePanSoundMem(Volume, m_bgmDefo);

	//ChangeVolumeSoundMem(Volume, m_bgmDefo) ;
}

void Sound::Draw()
{
	if (m_pause == true)
	{
		DrawBox(PauseBoxX, OriginY - MiniWindowTime,
			PauseBoxX + PauseBoxWight, OriginY + MiniWindowTime,
			0xFFFFFF, false);

		if (MiniWindowTime >= 150) {
			DrawBox(UnderBoxX, UnderBoxY,
				UnderBoxX + UnderBoxWidth, UnderBoxY + UnderBoxHeight,
				0xFFFFFF, false);
			DrawBox(UpBoxX, UpBoxY,
				UpBoxX + Volume, UpBoxY + UpBoxHeight,
				0x0095d9, true);

			DrawFormatString(100, 150, 0xFFFFFF,
				"Volume=%d", Volume);
		}
	}
}

void Sound::BGMDefo()
{
	m_bgmDefo = LoadSoundMem("data/BGM_Defo.mp3");		// ƒfƒtƒHBGM
	PlaySoundMem(m_bgmDefo, DX_PLAYTYPE_LOOP, true);
}

void Sound::Pause()
{
	if (Pad::IsTrigger(PAD_INPUT_1))
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
		if (MiniWindowTime >= 150)
		{
			MiniWindowTime = 150;
		}
		MiniWindowTime += 5;

		if (Pad::IsTrigger(PAD_INPUT_RIGHT))
		{
			Volume += MaxVolume*0.1f;
			if (Volume >= MaxVolume)
			{
				Volume = MaxVolume;
			}
		}
		else if (Pad::IsTrigger(PAD_INPUT_LEFT))
		{
			Volume -= MaxVolume * 0.1f;
			if (Volume <= 0)
			{
				Volume = 0;
			}
		}
	}


}
