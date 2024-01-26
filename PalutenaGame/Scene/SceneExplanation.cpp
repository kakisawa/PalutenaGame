#include "SceneExplanation.h"
#include "DxLib.h"
#include "Pad.h"
#include "Game.h"

namespace
{
	// �����̕\���ʒu
	constexpr int kChirPosX = kScreenWidth * 0.4;
	constexpr int kChirPosY = kScreenHeight * 0.8;
}

SceneExplanation::SceneExplanation():
	m_isSceneEnd(false),
	m_fadeAlpha(255)
{
}

SceneExplanation::~SceneExplanation()
{
}

void SceneExplanation::Init()
{
	Graph = LoadGraph("data/Explanation.png");
	m_isSceneEnd = false;
	m_fadeAlpha = 255;
}

void SceneExplanation::Update()
{

	if (Pad::IsTrigger(PAD_INPUT_4))
	{
		m_isSceneEnd = true;

		m_fadeAlpha += 8;
		if (m_fadeAlpha > 255)
		{
			m_fadeAlpha = 255;
		}
	}

	m_fadeAlpha -= 8;
	if (m_fadeAlpha < 0)
	{
		m_fadeAlpha = 0;
	}
}

void SceneExplanation::Draw()
{
	DrawGraph(0, 0, Graph, false);
	DrawString(120, 120, "�Q�[���N���A���", GetColor(255, 255, 255));
	DrawString(120, 120 + 64, "A�L�[�������Ă�������", GetColor(255, 255, 255));

	// �t�F�[�h�̕`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeAlpha);	// �������ŕ\���J�n
	DrawBox(0, 0, kScreenWidth, kScreenHeight, GetColor(255, 255, 255), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		// �s�����ɖ߂��Ă���

	SetFontSize(64);

	DrawString(kChirPosX, kChirPosY, "A�{�^���Ń^�C�g���ɖ߂�", 0xffffff);
}

void SceneExplanation::End()
{
	// �w�i������������폜
	DeleteGraph(Graph);
}

bool SceneExplanation::IsSceneEnd() const
{
	return m_isSceneEnd;
}
