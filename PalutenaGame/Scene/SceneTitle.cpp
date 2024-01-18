#include "SceneTitle.h"
#include "DxLib.h"
#include "Game.h"
#include "Pad.h"

namespace
{
	// 文字の表示位置
	constexpr int kChirPosX = kScreenWidth * 0.4;
	constexpr int kChirPosY = kScreenHeight * 0.7;

	// 文字の表示幅
	constexpr int kCharInterval = 35;

	// 文字を囲む四角の初期位置
	constexpr int kSelectPosX = kChirPosX - 2;
	constexpr int kSelectPosY = kChirPosY - 6;

	// 文字を囲む四角の移動量
	constexpr int kSelectMoveY = 35;

	// 文字を囲む四角のサイズ
	constexpr int kSelectSizeX = 120;
	constexpr int kSelectSizeY = 30;
}

SceneTitle::SceneTitle() :
	m_isSceneEnd(false),
	m_isGameEnd(false),
	m_select(kSclectOperation),
	m_selectPos(kSelectPosX, kSelectPosY),
	m_fadeAlpha(255)
{
}

void SceneTitle::Init()
{
	Graph = LoadGraph("data/Map/TitleGraph.jpg");	// 背景読み込み
	TitleGraph = LoadGraph("data/TitleGraph.png");		// タイトルロゴ読み込み

	m_select=kSclectOperation;
	m_isSceneEnd = false;
	m_selectPos.x = kSelectPosX;
	m_selectPos.y = kSelectPosY;
}

void SceneTitle::Update()
{
	// ↓キーを押したら選択状態を一つ下げる
	if (Pad::IsTrigger(PAD_INPUT_DOWN))
	{
		m_select = (m_select + 1) % kSclectNum;
		m_selectPos.y += kSelectMoveY;

		// 選択中の四角が一番下にだったら四角を一番上に戻す
		if (m_selectPos.y > kSelectPosY + kSelectMoveY * (kSclectNum - 1))
		{
			m_selectPos.y = kSelectPosY;
		}
	}
	// 上キーを押したら選択状態を一つ上げる
	else if (Pad::IsTrigger(PAD_INPUT_UP))
	{
		m_select = (m_select - 1) % kSclectNum;
		m_selectPos.y -= kSelectMoveY;

		// 選択中の四角が一番下にだったら四角を一番上に戻す
		if (m_selectPos.y < kSelectPosY)
		{
			m_selectPos.y = kSelectPosY + kSelectMoveY * (kSclectNum - 1);
		}
	}

	// Aボタンが押されたらメイン画面へ遷移する
	if (Pad::IsTrigger(PAD_INPUT_4))
	{
		switch (m_select)
		{
		case kSclectOperation:
			break;
		case kSelectGameState:
			m_isSceneEnd = true;
			break;
		case kSclectEnd:
			DxLib_End();
			break;
		default:
			break;
		}

		//if (!m_isSceneEnd)
		//{
		//	// // 効果音鳴らす
		//	// PlaySoundFile("data/sound/TitleDecide.mp3", DX_PLAYTYPE_BACK);
		//	PlaySoundMem(m_decideSe, DX_PLAYTYPE_BACK, true);
		//}
		// タイトル画面を終了してSceneMainに移動する処理を書きたい!
	}

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

void SceneTitle::Draw()
{
	DrawExtendGraph(-120, -160, 850, 510, TitleGraph, true);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeAlpha);	// 半透明で表示開始
	DrawBox(0, 0, kScreenWidth, kScreenHeight, GetColor(255, 255, 255), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		// 不透明に戻しておく

	DrawString(kChirPosX + 25, kChirPosY, "操作説明", 0xffffff);
	DrawString(kChirPosX, kChirPosY + kCharInterval, "ゲームを始める", 0xffffff);
	DrawString(kChirPosX, kChirPosY + kCharInterval * 2, "ゲームを終わる", 0xffffff);

	// 選択中の部分を四角で描画
	DrawBox(m_selectPos.x, m_selectPos.y, m_selectPos.x + kSelectSizeX,
		m_selectPos.y + kSelectSizeY, 0x00bfff, false);
}

void SceneTitle::End()
{
	// 画像をメモリから削除
	DeleteGraph(Graph);
	DeleteGraph(TitleGraph);
}

bool SceneTitle::IsSceneEnd() const
{
	return m_isSceneEnd && (m_fadeAlpha >= 255);
}
