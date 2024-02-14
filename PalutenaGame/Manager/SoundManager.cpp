#include "SoundManager.h"
#include "FontManager.h"
#include "ColorManager.h"
#include "Pause.h"
#include"Game.h"
#include "Pad.h"
#include "DxLib.h"
#include <cassert>

int ChangeBgm = InitBgmVolume;		// �ύX�㉹�ʕۑ�
int ChangeSe = InitSeVolume;

namespace
{
	// ���̏㉺�ړ���
	constexpr int kSelectMoveY = 230;

	// ���̔�
	constexpr int UnderBoxX = (kScreenWidth * 0.1f) * 1.4f;
	constexpr int UnderBoxY = (kScreenHeight * 0.5f) * 0.5f;
	// ���̔��̒���
	constexpr int UnderBoxWidth = (kScreenWidth * 0.8f) * 0.897f;
	constexpr int UnderBoxHeight = (kScreenHeight * 0.8f) * 0.1f;
	// ��̔�
	constexpr int UpBoxX = UnderBoxX;
	constexpr int UpBoxY = UnderBoxY;
	// ��̔��̒���
	constexpr int UpBoxWidth = UnderBoxWidth;
	constexpr int UpBoxHeight = UnderBoxHeight;
	
	// �^�C�g���ɖ߂�Box�ʒu
	constexpr int BackBoxX = UnderBoxX * 2.3f;
	constexpr int BackBoxY = UnderBoxY +(kSelectMoveY * 2);

	// �I�𒆂̔���\�����锠���W
	constexpr int SelectBoxX = UnderBoxX - 2;
	constexpr int SelectBoxY = UnderBoxY - 2;
	// �I�𒆂̔����͂ޔ��̃T�C�Y
	constexpr int SelectSizeX = UnderBoxWidth + 4;
	constexpr int SelectSizeY = UnderBoxHeight + 4;

	// BGM�����ʒu
	constexpr int BgmStringX = UnderBoxX;
	constexpr int BgmStringY = UnderBoxY - 80;
	// SE�����ʒu
	constexpr int SeStringX = UnderBoxX;
	constexpr int SeStringY = BgmStringY + kSelectMoveY;
	// �^�C�g���ɖ߂镶���ʒu
	constexpr int BackStringX = BackBoxX+140;
	constexpr int BackStringY= BackBoxY+10;
}

SoundManager::SoundManager() :
	m_select(kBgmVolume),
	m_selectPos(SelectBoxX, SelectBoxY)
{
	m_pPause = new Pause(this);
	// �t�H���g�̃������m��
	m_pFontManager = new FontManager;
	// �F�������m��
	m_pColorManager = new ColorManager;
}

SoundManager::~SoundManager()
{
	delete m_pPause;
	m_pPause = nullptr;
	// �t�H���g�������̉��
	delete m_pFontManager;
	m_pFontManager = nullptr;
	// �F���������
	delete m_pColorManager;
	m_pColorManager = nullptr;

	DeleteGraph(Graph);
}

void SoundManager::Init()
{
	// SE�̃��[�h
	m_soundSelect = LoadSoundMem("data/Sound/SE/button.mp3");	// �Z���N�g�T�E���h
	m_soundButton = LoadSoundMem("data/Sound/SE/select.mp3");	// �{�^���T�E���h
	m_soundJump = LoadSoundMem("data/Sound/SE/jump.mp3");		// �W�����v�T�E���h
	m_soundAttack = LoadSoundMem("data/Sound/SE/fire.mp3");		// �U���T�E���h
	m_soundDamage = LoadSoundMem("data/Sound/SE/damage.mp3");	// ��_���T�E���h

	Graph = LoadGraph("data/SelectUI2.png");
	assert(Graph != -1);

	IsSceneEnd = false;

	m_select = kBgmVolume;
	m_selectPos.x = SelectBoxX;
	m_selectPos.y = SelectBoxY;

	BgmVolume = ChangeBgm;
	SeVolume = ChangeSe;
}

void SoundManager::Draw()
{
	DrawBoxAA(UpBoxX, UpBoxY + (kSelectMoveY * 0),
		UpBoxX + BgmVolume * 5.4, UpBoxY + UpBoxHeight + (kSelectMoveY * 0),
		0x0095d9, true, 2.0f);
	DrawBoxAA(UpBoxX, UpBoxY + (kSelectMoveY * 1),
		UpBoxX + SeVolume * 5.4, UpBoxY + UpBoxHeight + (kSelectMoveY * 1),
		0x0095d9, true, 2.0f);
	DrawExtendGraph(BackBoxX, BackBoxY,
		BackBoxX+ UnderBoxWidth*0.5f, BackBoxY + UpBoxHeight,
		Graph, false);
	for (int i = 0; i < 2; i++)
	{
		DrawBoxAA(UnderBoxX, UnderBoxY + (kSelectMoveY * i),
			UnderBoxX + UnderBoxWidth, UnderBoxY + UnderBoxHeight + (kSelectMoveY * i),
			0xFFFFFF, false, 2.0f);
	}

	if (m_select == kBack)
	{
		DrawBoxAA(BackBoxX-3, BackBoxY-3,
			BackBoxX+UnderBoxWidth * 0.5f, BackBoxY + UpBoxHeight,
			0xff0000, false, 3.0f);
	}
	else {
		DrawBoxAA(m_selectPos.x, m_selectPos.y,
			m_selectPos.x + SelectSizeX, m_selectPos.y + SelectSizeY,
			0xff0000, false, 3.0f);
	}

	DrawFormatStringToHandle(BgmStringX, BgmStringY, m_pColorManager->GetColorWhite(),
		m_pFontManager->GetFont(), "BGM");
	DrawFormatStringToHandle(SeStringX, SeStringY, m_pColorManager->GetColorWhite(),
		m_pFontManager->GetFont(), "SeVolume");
	DrawStringToHandle(BackStringX, BackStringY,
		"�^�C�g���ɖ߂�", m_pColorManager->GetColorBlack(),
		m_pFontManager->GetFont());
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
	m_bgmDefo = LoadSoundMem("data/Sound/BGM/BGM_Defo.mp3");		// �f�t�HBGM
	PlaySoundMem(m_bgmDefo, DX_PLAYTYPE_LOOP, true);
}

void SoundManager::BGMButtle()
{
	m_bgmButtle = LoadSoundMem("data/Sound/BGM/BGM-Buttle.mp3");		// �퓬BGM
	PlaySoundMem(m_bgmButtle, DX_PLAYTYPE_LOOP, true);
}

void SoundManager::BGMGameClear()
{
	m_bgmGameClear = LoadSoundMem("data/Sound/BGM/BGM_GameClear.mp3");	// �Q�[���N���ABGM
	PlaySoundMem(m_bgmGameClear, DX_PLAYTYPE_LOOP, true);
}

void SoundManager::BGMGameOver()
{
	m_bgmGameOver = LoadSoundMem("data/Sound/BGM/BGM_GameOver.mp3");	// �Q�[���I�[�o�[BGM
	PlaySoundMem(m_bgmGameOver, DX_PLAYTYPE_LOOP, true);
}

void SoundManager::BGMExplanation()
{
	m_bgmExplanation = LoadSoundMem("data/Sound/BGM/BGM_Explanation.mp3");// ����������BGM
	PlaySoundMem(m_bgmExplanation, DX_PLAYTYPE_LOOP, true);
}

void SoundManager::ChangeSound()
{
	if (Pad::IsTrigger(PAD_INPUT_DOWN))
	{
		m_select = (m_select + 1) % kSclectNum;
		m_selectPos.y += kSelectMoveY;

		// �I�𒆂̎l�p����ԉ��ɂ�������l�p����ԏ�ɖ߂�
		if (m_selectPos.y > SelectBoxY + kSelectMoveY * (kSclectNum - 1))
		{
			m_selectPos.y = SelectBoxY;
		}
		SoundSelect();
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
		SoundSelect();
	}

	if (Pad::IsTrigger(PAD_INPUT_RIGHT))
	{
		if (m_select == kSeVolume)
		{
			SeVolume += MaxVolume * 0.08f;
			ChangeSEVolume(SeVolume);
			SetSeVolume();
			SoundSelect();
			if (SeVolume >= MaxVolume)
			{
				SeVolume = MaxVolume;
			}
			ChangeSe = SeVolume;
		}
		else if (m_select == kBgmVolume)
		{
			BgmVolume += MaxVolume * 0.08f;
			ChangeBGMVolume(BgmVolume);
			SetBgmVolume();
			SoundSelect();
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
			BgmVolume -= MaxVolume * 0.08f;
			ChangeBGMVolume(BgmVolume);
			SetBgmVolume();
			SoundSelect();
			if (BgmVolume <= 0)
			{
				BgmVolume = 0;
			}
			ChangeBgm = BgmVolume;
		}
		else if (m_select == kSeVolume)
		{
			SeVolume -= MaxVolume * 0.08f;
			ChangeSEVolume(SeVolume);
			SetSeVolume();
			SoundSelect();
			if (SeVolume <= 0)
			{
				SeVolume = 0;
			}
			ChangeSe = SeVolume;
		}
	}

	if (Pad::IsTrigger(PAD_INPUT_4))
	{
		if (m_select == kBack)
		{
			IsSceneEnd = true;
			SoundButton();
		}
	}
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
