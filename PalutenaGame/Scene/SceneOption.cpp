#include "SceneOption.h"
#include "SoundManager.h"
#include "ColorManager.h"
#include "FontManager.h"
#include "DxLib.h"
#include "Pad.h"
#include "Game.h"
#include <cassert>

namespace
{
	// �����̕\���ʒu
	constexpr int kSelectChirPosX = kScreenWidth * 0.2;
	constexpr int kSelectChirPosY = kScreenHeight * 0.87;

	// �X�N���[���ړ���
	constexpr float backGround_scale = 1.2f;
	// �w�i�̊g�嗦
	constexpr int kBgScale = 1;
}

SceneOption::SceneOption():
	m_isSceneEnd(false),
	m_fadeAlpha(255)
{
	// �������m��
	m_pSoundManager = new SoundManager;
	// �F�������m��
	m_pColorManager = new ColorManager;
	// �t�H���g������
	m_pFontManager = new FontManager;
}


SceneOption::~SceneOption()
{
	// �T�E���h���������
	delete m_pSoundManager;
	m_pSoundManager = nullptr;
	// �F���������
	delete m_pColorManager;
	m_pColorManager = nullptr;
	delete m_pFontManager;
	m_pFontManager = nullptr;
}

void SceneOption::Init()
{
	//�T�E���h�}�l�[�W���[�̏�����
	m_pSoundManager->Init();
	m_pSoundManager->BGMExplanation();

	BgGraph = LoadGraph("data/Map/patter.png");
	m_isSceneEnd = false;
	m_fadeAlpha = 255;
}

void SceneOption::Update()
{
	m_pSoundManager->ChangeSound();

	m_pSoundManager->SetBgmVolume();
	m_pSoundManager->SetSeVolume();

	if (Pad::IsTrigger(PAD_INPUT_4))
	{
		m_isSceneEnd = true;

		m_pSoundManager->SoundButton();
	}

	// �w�i�X�N���[��
	m_scrollX += backGround_scale;

	// �t�F�[�h�C��
	if (m_isSceneEnd)
	{
		m_fadeAlpha += 8;
		if (m_fadeAlpha > 255)
		{
			m_fadeAlpha = 255;
		}
	}
	else
	{
		m_fadeAlpha -= 8;
		if (m_fadeAlpha < 0)
		{
			m_fadeAlpha = 0;
		}
	}
}

void SceneOption::Draw()
{
	BackDraw();

	DrawBox(kScreenWidth * 0.1f-3, kScreenHeight * 0.1f-3,
		kScreenWidth * 0.9f+3, kScreenHeight * 0.8f+3,
		m_pColorManager->GetColorWhite(), true);
	DrawBox(kScreenWidth * 0.1f, kScreenHeight * 0.1f, 
		kScreenWidth * 0.9f, kScreenHeight * 0.8f, 
		m_pColorManager->GetColorBlack(), true);


	m_pSoundManager->Draw();

	SetFontSize(64);
	DrawString(kSelectChirPosX, kSelectChirPosY,
		"A�{�^���Ń^�C�g���ɖ߂�", m_pColorManager->GetColorWhite(), m_pFontManager->GetFont());

	// �t�F�[�h�̕`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeAlpha);	// �������ŕ\���J�n
	DrawBox(0, 0, kScreenWidth, kScreenHeight,
		m_pColorManager->GetColorBlack(), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		// �s�����ɖ߂��Ă���
}

void SceneOption::End()
{
	// �w�i������������폜
	DeleteGraph(Graph);

	StopSoundMem(m_pSoundManager->m_bgmExplanation);
	m_pSoundManager->End();
}

void SceneOption::BackDraw()
{
	Size bg1Size;
	GetGraphSize(BgGraph, &bg1Size.width, &bg1Size.height);

	// �X�N���[���ʂ��v�Z
	int scrollBg = static_cast<int>(m_scrollX) % static_cast<int>(bg1Size.width * kBgScale);

	for (int index = 0; index < 4; index++)
	{
		DrawRotaGraph2(-scrollBg + index * bg1Size.width * kBgScale,
			kScreenHeight - bg1Size.height * kBgScale,
			0, 0,
			kBgScale, 0.0f,
			BgGraph, true);
	}
}

bool SceneOption::IsSceneEnd() const
{
	return m_isSceneEnd && (m_fadeAlpha >= 255);
}
