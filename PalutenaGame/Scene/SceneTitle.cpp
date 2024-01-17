#include "SceneTitle.h"
#include "DxLib.h"
#include "Game.h"
#include "Pad.h"

namespace
{
	// 文字の表示位置

	// 文字を囲む四角の位置

	// 文字を囲む資格の移動量

}

SceneTitle::SceneTitle():
	m_isSceneEnd(false),
	m_select(kSelectGameState)
{
	
}

void SceneTitle::Init()
{
	Graph = LoadGraph("data/Map/TitleGraph.jpg");	// 背景読み込み
	TitleGraph = LoadGraph("data/TitleGraph.png");		// タイトルロゴ読み込み

	/*m_selectPos.x = kInitSelectPosX;
	m_selectPos.y = kInitSelectPosY;*/

	m_isSceneEnd = false;
}

void SceneTitle::Update()
{
	if (Pad::IsTrigger(KEY_INPUT_DOWN))
	{
		m_select = (m_select + 1) % kSclectNum;
	}


	// Aボタンが押されたらメイン画面へ遷移する
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
	//DrawGraph(0, 0, Graph, false);
	DrawExtendGraph(-120, -160, 850, 510, TitleGraph, true);
	DrawString(330, 340, "操作説明", GetColor(255, 255, 255));
	DrawString(300, 375, "ゲームを始める", GetColor(255, 255, 255));
	DrawString(300, 415, "ゲームを終わる", GetColor(255, 255, 255));

}

void SceneTitle::End()
{
	// 画像をメモリから削除
	DeleteGraph(Graph);
	DeleteGraph(TitleGraph);
}

bool SceneTitle::IsSceneEnd() const
{
	return m_isSceneEnd;
}
