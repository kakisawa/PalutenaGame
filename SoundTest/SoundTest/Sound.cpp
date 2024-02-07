#include "Sound.h"
#include "DxLib.h"
#include "Pad.h"

namespace {
	constexpr int UnderBoxX = 100;
	constexpr int UnderBoxY = 300;

	constexpr int UnderBoxWidth = 200;
	constexpr int UnderBoxHeight = 20;

	constexpr int UpBoxX = 100;
	constexpr int UpBoxY = 300;

	constexpr int UpBoxWidth = 100;
	constexpr int UpBoxHeight = 20;

	constexpr int PauseBoxX = 350;
	constexpr int PauseBoxY = 50;

	constexpr int OriginY = 200;

	constexpr int PauseBoxWight = 200;
	constexpr int PauseBoxHeight = 350;

	// Y...100
	// X...		350__550
	// Y...500
}

Sound::Sound()
{
	Volume = UpBoxWidth;
}

Sound::~Sound()
{
	DeleteSoundMem(m_bgmDefo);
}

void Sound::Init()
{
	BGMDefo();
}

void Sound::Update()
{
	Pad::Update();

	if (Pad::IsTrigger(PAD_INPUT_RIGHT))
	{
		Volume +=10;
		if (Volume >= UnderBoxWidth)
		{
			Volume = UnderBoxWidth;
		}
	}
	else if (Pad::IsTrigger(PAD_INPUT_LEFT))
	{
		Volume -= 10;
		if (Volume <= 0)
		{
			Volume = 0;
		}
	}

	for (int i = 0; i < 200; i++)
	{
		DrawBox(PauseBoxX, OriginY - i,
			PauseBoxX + PauseBoxWight, OriginY + i,
			0xFFFFFF, false);
	}
}

void Sound::Draw()
{
	DrawBox(UnderBoxX, UnderBoxY,
		UnderBoxX+UnderBoxWidth, UnderBoxY+UnderBoxHeight,
		0xFFFFFF, false);
	DrawBox(UpBoxX, UpBoxY,
		UpBoxX + Volume, UpBoxY + UpBoxHeight,
		0x0095d9, true);

	DrawFormatString(100, 100, 0xFFFFFF,
		"Volume=%d", Volume);



	
}

void Sound::BGMDefo()
{
	m_bgmDefo = LoadSoundMem("data/BGM_Defo.mp3");		// ƒfƒtƒHBGM
	PlaySoundMem(m_bgmDefo, DX_PLAYTYPE_LOOP, true);
}
