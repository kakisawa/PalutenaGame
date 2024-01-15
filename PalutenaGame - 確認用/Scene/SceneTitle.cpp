#include "SceneTitle.h"
#include "DxLib.h"
#include "Game.h"
#include "Pad_Key.h"


SceneTitle::SceneTitle():
	m_isSceneEnd(false)
{
	
}


void SceneTitle::Init()
{
	// 背景のロード
	Graph = LoadGraph("data/Map/TitleGraph.jpg");
	m_isSceneEnd = false;
	
}

void SceneTitle::Update()
{
	// エンターキーが押されたらメイン画面へ遷移する
	if (Pad::IsTrigger(PAD_INPUT_4))
	{
		//if (!m_isSceneEnd)
		//{
		//	// // 効果音鳴らす
		//	// PlaySoundFile("data/sound/TitleDecide.mp3", DX_PLAYTYPE_BACK);
		//	PlaySoundMem(m_decideSe, DX_PLAYTYPE_BACK, true);
		//}

		// タイトル画面を終了してSceneMainに移動する処理を書きたい!
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
	DrawGraph(0, 0, Graph, false);
	DrawString(120, 120, "タイトル画面", GetColor(255, 255, 255));
	DrawString(120, 120 + 16, "Enterキーを押してください", GetColor(255, 255, 255));
}

void SceneTitle::End()
{
	// 背景をメモリから削除
	DeleteGraph(Graph);
}

bool SceneTitle::IsSceneEnd() const
{
	return m_isSceneEnd;
}
