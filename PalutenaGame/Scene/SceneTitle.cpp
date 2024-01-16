#include "SceneTitle.h"
#include "DxLib.h"
#include "Game.h"
#include "Pad.h"


SceneTitle::SceneTitle():
	m_isSceneEnd(false)
{
	
}


void SceneTitle::Init()
{
	Graph = LoadGraph("data/Map/TitleGraph.jpg");	// �w�i�ǂݍ���
	TitleGraph = LoadGraph("data/TitleGraph.png");		// �^�C�g�����S�ǂݍ���

	m_isSceneEnd = false;
}

void SceneTitle::Update()
{
	// A�{�^���������ꂽ�烁�C����ʂ֑J�ڂ���
	if (Pad::IsTrigger(PAD_INPUT_4))
	{
		//if (!m_isSceneEnd)
		//{
		//	// // ���ʉ��炷
		//	// PlaySoundFile("data/sound/TitleDecide.mp3", DX_PLAYTYPE_BACK);
		//	PlaySoundMem(m_decideSe, DX_PLAYTYPE_BACK, true);
		//}

		// �^�C�g����ʂ��I������SceneMain�Ɉړ����鏈������������!
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

void SceneTitle::Draw()
{
	//DrawGraph(0, 0, Graph, false);
	DrawExtendGraph(-120, -160, 850, 510, TitleGraph, true);
	DrawString(260, 350 + 16, "A�{�^���������Ă�������", GetColor(255, 255, 255));
}

void SceneTitle::End()
{
	// �摜������������폜
	DeleteGraph(Graph);
	DeleteGraph(TitleGraph);
}

bool SceneTitle::IsSceneEnd() const
{
	return m_isSceneEnd;
}
