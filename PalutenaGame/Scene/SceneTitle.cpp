#include "SceneTitle.h"
#include "DxLib.h"
#include "Game.h"
#include "Pad.h"
#include "Util/Font.h"

namespace
{
	// 文字の表示位置
	constexpr int kChirPosX = kScreenWidth * 0.38;
	constexpr int kChirPosY = kScreenHeight * 0.65;

	// 文字の表示幅
	constexpr int kCharInterval = 90;

	// 文字を囲む四角の初期位置
	constexpr int kSelectPosX = kChirPosX - 2;
	constexpr int kSelectPosY = kChirPosY - 2;

	// 文字を囲む四角の移動量
	constexpr int kSelectMoveY = 90;

	// 文字を囲む四角のサイズ
	constexpr int kSelectSizeX = 460;
	constexpr int kSelectSizeY = 75;

	// タイトルロゴ表示位置
	constexpr int kLogoPosX = kScreenWidth * 0.08;
	constexpr int kLogoPosY = -150;

	// タイトルロゴサイズ
	constexpr int kLogoSizeX = 1637;
	constexpr int kLogoSizeY = 1089;

	// スクロール移動量
	constexpr float backGround_scale = 1.2f;
	// 背景の拡大率
	constexpr int kBgScale = 1;
}

SceneTitle::SceneTitle() :
	x(0),
	y(0),
	m_isSceneEnd(false),
	isToExplanation(false),
	isToSelect(false),
	m_scrollX(0),
	m_select(kSelectGameStart),
	m_selectPos(kSelectPosX, kSelectPosY + kSelectMoveY),
	m_bgPos(0, 0),
	m_fadeAlpha(255),
	m_fadeLetter(0)
{
	// フォントのメモリ確保
	m_pFont = new Font;
}

SceneTitle::~SceneTitle()
{
	// フォントメモリの解放
	delete m_pFont;
	m_pFont = nullptr;
}

void SceneTitle::Init()
{
	Graph = LoadGraph("data/Map/patter.png");	// 背景読み込み
	TitleGraph = LoadGraph("data/TitleGraph3.png");		// タイトルロゴ読み込み

	m_select = kSelectGameStart;

	m_isSceneEnd = false;
	isToExplanation = false;
	isToSelect = false;
	m_selectPos.x = kSelectPosX;
	m_selectPos.y = kSelectPosY + kSelectMoveY;
	m_scrollX = 0;
	m_bgPos.x = 0;
	m_bgPos.y = 0;
	m_fadeLetter = 0;
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
			m_isSceneEnd = true;
			isToExplanation = true;
			break;
		case kSelectGameStart:
			m_isSceneEnd = true;
			isToSelect = true;
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

	// 背景スクロール
	m_scrollX += backGround_scale;

	// 文字の点滅
	m_fadeLetter++;
	if (m_fadeLetter == 80)
	{
		m_fadeLetter = 0;
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
	// 背景・タイトルの描画
	BackDraw();
	DrawExtendGraph(kLogoPosX, kLogoPosY, kLogoPosX + kLogoSizeX, kLogoPosY + kLogoSizeY, TitleGraph, true);

	// 選択肢等の文字の描画用
	StringDraw();
}

void SceneTitle::End()
{
	// 画像をメモリから削除
	DeleteGraph(Graph);
	DeleteGraph(TitleGraph);
}

void SceneTitle::StringDraw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeAlpha);	// 半透明で表示開始
	DrawBox(0, 0, kScreenWidth, kScreenHeight, GetColor(255, 255, 255), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		// 不透明に戻しておく

	for (int i = 0; i < 3; i++)
	{
		DrawBox(m_selectPos.x, kSelectPosY + (kCharInterval * i), m_selectPos.x + kSelectSizeX,
			kSelectPosY + (kSelectSizeY + (kCharInterval * i)), 0xF4EADE, true);

		DrawBox(m_selectPos.x, kSelectPosY + (kCharInterval * i), m_selectPos.x + kSelectSizeX,
			kSelectPosY + (kSelectSizeY + (kCharInterval * i)), 0x99e6ff, false);
	}

	// 選択中の部分を四角で描画
	DrawBox(m_selectPos.x, m_selectPos.y, m_selectPos.x + kSelectSizeX,
		m_selectPos.y + kSelectSizeY, 0x00bfff, true);

	SetFontSize(64);

	DrawString(kChirPosX + 100, kChirPosY, "操作説明", 0x000000);

	//DrawStringToHandle(kChirPosX + 100, kChirPosY, "操作説明", 0x000000, m_pFont->m_TitleFont);
	DrawString(kChirPosX, kChirPosY + kCharInterval, "ゲームを始める", 0x000000);
	DrawString(kChirPosX, kChirPosY + kCharInterval * 2, "ゲームを終わる", 0x000000);

	// 文字の点滅描画
	if (m_fadeLetter < 60)
	{
		SetFontSize(32);
		DrawString(kChirPosX + 123, kChirPosY + kCharInterval * 3.6, "Aキーで決定", 0xffffff);
	}
}

void SceneTitle::BackDraw()
{
	Size bg1Size;
	GetGraphSize(Graph, &bg1Size.width, &bg1Size.height);

	// スクロール量を計算
	int scrollBg = static_cast<int>(m_scrollX) % static_cast<int>(bg1Size.width * kBgScale);

	for (int index = 0; index < 4; index++)
	{
		DrawRotaGraph2(-scrollBg + index * bg1Size.width * kBgScale,
			kScreenHeight - bg1Size.height * kBgScale,
			0, 0,
			kBgScale, 0.0f,
			Graph, true);
	}
}

bool SceneTitle::IsSceneEnd() const
{
	return m_isSceneEnd && (m_fadeAlpha >= 255);
}

bool SceneTitle::ToStage() const
{
	return isToSelect;
}

bool SceneTitle::ToExplanation() const
{
	return isToExplanation;
}
