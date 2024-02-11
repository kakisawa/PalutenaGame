#include "Pause.h"
#include "Game.h"
#include "Pad.h"
#include "DxLib.h"
#include "SoundManager.h"

namespace {
	// �|�[�Y�����ʒu
	constexpr int PauseBoxX = kScreenWidth*0.1f;
	constexpr int PauseBoxY = kScreenHeight*0.5f;
	// �|�[�Y�̍ő咷��
	constexpr int PauseBoxWight = kScreenWidth * 0.8f;
	constexpr int PauseBoxHeight = kScreenHeight * 0.8f;

	// ���̔�
	constexpr int UnderBoxX = PauseBoxX*1.1f;
	constexpr int UnderBoxY = PauseBoxY*0.2f;
	// ���̔��̒���
	constexpr int UnderBoxWidth = PauseBoxWight*0.8f;
	constexpr int UnderBoxHeight = PauseBoxHeight*0.2f;
	// ��̔�
	constexpr int UpBoxX = PauseBoxX * 1.1f;
	constexpr int UpBoxY = PauseBoxY * 0.2f;
	// ��̔��̒���
	constexpr int UpBoxWidth = PauseBoxWight * 0.8f;
	constexpr int UpBoxHeight = PauseBoxHeight * 0.2f;

	// �I�𒆂̔���\�����锠���W
	constexpr int SelectBoxX = UnderBoxX - 2;
	constexpr int SelectBoxY = UnderBoxY - 2;
	// �I�𒆂̔����͂ޔ��̃T�C�Y
	constexpr int SelectSizeX = UnderBoxWidth + 4;
	constexpr int SelectSizeY = UnderBoxHeight + 4;

	// ���̏㉺�ړ���
	constexpr int kSelectMoveY = 60;

	// ���ʂ̍ő�
	constexpr int MaxVolume = 255;
}

Pause::Pause():
	MiniWindowTime(0),
	PauseCount(0),
	m_pause(false),
	m_select(kBgmVolume),
	m_selectPos(SelectBoxX, SelectBoxY)
{
}

Pause::~Pause()
{
}

void Pause::Init()
{
	MiniWindowTime = 0;
	PauseCount = 0;
	m_pause = false;
	m_select = kBgmVolume;

	BgmVolume = MaxVolume * 0.5f;
	SeVolume= MaxVolume * 0.5f;
}

void Pause::Update()
{
	PushPause();
}

void Pause::Draw()
{
	if (m_pause == true)
	{
		DrawBox(PauseBoxX, PauseBoxY - MiniWindowTime,
			PauseBoxX + PauseBoxWight, PauseBoxY + MiniWindowTime,
			0xFFFFFF, false);

		if (MiniWindowTime >= PauseBoxHeight*0.5f) {
			for (int i = 0; i < 2; i++)
			{
				DrawBox(UnderBoxX, UnderBoxY + (kSelectMoveY * i),
					UnderBoxX + UnderBoxWidth, UnderBoxY + UnderBoxHeight + (kSelectMoveY * i),
					0xFFFFFF, false);
			}
			DrawBox(UpBoxX, UpBoxY + (kSelectMoveY * 0),
				UpBoxX + BgmVolume, UpBoxY + UpBoxHeight + (kSelectMoveY * 0),
				0x0095d9, true);
			DrawBox(UpBoxX, UpBoxY + (kSelectMoveY * 1),
				UpBoxX + BgmVolume, UpBoxY + UpBoxHeight + (kSelectMoveY * 1),
				0x0095d9, true);

			DrawBox(m_selectPos.x, m_selectPos.y, m_selectPos.x + SelectSizeX, m_selectPos.y + SelectSizeY, 0xffffff, false);
		}
		DrawFormatString(100, 170, 0xFFFFFF,
			"BgmVolume=%d", BgmVolume);
		DrawFormatString(100, 170 + kSelectMoveY, 0xFFFFFF,
			"SeVolume=%d", BgmVolume);
	}
}

void Pause::PushPause()
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
		MiniWindowTime += 10;

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
			BgmVolume += MaxVolume * 0.08f;
			if (BgmVolume >= MaxVolume)
			{
				BgmVolume = MaxVolume;
			}
		}
		else if (m_select == kBgmVolume && Pad::IsTrigger(PAD_INPUT_LEFT))
		{
			BgmVolume -= MaxVolume * 0.1f;
			if (BgmVolume <= 0)
			{
				BgmVolume = 0;
			}
		}
		if (m_select == kSeVolume && Pad::IsTrigger(PAD_INPUT_RIGHT))
		{
			BgmVolume += MaxVolume * 0.08f;
			// �{��������SE��炵����
			if (BgmVolume >= MaxVolume)
			{
				BgmVolume = MaxVolume;
			}
		}
		else if (m_select == kSeVolume && Pad::IsTrigger(PAD_INPUT_LEFT))
		{
			SeVolume -= MaxVolume * 0.1f;
			// �{��������SE��炵����
			if (SeVolume <= 0)
			{
				SeVolume = 0;
			}
		}
	}
}
