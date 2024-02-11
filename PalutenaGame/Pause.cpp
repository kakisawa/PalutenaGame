#include "Pause.h"
#include "Game.h"
#include "Pad.h"
#include "DxLib.h"
#include "SoundManager.h"

int ChangeBgm= InitBgmVolume;		// �ύX�㉹�ʕۑ�
int ChangeSe=InitSeVolume;

namespace {
	// �|�[�Y�����ʒu
	constexpr int PauseBoxX = kScreenWidth * 0.1f;
	constexpr int PauseBoxY = kScreenHeight * 0.5f;
	// �|�[�Y�̍ő咷��
	constexpr int PauseBoxWight = kScreenWidth * 0.8f;
	constexpr int PauseBoxHeight = kScreenHeight * 0.8f;

	// ���̔�
	constexpr int UnderBoxX = PauseBoxX * 1.4f;
	constexpr int UnderBoxY = PauseBoxY * 0.4f;
	// ���̔��̒���
	constexpr int UnderBoxWidth = PauseBoxWight * 0.897f;
	constexpr int UnderBoxHeight = PauseBoxHeight * 0.1f;
	// ��̔�
	constexpr int UpBoxX = PauseBoxX * 1.4f;
	constexpr int UpBoxY = PauseBoxY * 0.4f;
	// ��̔��̒���
	constexpr int UpBoxWidth = PauseBoxWight * 0.897f;
	constexpr int UpBoxHeight = PauseBoxHeight * 0.1f;

	// �I�𒆂̔���\�����锠���W
	constexpr int SelectBoxX = UnderBoxX - 2;
	constexpr int SelectBoxY = UnderBoxY - 2;
	// �I�𒆂̔����͂ޔ��̃T�C�Y
	constexpr int SelectSizeX = UnderBoxWidth + 4;
	constexpr int SelectSizeY = UnderBoxHeight + 4;

	// ���̏㉺�ړ���
	constexpr int kSelectMoveY = 150;

	// BGM�����ʒu
	constexpr int BgmStringX = UnderBoxX;
	constexpr int BgmStringY = UnderBoxY - 30;
	// SE�����ʒu
	constexpr int SeStringX = UnderBoxX;
	constexpr int SeStringY = UnderBoxY + kSelectMoveY - 30;
}

Pause::Pause(SoundManager* soundManager) :
	m_pSoundManager(soundManager),
	MiniWindowTime(0),
	BgmVolume(InitBgmVolume),
	SeVolume(InitSeVolume),
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

	BgmVolume = ChangeBgm;
	SeVolume = ChangeSe;
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

		if (Pad::IsTrigger(PAD_INPUT_RIGHT))
		{
			if (m_select == kSeVolume)
			{
				SeVolume+=MaxVolume * 0.08f;
				m_pSoundManager->ChangeSEVolume(SeVolume);
				m_pSoundManager->SetSeVolume();
				m_pSoundManager->SoundSelect();
				// �{��������SE��炵����
				if (SeVolume >= MaxVolume)
				{
					SeVolume = MaxVolume;
				}
				ChangeSe = SeVolume;
			}
			else if (m_select == kBgmVolume)
			{
				BgmVolume +=MaxVolume * 0.08f;
				m_pSoundManager->ChangeBGMVolume(BgmVolume);
				m_pSoundManager->SetBgmVolume();
				m_pSoundManager->SoundSelect();
				if (BgmVolume >= MaxVolume)
				{
					BgmVolume = MaxVolume;
				}
				ChangeBgm = BgmVolume;
			}
		}

		else if (Pad::IsTrigger(PAD_INPUT_LEFT))
		{
			if (m_select == kBgmVolume)
			{
				BgmVolume -=MaxVolume * 0.08f;
				m_pSoundManager->ChangeBGMVolume(BgmVolume);
				m_pSoundManager->SetBgmVolume();
				m_pSoundManager->SoundSelect();
				if (BgmVolume <= 0)
				{
					BgmVolume = 0;
				}
				ChangeBgm = BgmVolume;
			}
			else if (m_select == kSeVolume)
			{
				SeVolume-=MaxVolume * 0.08f;
				m_pSoundManager->ChangeSEVolume(SeVolume);
				m_pSoundManager->SetSeVolume();
				m_pSoundManager->SoundSelect();
				// �{��������SE��炵����
				if (SeVolume <= 0)
				{
					SeVolume = 0;
				}
				ChangeSe = SeVolume;
			}
		}
	}
}

void Pause::Draw()
{
	if (m_pause == true)
	{
		DrawBox(PauseBoxX, PauseBoxY - MiniWindowTime,
			PauseBoxX + PauseBoxWight, PauseBoxY + MiniWindowTime,
			0x000000, true);

		if (MiniWindowTime >= PauseBoxHeight * 0.5f) {
			DrawBox(UpBoxX, UpBoxY + (kSelectMoveY * 0),
				UpBoxX + BgmVolume * 3.6, UpBoxY + UpBoxHeight + (kSelectMoveY * 0),
				0x0095d9, true);
			DrawBox(UpBoxX, UpBoxY + (kSelectMoveY * 1),
				UpBoxX + SeVolume * 3.6, UpBoxY + UpBoxHeight + (kSelectMoveY * 1),
				0x0095d9, true);

			for (int i = 0; i < 2; i++)
			{
				DrawBox(UnderBoxX, UnderBoxY + (kSelectMoveY * i),
					UnderBoxX + UnderBoxWidth, UnderBoxY + UnderBoxHeight + (kSelectMoveY * i),
					0xFFFFFF, false);
			}

			DrawBox(m_selectPos.x, m_selectPos.y, m_selectPos.x + SelectSizeX, m_selectPos.y + SelectSizeY, 0xffffff, false);

			DrawFormatString(BgmStringX, BgmStringY, 0xFFFFFF,
				"BgmVolume=%d", BgmVolume);
			DrawFormatString(SeStringX, SeStringY, 0xFFFFFF,
				"SeVolume=%d", SeVolume);
		}


	}
}

int Pause::SetBgmVolume() const
{
	return ChangeBgm;
}

int Pause::SetSeVolume() const
{
	return ChangeSe;
}
