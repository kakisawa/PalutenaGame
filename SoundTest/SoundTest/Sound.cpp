#include "Sound.h"
#include "DxLib.h"
#include "Pad.h"

namespace {
	// 下の箱
	constexpr int UnderBoxX = 100;
	constexpr int UnderBoxY = 200;
	// 下の箱の長さ
	constexpr int UnderBoxWidth = 255;
	constexpr int UnderBoxHeight = 20;
	// 上の箱
	constexpr int UpBoxX = 100;
	constexpr int UpBoxY = 200;
	// 上の箱の長さ
	constexpr int UpBoxWidth = 100;
	constexpr int UpBoxHeight = 20;

	// 選択中の箱を表示する箱座標
	constexpr int SelectBoxX = UnderBoxX - 2;
	constexpr int SelectBoxY = UnderBoxY - 2;
	// 選択中の箱を囲む箱のサイズ
	constexpr int SelectSizeX = UnderBoxWidth + 4;
	constexpr int SelectSizeY = UnderBoxHeight + 4;

	// 箱の上下移動量
	constexpr int kSelectMoveY = 60;

	// ポーズ初期位置
	constexpr int PauseBoxX = 70;
	constexpr int PauseBoxY = 250;
	// ポーズの最大長さ
	constexpr int PauseBoxWight = 500;
	constexpr int PauseBoxHeight = 350;

	// 最大音量
	constexpr int MaxVolume = 255;
}

Sound::Sound() :
	Volume(MaxVolume * 0.5f),
	SeVolume(MaxVolume * 0.5f),
	MiniWindowTime(0),
	PauseCount(0),
	m_pause(false),
	m_select(kBgmVolume),
	m_selectPos(SelectBoxX, SelectBoxY)
{
}

Sound::~Sound()
{
	DeleteSoundMem(m_bgmDefo);
}

void Sound::Init()
{
	BGMDefo();

	Volume = MaxVolume * 0.8f;
	SeVolume = MaxVolume * 0.8f;
	MiniWindowTime = 0;
	PauseCount = 0;
	m_pause = false;
	m_select = kBgmVolume;
}

void Sound::Update()
{
	Pad::Update();

	Pause();
	ChangeVolumeSoundMem(Volume, m_bgmDefo);
	ChangeVolumeSoundMem(SeVolume, m_seDefo);
}

void Sound::Draw()
{
	if (m_pause == true)
	{
		DrawBox(PauseBoxX, PauseBoxY - MiniWindowTime,
			PauseBoxX + PauseBoxWight, PauseBoxY + MiniWindowTime,
			0xFFFFFF, false);

		if (MiniWindowTime >= 150) {
			DrawBox(UpBoxX, UpBoxY + (kSelectMoveY * 0),
				UpBoxX + Volume, UpBoxY + UpBoxHeight + (kSelectMoveY * 0),
				0x0095d9, true);
			DrawBox(UpBoxX, UpBoxY + (kSelectMoveY * 1),
				UpBoxX + SeVolume, UpBoxY + UpBoxHeight + (kSelectMoveY * 1),
				0x0095d9, true);
			for (int i = 0; i < 2; i++)
			{
				DrawBox(UnderBoxX, UnderBoxY + (kSelectMoveY * i),
					UnderBoxX + UnderBoxWidth, UnderBoxY + UnderBoxHeight + (kSelectMoveY * i),
					0xFFFFFF, false);
			}

			DrawBox(m_selectPos.x, m_selectPos.y, m_selectPos.x + SelectSizeX, m_selectPos.y + SelectSizeY, 0xffffff, false);

			DrawFormatString(100, 170, 0xFFFFFF,
				"Volume=%d", Volume);
			DrawFormatString(100, 170+ kSelectMoveY, 0xFFFFFF,
				"SeVolume=%d", SeVolume);
		}
	}
}

void Sound::BGMDefo()
{
	m_bgmDefo = LoadSoundMem("data/BGM_Defo.mp3");		// デフォBGM
	PlaySoundMem(m_bgmDefo, DX_PLAYTYPE_LOOP, true);

	m_seDefo = LoadSoundMem("data/button.mp3");
}

void Sound::Pause()
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
		if (MiniWindowTime >= 150)
		{
			MiniWindowTime = 150;
		}
		MiniWindowTime += 5;

		if (Pad::IsTrigger(PAD_INPUT_DOWN))
		{
			m_select = (m_select + 1) % kSclectNum;
			m_selectPos.y += kSelectMoveY;

			// 選択中の四角が一番下にだったら四角を一番上に戻す
			if (m_selectPos.y > SelectBoxY + kSelectMoveY * (kSclectNum - 1))
			{
				m_selectPos.y = SelectBoxY;
			}
		}
		// 上キーを押したら選択状態を一つ上げる
		else if (Pad::IsTrigger(PAD_INPUT_UP))
		{
			m_select = (m_select - 1) % kSclectNum;
			m_selectPos.y -= kSelectMoveY;

			// 選択中の四角が一番下にだったら四角を一番上に戻す
			if (m_selectPos.y < SelectBoxY)
			{
				m_selectPos.y = SelectBoxY + kSelectMoveY * (kSclectNum - 1);
			}
		}

		if (m_select == kBgmVolume && Pad::IsTrigger(PAD_INPUT_RIGHT))
		{
			Volume += MaxVolume * 0.08f;
			if (Volume >= MaxVolume)
			{
				Volume = MaxVolume;
			}
		}
		else if (m_select == kBgmVolume && Pad::IsTrigger(PAD_INPUT_LEFT))
		{
			Volume -= MaxVolume * 0.1f;
			if (Volume <= 0)
			{
				Volume = 0;
			}
		}
		if (m_select == kSeVolume && Pad::IsTrigger(PAD_INPUT_RIGHT))
		{
			SeVolume += MaxVolume * 0.08f;
			PlaySoundMem(m_seDefo, DX_PLAYTYPE_BACK, true);
			if (SeVolume >= MaxVolume)
			{
				SeVolume = MaxVolume;
			}
		}
		else if (m_select == kSeVolume && Pad::IsTrigger(PAD_INPUT_LEFT))
		{
			SeVolume -= MaxVolume * 0.1f;
			PlaySoundMem(m_seDefo, DX_PLAYTYPE_BACK, true);
			if (SeVolume <= 0)
			{
				SeVolume = 0;
			}
		}
	}
}
