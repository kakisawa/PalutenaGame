#include "SceneGameOver.h"
#include "SceneManager.h"
#include "SoundManager.h"
#include "FontManager.h"
#include "Pad.h"
#include "Game.h"
#include "DxLib.h"

namespace
{
	// タイトル文字表示位置
	constexpr int kTitleChirPosX = kScreenWidth * 0.03f;
	constexpr int kTitleChirPosY = kScreenHeight * 0.05f;

	// スコア文字表示位置
	constexpr int kScoreChirPosX = kScreenWidth * 0.43f;
	constexpr int kScoreChirPosY = kScreenHeight * 0.15f;

	// 選択文字の表示位置
	constexpr int kSelectChirPosX = kScreenWidth * 0.15;
	constexpr int kSelectChirPosY = kScreenHeight * 0.83;

	// 文字の表示幅
	constexpr int kCharInterval = 770;

	// 選択文字を囲む四角の初期位置
	constexpr int kSelectPosX = kSelectChirPosX - 2;
	constexpr int kSelectPosY = kSelectChirPosY - 2;

	// 選択文字を囲む四角の移動量
	constexpr int kSelectMoveX = 770;

	// 選択文字を囲む四角のサイズ
	constexpr int kSelectSizeX = kScreenWidth*0.31;
	constexpr int kSelectSizeY = 75;

	// スクロール移動量
	constexpr float backGround_scale = 1.2f;
	// 背景の拡大率
	constexpr int kBgScale = 1;
}

SceneGameOver::SceneGameOver() :
	m_isSceneEnd(false),
	m_select(kScelectBackTitle),
	m_scrollX(0),
	m_fadeAlpha(255),
	m_fadeLetter(0),
	m_selectPos(kSelectPosX, kSelectPosY)
{
	// SE・BGMメモリ確保
	m_pSoundManager = new SoundManager;
	// フォントメモリ
	m_pFontManager = new FontManager;
}

SceneGameOver::~SceneGameOver()
{
	// メモリ解放
	delete m_pSoundManager;
	m_pSoundManager = nullptr;
	delete m_pFontManager;
	m_pFontManager = nullptr;
}

void SceneGameOver::Init()
{
	Graph = LoadGraph("data/Map/patter3.png");
	Cursor = LoadGraph("data/Cursor.png");				// カーソルロゴ読み込み

	m_select= kScelectBackTitle;
	m_isSceneEnd = false;
	m_scrollX = 0;
	m_fadeAlpha = 255;
	m_fadeLetter = 0;
	m_selectPos.x = kSelectPosX;
	m_selectPos.y = kSelectPosY;

	//サウンドマネージャーの初期化
	m_pSoundManager->Init();

	m_pSoundManager->BGMGameOver();
}

void SceneGameOver::Update()
{
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

void SceneGameOver::Draw()
{
	// 背景の描画
	BackDraw();
	// 選択肢等の文字の描画用
	StringDraw();

	// フェードの描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeAlpha);	// 半透明で表示開始
	DrawBox(0, 0, kScreenWidth, kScreenHeight, GetColor(255, 255, 255), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		// 不透明に戻しておく
}

void SceneGameOver::End()
{
	// 背景をメモリから削除
	DeleteGraph(Graph);

	m_pSoundManager->End();
}

void SceneGameOver::StringDraw()
{

	for (int i = 0; i < 2; i++)
	{
		DrawBox(kSelectPosX + (kCharInterval * i), kSelectPosY,
			kSelectPosX + (kSelectSizeX + (kCharInterval * i)), kSelectPosY + kSelectSizeY,
			0xF4EADE, true);

		DrawBox(kSelectPosX + (kCharInterval * i), kSelectPosY,
			kSelectPosX + (kSelectSizeX + (kCharInterval * i)), kSelectPosY + kSelectSizeY,
			0x99e6ff, false);
	}

	// 選択中の部分を四角で描画
	DrawBox(m_selectPos.x, m_selectPos.y,
		m_selectPos.x + kSelectSizeX, m_selectPos.y + kSelectSizeY,
		0x00bfff, true);
	DrawExtendGraph(m_selectPos.x - 20, m_selectPos.y - 20,
		m_selectPos.x + kSelectSizeX + 20, m_selectPos.y + kSelectSizeY + 20,
		Cursor, true);

	SetFontSize(96);
	DrawString(kScoreChirPosX, kScoreChirPosY, "スコア", 0x000000);

	SetFontSize(64);

	DrawString(kTitleChirPosX, kTitleChirPosY, "ゲームオーバー画面", 0x000000);

	DrawStringToHandle(kSelectChirPosX, kSelectChirPosY, "タイトル画面に戻る", 
		0x000000, m_pFontManager->GetFont());
	DrawStringToHandle(kSelectChirPosX + kCharInterval, kSelectChirPosY, "　ゲームを終わる", 
		0x000000, m_pFontManager->GetFont());

	// 文字の点滅描画
	if (m_fadeLetter < 60)
	{
		SetFontSize(32);
		DrawString(kSelectChirPosX + 123, kSelectChirPosY + kCharInterval * 3.6, "Aキーで決定", 0xffffff);
	}
}

void SceneGameOver::BackDraw()
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

bool SceneGameOver::IsSceneEnd() const
{
	return m_isSceneEnd && (m_fadeAlpha >= 255);
}