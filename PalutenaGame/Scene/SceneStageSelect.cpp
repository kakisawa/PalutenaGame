#include "SceneStageSelect.h"
#include "SoundManager.h"
#include "FontManager.h"
#include "ColorManager.h"
#include "DxLib.h"
#include "Game.h"
#include "Pad.h"

namespace
{
	// 文字の表示位置
	constexpr int kSelectChirPosX = kScreenWidth * 0.08f;
	constexpr int kSelectChirPosY = kScreenHeight * 0.25f;

	constexpr int kSelectBackChirPosX = kScreenWidth * 0.43f;
	constexpr int kSelectBackChirPosY = kScreenHeight * 0.85f;

	// 文字の表示幅
	constexpr int kCharInterval = 300;

	// 文字を囲む四角の初期位置
	constexpr int kSelectPosX = kSelectChirPosX - 2;
	constexpr int kSelectPosY = kSelectChirPosY - 2;

	// 文字を囲む四角の移動量
	constexpr int kSelectMoveY = 300;

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
	// 色メモリ確保
	m_pColorManager = new ColorManager;
}

SceneStageSelect::~SceneStageSelect()
{
	// メモリ解放
	delete m_pSoundManager;
	m_pSoundManager = nullptr;
	delete m_pFontManager;
	m_pFontManager = nullptr;
	delete m_pColorManager;
	m_pColorManager = nullptr;
}

void SceneStageSelect::Init()
{
	Graph = LoadGraph("data/Map/patter.png");	// 背景読み込み
	Cursor = LoadGraph("data/Cursor.png");		// カーソルロゴ読み込み
	PushA = LoadGraph("data/PushA.png");				// 「Aボタンで決定」グラフ読み込み
	ExplanationGraph = LoadGraph("data/Explanation.png");
	SelectUI= LoadGraph("data/SelectUI.png");
	SelectUI2=LoadGraph("data/SelectUI2.png");

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
	m_pSoundManager->SetBgmVolume();
	m_pSoundManager->SetSeVolume();

	// ↓キーを押したら選択状態を一つ下げる
	if (Pad::IsTrigger(PAD_INPUT_DOWN))
	{
		m_pSoundManager->SoundSelect();

		m_select = (m_select + 1) % kSclectNum;

		// 選択中の四角が一番下だったら四角を一番上に戻す
		if (m_selectPos.y >= kSelectBackChirPosY){
			m_selectPos.x = kSelectPosX;
			m_selectPos.y = kSelectPosY;
			return;
		}
		if (m_selectPos.y == kSelectPosY) {
			m_selectPos.y += kSelectMoveY;
		}
		else if(m_selectPos.y == kSelectPosY + (kCharInterval * 1)){
			m_selectPos.x = kSelectBackChirPosX;
			m_selectPos.y = kSelectBackChirPosY;
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
			m_selectPos.x = kSelectBackChirPosX;
			m_selectPos.y = kSelectBackChirPosY;
			m_select = kBackTitle;
			return;
		}

		if (m_selectPos.y == kSelectPosY + (kCharInterval * 1)) {
			m_selectPos.y -= kSelectMoveY;
		}
		else if (m_selectPos.y == kSelectBackChirPosY)
		{
			m_selectPos.x = kSelectPosX;
			m_selectPos.y = kSelectPosY + (kCharInterval * 1);
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
			/*m_isSceneEnd = true;
			isStage2 = true;
			break;*/
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
	DeleteGraph(ExplanationGraph);

	m_pSoundManager->End();
}

void SceneStageSelect::StringDraw()
{
	// ステージセレクト・タイトルに戻るBox
	for (int i = 0; i < 2; i++)
	{
		DrawGraph(kSelectPosX, kSelectPosY + (kCharInterval * i),
			SelectUI, false);
		DrawGraph(kSelectBackChirPosX, kSelectBackChirPosY,
			SelectUI, false);
	}

	// 選択中のBox・カーソル描画
	DrawGraph(m_selectPos.x, m_selectPos.y,
		SelectUI2, false);
	DrawExtendGraph(m_selectPos.x - 20, m_selectPos.y - 20,
		m_selectPos.x + kSelectSizeX + 20,
		m_selectPos.y + kSelectSizeY + 20,
		Cursor, true);

	DrawStringToHandle(kSelectChirPosX, kSelectChirPosY,
		"　   ステージ1", m_pColorManager->GetColorBlack(),
		m_pFontManager->GetFont());
	DrawStringToHandle(kSelectChirPosX, kSelectChirPosY + kCharInterval,
		"   ComingSoon", m_pColorManager->GetColorBlack(), 
		m_pFontManager->GetFont());
	DrawStringToHandle(kSelectBackChirPosX, kSelectBackChirPosY, 
		"  タイトルに戻る", m_pColorManager->GetColorBlack(),
		m_pFontManager->GetFont());

	// 文字の点滅描画
	if (m_fadeLetter < 60)
	{
		DrawGraph(kSelectChirPosX, kSelectBackChirPosY,
			PushA, true);
	}

	// フェードの描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeAlpha);	// 半透明で表示開始
	DrawBox(0, 0, kScreenWidth, kScreenHeight, 
		m_pColorManager->GetColorBlack(), true);
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

	DrawGraph(700, 100, ExplanationGraph, true);
}

bool SceneStageSelect::IsSceneEnd() const
{
	return m_isSceneEnd && (m_fadeAlpha >= 255);
}