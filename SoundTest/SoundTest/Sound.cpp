#include "Sound.h"
#include "DxLib.h"
#include "Pad.h"

namespace {
	// ���̔�
	constexpr int UnderBoxX = 100;
	constexpr int UnderBoxY = 200;
	// ���̔��̒���
	constexpr int UnderBoxWidth = 255;
	constexpr int UnderBoxHeight = 20;
	// ��̔�
	constexpr int UpBoxX = 100;
	constexpr int UpBoxY = 200;
	// ��̔��̒���
	constexpr int UpBoxWidth = 100;
	constexpr int UpBoxHeight = 20;

	// �I�𒆂̔���\�����锠���W
	constexpr int SelectBoxX = UnderBoxX - 2;
	constexpr int SelectBoxY = UnderBoxY - 2;
	// �I�𒆂̔����͂ޔ��̃T�C�Y
	constexpr int SelectSizeX = UnderBoxWidth + 4;
	constexpr int SelectSizeY = UnderBoxHeight + 4;

	// ���̏㉺�ړ���
	constexpr int kSelectMoveY = 60;

	// �|�[�Y�����ʒu
	constexpr int PauseBoxX = 70;
	constexpr int PauseBoxY = 250;
	// �|�[�Y�̍ő咷��
	constexpr int PauseBoxWight = 500;
	constexpr int PauseBoxHeight = 350;

	// �ő剹��
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
	m_bgmDefo = LoadSoundMem("data/BGM_Defo.mp3");		// �f�t�HBGM
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
