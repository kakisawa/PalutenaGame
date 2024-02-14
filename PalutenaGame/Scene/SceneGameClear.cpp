#include "SceneGameClear.h"
#include "SceneManager.h"
#include "SceneMain.h"
#include "SceneSecond.h"
#include "SoundManager.h"
#include "FontManager.h"
#include "ColorManager.h"
#include "Player.h"
#include "Pad.h"
#include "Game.h"
#include "DxLib.h"

namespace
{
	// タイトル画像表示位置
	constexpr int kTitleGraphPosX = kScreenWidth * 0.27;
	constexpr int kTitleGraphPosY = kScreenHeight * 0.08f;
	// スコア画像表示位置
	constexpr int kScoreGraphPosX = kScreenWidth * 0.25f;
	constexpr int kScoreGraphPosY = kScreenHeight * 0.58f;
	// PushAキー画像表示位置
	constexpr int kPushAX = kScreenWidth * 0.398f;
	constexpr int kPushAY = kScreenHeight * 0.901f;

	// スコア数値表示位置
	constexpr int kScorePosX = kScoreGraphPosX * 2.2f;
	constexpr int kScorePosY = kScoreGraphPosY;

	// 選択肢四角内の文字表示位置
	constexpr int kSelectChirPosX = kScreenWidth * 0.2;
	constexpr int kSelectChirPosY = kScreenHeight * 0.8f;
	// 選択肢四角内の文字表示幅
	constexpr int kCharInterval = 770;
	// 選択肢四角の初期位置
	constexpr int kSelectPosX = kSelectChirPosX - 2;
	constexpr int kSelectPosY = kSelectChirPosY - 2;
	// 選択肢四角の移動量
	constexpr int kSelectMoveX = kCharInterval;
	// 選択肢四角のサイズ
	constexpr int kSelectSizeX = 470;
	constexpr int kSelectSizeY = 75;


	// スクロール移動量
	constexpr float backGround_scale = 1.2f;
	// 背景の拡大率
	constexpr int kBgScale = 1;
}

SceneGameClear::SceneGameClear() :
	m_isSceneEnd(false),
	m_select(kScelectBackTitle),
	m_scrollX(0),
	m_fadeAlpha(255),
	m_fadeLetter(0),
	ResultScore(0),
	m_selectPos(kSelectPosX, kSelectPosY)
{
	// SE・BGMメモリ確保
	m_pSoundManager = new SoundManager;
	// フォントメモリ
	m_pFontManager = new FontManager;
	// 色メモリ確保
	m_pColorManager = new ColorManager;
}

SceneGameClear::~SceneGameClear()
{
	// メモリ解放
	delete m_pSoundManager;
	m_pSoundManager = nullptr;
	delete m_pFontManager;
	m_pFontManager = nullptr;
	delete m_pColorManager;
	m_pColorManager = nullptr;
}

void SceneGameClear::Init()
{
	Graph = LoadGraph("data/Map/patter4.png");
	TitleGraph = LoadGraph("data/GameClear.png");
	ScoreGraph = LoadGraph("data/Score.png");
	Cursor = LoadGraph("data/Cursor.png");
	SelectUI = LoadGraph("data/SelectUI.png");
	SelectUI2 = LoadGraph("data/SelectUI2.png");
	PushA= LoadGraph("data/PushA.png");				// 「Aボタンで決定」グラフ読み込み

	m_select = kScelectBackTitle;
	m_isSceneEnd = false;
	m_scrollX = 0;
	m_fadeAlpha = 255;
	m_fadeLetter = 0;
	ResultScore = 0;
	m_selectPos.x = kSelectPosX;
	m_selectPos.y = kSelectPosY;

	//サウンドマネージャーの初期化
	m_pSoundManager->Init();

	m_pSoundManager->BGMGameClear();
}

void SceneGameClear::Update()
{
	m_pSoundManager->SetBgmVolume();
	m_pSoundManager->SetSeVolume();

	// 右キーを押したら選択状態を右に移す
	if (Pad::IsTrigger(PAD_INPUT_RIGHT))
	{
		// SE
		m_pSoundManager->SoundSelect();

		m_select = (m_select + 1) % kSclectNum;
		m_selectPos.x += kSelectMoveX;

		// 選択中の四角が一番下にだったら四角を一番上に戻す
		if (m_selectPos.x > kSelectPosX + kSelectMoveX * (kSclectNum - 1))
		{
			m_selectPos.x = kSelectPosX;
		}
	}
	// 左キーを押したら選択状態を左に移す
	else if (Pad::IsTrigger(PAD_INPUT_LEFT))
	{
		// SE
		m_pSoundManager->SoundSelect();

		m_select = (m_select - 1) % kSclectNum;
		m_selectPos.x -= kSelectMoveX;

		// 選択中の四角が一番下にだったら四角を一番上に戻す
		if (m_selectPos.x < kSelectPosX)
		{
			m_selectPos.x = kSelectPosX + kSelectMoveX * (kSclectNum - 1);
		}
	}

	// エンターキーが押されたらタイトル画面へ遷移する
	if (Pad::IsTrigger(PAD_INPUT_4))
	{
		switch (m_select)
		{
		case kScelectBackTitle:
			m_isSceneEnd = true;
			break;
		case kScelectEnd:
			DxLib_End();
			break;
		default:
			break;
		}

		// SE
		m_pSoundManager->SoundButton();
	}

	// 背景スクロール
	m_scrollX += backGround_scale;

	// 文字の点滅
	m_fadeLetter++;
	if (m_fadeLetter == 80)
	{
		m_fadeLetter = 0;
	}

	// フェードイン・アウト
	if (m_isSceneEnd)
	{
		m_fadeAlpha += 8;
		if (m_fadeAlpha > 255)
		{
			m_fadeAlpha = 255;
		}
	}
	else {
		m_fadeAlpha -= 8;
		if (m_fadeAlpha < 0)
		{
			m_fadeAlpha = 0;
		}
	}
}

void SceneGameClear::Draw()
{
	// 背景の描画
	BackDraw();
	// 画像描画
	UIDraw();
	// 選択肢等の文字の描画用
	StringDraw();

	// フェードの描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeAlpha);	// 半透明で表示開始
	DrawBox(0, 0, kScreenWidth, kScreenHeight, m_pColorManager->GetColorBlack(), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		// 不透明に戻しておく
}

void SceneGameClear::End()
{
	DeleteGraph(Graph);		// 背景をメモリから削除
	m_pSoundManager->End();
}

void SceneGameClear::StringDraw()
{
	DrawStringToHandle(kSelectChirPosX, kSelectChirPosY, "  タイトルに戻る",
		m_pColorManager->GetColorBlack(), m_pFontManager->GetFont());
	DrawStringToHandle(kSelectChirPosX + kCharInterval, kSelectChirPosY, "  ゲームを終わる",
		m_pColorManager->GetColorBlack(), m_pFontManager->GetFont());

	ResultScore = SceneManager::s_ResultScore;
	DrawFormatStringToHandle(kScorePosX+2, kScorePosY+2,
		m_pColorManager->GetColorWhite(), m_pFontManager->GetFont3(),
		"%4d", ResultScore);
	DrawFormatStringToHandle(kScorePosX, kScorePosY,
		m_pColorManager->GetColorBlack(), m_pFontManager->GetFont3(),
		"%4d", ResultScore);

	// 文字の点滅描画
	if (m_fadeLetter < 60)
	{
		DrawExtendGraph(kPushAX, kPushAY,
			kPushAX + 560, kPushAY + 80,
			PushA, true);
	}
}

void SceneGameClear::BackDraw()
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

void SceneGameClear::UIDraw()
{
	DrawGraph(kTitleGraphPosX, kTitleGraphPosY, TitleGraph, true);
	DrawGraph(kScoreGraphPosX, kScoreGraphPosY, ScoreGraph, true);

	// タイトルに戻る・ゲームを終了するBOX
	for (int i = 0; i < 2; i++) {
		DrawGraph(kSelectPosX + (kCharInterval * i), kSelectPosY,
			SelectUI, false);
	}

	// 選択中の部分を四角で描画
	DrawGraph(m_selectPos.x, m_selectPos.y,
		SelectUI2, false);
	DrawExtendGraph(m_selectPos.x - 20, m_selectPos.y - 20,
		m_selectPos.x + kSelectSizeX + 20,
		m_selectPos.y + kSelectSizeY + 20,
		Cursor, true);
}

bool SceneGameClear::IsSceneEnd() const
{
	return m_isSceneEnd && (m_fadeAlpha >= 255);
}