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
	// エンターキーが押されたらタイトル画面へ遷移する
	if (Pad::IsTrigger(PAD_INPUT_4))
	{
		//if (!m_isSceneEnd)
		//{
		//	// // 効果音鳴らす
		//	// PlaySoundFile("data/sound/TitleDecide.mp3", DX_PLAYTYPE_BACK);
		//	PlaySoundMem(m_decideSe, DX_PLAYTYPE_BACK, true);
		//}

		// タイトル画面を終了してタイトルに移動する処理を書きたい!
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
	DrawString(120, 120, "ゲームオーバー画面", GetColor(255, 255, 255));
	DrawString(120, 120 + 16, "Enterキーを押してください", GetColor(255, 255, 255));
}

void SceneGameOver::End()
{
	// 背景をメモリから削除
	DeleteGraph(Graph);
}

bool SceneGameOver::IsSceneEnd() const
{
	return m_isSceneEnd;
}
