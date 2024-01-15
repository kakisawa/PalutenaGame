#include "SceneGameOver.h"
#include "Pad.h"
#include "DxLib.h"

SceneGameOver::SceneGameOver():
	m_isSceneEnd(false)
{
	
}

SceneGameOver::~SceneGameOver()
{
}

void SceneGameOver::Init()
{
	Graph = LoadGraph("data/Map/GameOverGraph.jpg");
	m_isSceneEnd = false;
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
	}

	/*if (m_isSceneEnd)
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
	}*/
}

void SceneGameOver::Draw()
{
	DrawGraph(0, 0, Graph, false);
	DrawString(120, 120, "�Q�[���I�[�o�[���", GetColor(255, 255, 255));
	DrawString(120, 120 + 16, "Enter�L�[�������Ă�������", GetColor(255, 255, 255));
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
