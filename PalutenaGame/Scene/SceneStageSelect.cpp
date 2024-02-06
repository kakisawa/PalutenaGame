#include "SceneStageSelect.h"
#include "SoundManager.h"
#include "FontManager.h"
#include "DxLib.h"
#include "Game.h"
#include "Pad.h"

namespace
{
	// 文字の表示位置
	constexpr int kSelectChirPosX = kScreenWidth * 0.08f;
	constexpr int kSelectChirPosY = kScreenHeight * 0.15f;

	constexpr int kSelectBackChirPosX = kScreenWidth * 0.43f;
	constexpr int kSelectBackChirPosY = kScreenHeight * 0.85f;

	// 文字の表示幅
	constexpr int kCharInterval = 180;

	// 文字を囲む四角の初期位置
	constexpr int kSelectPosX = kSelectChirPosX - 2;
	constexpr int kSelectPosY = kSelectChirPosY - 2;

	// 文字を囲む四角の移動量
	constexpr int kSelectMoveY = 180;

	// 文字を囲む四角のサイズ
	constexpr int kSelectSizeX = kScreenWidth*0.245;
	constexpr int kSelectSizeY = 75;

	// スクロール移動量
	constexpr float backGround_scale = 1.2f;
	// 背景の拡大率
	constexpr int kBgScale = 1;
}

SceneStageSelect::SceneStageSelect() :
	m_select(kStage1),
	isStage1(false),
	isStage2(false),
	isBackTitle(false),
	m_scrollX(0),
	m_selectPos(kSelectPosX, kSelectPosY),
	m_bgPos(0, 0),
	m_fadeLetter(0),
	m_fadeAlpha(255)
{
	// SE/BGMメモリ確保
	m_pSoundManager = new SoundManager;
	// フォントメモリ確保
	m_pFontManager = new FontManager;
}

SceneStageSelect::~SceneStageSelect()
{
	// メモリ解放
	delete m_pSoundManager;
	m_pSoundManager = nullptr;
	delete m_pFontManager;
	m_pFontManager = nullptr;
}

void SceneStageSelect::Init()
{
	Graph = LoadGraph("data/Map/patter.png");	// 背景読み込み
	Cursor = LoadGraph("data/Cursor.png");		// カーソルロゴ読み込み
	PushA = LoadGraph("data/PushA.png");				// 「Aボタンで決定」グラフ読み込み

	m_select = kStage1;
	m_isSceneEnd = false;
	isStage1 = false;
	isStage2 = false;
	isBackTitle = false;
	m_selectPos.x = kSelectPosX;
	m_selectPos.y = kSelectPosY;
	m_scrollX = 0;
	m_bgPos.x = 0;
	m_bgPos.y = 0;
	m_fadeAlpha = 255;
	m_fadeLetter = 0;

	//サウンドマネージャーの初期化
	m_pSoundManager->Init();

	m_pSoundManager->BGMDefo();
}

void SceneStageSelect::Update()
{
	// ↓キーを押したら選択状態を一つ下げる
	if (Pad::IsTrigger(PAD_INPUT_DOWN))
	{
		m_pSoundManager->SoundSelect();

		m_select = (m_select + 1) % kSclectNum;

		// 選択中の四角が一番下だったら四角を一番上に戻す
		if (m_selectPos.y >= 918){
			m_selectPos.x = kSelectPosX;
			m_selectPos.y = kSelectPosY;
			return;
		}
		if (m_selectPos.y == kSelectPosY) {
			m_selectPos.y += kSelectMoveY;
		}
		else if(m_selectPos.y == 340){
			m_selectPos.x = 825;
			m_selectPos.y = 918;
		}
	}
	// 上キーを押したら選択状態を一つ上げる
	else if (Pad::IsTrigger(PAD_INPUT_UP))
	{
		m_pSoundManager->SoundSelect();

		m_select = (m_select - 1) % kSclectNum;

		// 選択中の四角が一番上だったら四角を一番下に戻す
		if (m_selectPos.y == kSelectPosY)
		{
			m_selectPos.x = 825;
			m_selectPos.y = 918;
			m_select = kBackTitle;
			return;
		}

		if (m_selectPos.y == 340) {
			m_selectPos.y -= kSelectMoveY;
		}
		else if (m_selectPos.y == 918)
		{
			m_selectPos.x = kSelectPosX;
			m_selectPos.y = 340;
			return;
		}
	}

	// Aボタンが押されたらメイン画面へ遷移する
	if (Pad::IsTrigger(PAD_INPUT_4))
	{
		// SE
		m_pSoundManager->SoundButton();
		
		switch (m_select)
		{
		case kStage1:
 			m_isSceneEnd = true;
			isStage1 = true;
			break;
		case kStage2:
			m_isSceneEnd = true;
			isStage2 = true;
			break;
		case kBackTitle:
			isBackTitle = true;
			m_isSceneEnd = true;
			break;
		default:
			break;
		}
	}

	// 背景スクロール
	m_scrollX += backGround_scale;

	// 文字の点滅
	m_fadeLetter++;
	if (m_fadeLetter == 80)
	{
		m_fadeLetter = 0;
	}
	// フェードイン
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

void SceneStageSelect::Draw()
{
	// 背景の描画
	BackDraw();	
	// 選択肢等の文字の描画用
	StringDraw();
}

void SceneStageSelect::End()
{
	// 画像をメモリから削除
	DeleteGraph(Graph);
	DeleteGraph(Cursor);

	m_pSoundManager->End();
}

void SceneStageSelect::StringDraw()
{
	// ステージセレクトBox
	for (int i = 0; i < 2; i++)
	{
		DrawBox(kSelectPosX, kSelectPosY + (kCharInterval * i), kSelectPosX + kSelectSizeX,
			kSelectPosY + (kSelectSizeY + (kCharInterval * i)), 0xF4EADE, true);

		DrawBox(kSelectPosX, kSelectPosY + (kCharInterval * i), kSelectPosX + kSelectSizeX,
			kSelectPosY + (kSelectSizeY + (kCharInterval * i)), 0x99e6ff, false);
	}
	// タイトルに戻るBox
	DrawBox(kSelectBackChirPosX, kSelectBackChirPosY,
		kSelectBackChirPosX + kSelectSizeX, kSelectBackChirPosY+75,
		0xF4EADE, true);

	// 選択中の部分を四角で描画
	DrawBox(m_selectPos.x, m_selectPos.y, m_selectPos.x + kSelectSizeX,
		m_selectPos.y + kSelectSizeY, 0x00bfff, true);
	DrawExtendGraph(m_selectPos.x - 20, m_selectPos.y - 20,
		m_selectPos.x + kSelectSizeX + 20,
		m_selectPos.y + kSelectSizeY + 20,
		Cursor, true);

	DrawStringToHandle(kSelectChirPosX, kSelectChirPosY,
		"　ステージ1", 0x000000, m_pFontManager->GetFont());
	DrawStringToHandle(kSelectChirPosX, kSelectChirPosY + kCharInterval,
		"　ステージ2", 0x000000, m_pFontManager->GetFont());
	DrawStringToHandle(kSelectBackChirPosX, kSelectBackChirPosY, 
		"タイトルに戻る", 0x000000, m_pFontManager->GetFont());

	// 文字の点滅描画
	if (m_fadeLetter < 60){
		DrawGraph(kSelectChirPosX, kSelectChirPosY + kCharInterval * 2.8f, PushA, true);
	}

	// フェードの描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeAlpha);	// 半透明で表示開始
	DrawBox(0, 0, kScreenWidth, kScreenHeight, GetColor(255, 255, 255), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		// 不透明に戻しておく
}

void SceneStageSelect::BackDraw()
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

bool SceneStageSelect::IsSceneEnd() const
{
	return m_isSceneEnd && (m_fadeAlpha >= 255);
}