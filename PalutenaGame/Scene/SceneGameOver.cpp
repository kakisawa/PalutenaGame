#include "SceneGameOver.h"
#include "Pad.h"
#include "Game.h"
#include "DxLib.h"

SceneGameOver::SceneGameOver() :
	m_isSceneEnd(false),
	m_fadeAlpha(255)
{

}

SceneGameOver::~SceneGameOver()
{
}

void SceneGameOver::Init()
{
	Graph = LoadGraph("data/Map/GameOverGraph.jpg");
	m_isSceneEnd = false;
	m_fadeAlpha = 255;
}

void SceneGameOver::Update()
{
	// �G���^�[�L�[�������ꂽ��^�C�g����ʂ֑J�ڂ���
	if (Pad::IsTrigger(PAD_INPUT_4))
	{
		//if (!m_isSceneEnd)
		//{
		//	// // ���ʉ��炷
		//	// PlaySoundFile("data/sound/TitleDecide.mp3", DX_PLAYTYPE_BACK);
		//	PlaySoundMem(m_decideSe, DX_PLAYTYPE_BACK, true);
		//}

		// �^�C�g����ʂ��I�����ă^�C�g���Ɉړ����鏈������������!
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

void SceneGameOver::Draw()
{
	DrawGraph(0, 0, Graph, false);
	DrawString(120, 120, "�Q�[���I�[�o�[���", GetColor(255, 255, 255));
	DrawString(120, 120 + 16, "Enter�L�[�������Ă�������", GetColor(255, 255, 255));

	// �t�F�[�h�̕`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeAlpha);	// �������ŕ\���J�n
	DrawBox(0, 0, kScreenWidth, kScreenHeight, GetColor(255, 255, 255), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		// �s�����ɖ߂��Ă���
}

void SceneGameOver::End()
{
	// �w�i������������폜
	DeleteGraph(Graph);
}

bool SceneGameOver::IsSceneEnd() const
{
	return m_isSceneEnd;
}
