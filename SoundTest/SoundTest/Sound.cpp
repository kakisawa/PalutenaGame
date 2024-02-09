#include "Sound.h"
#include "DxLib.h"
#include "Pad.h"

namespace {
	// BGM���̔�
	constexpr int UnderBoxX = 100;
	constexpr int UnderBoxY = 200;
	// BGM���̔��̒���
	constexpr int UnderBoxWidth = 255;
	constexpr int UnderBoxHeight = 20;
	// BGM��̔�
	constexpr int UpBoxX = 100;
	constexpr int UpBoxY = 200;
	// BGM��̔��̒���
	constexpr int UpBoxWidth = 100;
	constexpr int UpBoxHeight = 20;

	// �I�𒆂̔���\�����锠���W
	constexpr int SelectBoxX = UnderBoxX-2;
	constexpr int SelectBoxY = UnderBoxY -2;
	// �I�𒆂̔����͂ޔ��̃T�C�Y
	constexpr int SelectSizeX = UnderBoxWidth+4;
	constexpr int SelectSizeY = UnderBoxHeight+4;

	// ���̏㉺�ړ���
	constexpr int kSelectMoveY = 60;

	// �|�[�Y�����ʒu
	constexpr int PauseBoxX = 70;
	constexpr int PauseBoxY = 50;
	// �|�[�Y�̉���
	constexpr int OriginY = 250;
	// �|�[�Y�̍ő咷��
	constexpr int PauseBoxWight = 500;
	constexpr int PauseBoxHeight = 350;

	// �ő剹��
	constexpr int MaxVolume = 255;
}

Sound::Sound():
	Volume(MaxVolume*0.5f),
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

	Volume = MaxVolume * 0.5f;
	SeVolume = MaxVolume * 0.5f;
	MiniWindowTime = 0;
	PauseCount = 0;
	m_pause = false;
	m_select = kBgmVolume;
}

void Sound::Update()
{
	Pad::Update();

	if(Pad::IsTrigger(PAD_INPUT_10))
	{
		PlaySoundMem(m_seDefo, DX_PLAYTYPE_BACK, true);
	}


	Pause();
	ChangeVolumeSoundMem(Volume, m_bgmDefo);
	ChangeVolumeSoundMem(SeVolume, m_seDefo);
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

			DrawBox(m_selectPos.x, m_selectPos.y, m_selectPos.x+ SelectSizeX, m_selectPos.y+ SelectSizeY, 0xffffff, false);

			DrawFormatString(100, 150, 0xFFFFFF,
				"Volume=%d", Volume);
		}
	}
}

void Sound::BGMDefo()
{
	m_bgmDefo = LoadSoundMem("data/BGM_Defo.mp3");		// �f�t�HBGM
	PlaySoundMem(m_bgmDefo, DX_PLAYTYPE_LOOP, true);

	m_seDefo= LoadSoundMem("data/button.mp3");
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

		if (Pad::IsTrigger(PAD_INPUT_DOWN))
		{
			m_select = (m_select + 1) % kSclectNum;
			m_selectPos.y += kSelectMoveY;

			// �I�𒆂̎l�p����ԉ��ɂ�������l�p����ԏ�ɖ߂�
			if (m_selectPos.y > SelectBoxY + kSelectMoveY * (kSclectNum - 1))
			{
				m_selectPos.y = SelectBoxY;
			}
		}
		// ��L�[����������I����Ԃ���グ��
		else if (Pad::IsTrigger(PAD_INPUT_UP))
		{
			m_select = (m_select - 1) % kSclectNum;
			m_selectPos.y -= kSelectMoveY;

			// �I�𒆂̎l�p����ԉ��ɂ�������l�p����ԏ�ɖ߂�
			if (m_selectPos.y < SelectBoxY)
			{
				m_selectPos.y = SelectBoxY + kSelectMoveY * (kSclectNum - 1);
			}
		}

		if (m_select==kBgmVolume&&Pad::IsTrigger(PAD_INPUT_RIGHT))
		{
			Volume += MaxVolume*0.08f;
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
	}
}
