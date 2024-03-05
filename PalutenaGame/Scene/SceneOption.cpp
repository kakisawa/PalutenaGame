#include "SceneOption.h"
#include "SoundManager.h"
#include "ColorManager.h"
#include "FontManager.h"
#include "DxLib.h"
#include "Pad.h"
#include "Game.h"
#include <cassert>

namespace
{
	// 文字の表示位置
	constexpr float kSelectChirPosX = kScreenWidth * 0.28f;
	constexpr float kSelectChirPosY = kScreenHeight * 0.83f;

	// スクロール移動量
	constexpr float kBackGroundScale = 1.2f;
	// 背景の拡大率
	constexpr int kBgScale = 1;
}

SceneOption::SceneOption():
	m_scrollX(0),
	m_pushAGraph(-1),
	m_bgGraph(-1),
	m_isSceneEnd(false),
	m_fadeAlpha(255),
	m_fadeLetter(0)
{
	// メモリ確保
	m_pSoundManager = new SoundManager;
	// 色メモリ確保
	m_pColorManager = new ColorManager;
	// フォントメモリ
	m_pFontManager = new FontManager;
}

SceneOption::~SceneOption()
{
	// サウンドメモリ解放
	delete m_pSoundManager;
	m_pSoundManager = nullptr;
	// 色メモリ解放
	delete m_pColorManager;
	m_pColorManager = nullptr;
	delete m_pFontManager;
	m_pFontManager = nullptr;
}

void SceneOption::Init()
{
	m_pSoundManager->BGMExplanation();
	m_pSoundManager->Init();
	m_bgGraph = LoadGraph("data/Map/patter.png");
	m_pushAGraph = LoadGraph("data/PushA.png");		// 「Aボタンで決定」グラフ読み込み
	m_isSceneEnd = false;
	m_fadeAlpha = 255;
	m_fadeLetter = 0;
}

void SceneOption::Update()
{
	m_pSoundManager->ChangeSound();

	m_pSoundManager->SetBgmVolume();
	m_pSoundManager->SetSeVolume();

	if (m_pSoundManager->IsSceneEnd())
	{
		m_isSceneEnd = true;
	}

	// 背景スクロール
	m_scrollX += kBackGroundScale;
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

void SceneOption::Draw()
{
	BackDraw();

	DrawBoxAA(kScreenWidth * 0.1f-3, kScreenHeight * 0.1f-3,
		kScreenWidth * 0.9f+3, kScreenHeight * 0.8f+3,
		m_pColorManager->GetColorWhite(), true);
	DrawBoxAA(kScreenWidth * 0.1f, kScreenHeight * 0.1f, 
		kScreenWidth * 0.9f, kScreenHeight * 0.8f, 
		m_pColorManager->GetColorBlack(), true);

	m_pSoundManager->Draw();

	// 文字の点滅描画
	if (m_fadeLetter < 60) {
		DrawGraphF(kSelectChirPosX, kSelectChirPosY,
			m_pushAGraph, true);
	}

	// フェードの描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeAlpha);	// 半透明で表示開始
	DrawBox(0, 0, kScreenWidth, kScreenHeight,
		m_pColorManager->GetColorBlack(), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		// 不透明に戻しておく
}

void SceneOption::End()
{
	// 背景をメモリから削除
	DeleteGraph(m_graph);

	StopSoundMem(m_pSoundManager->m_bgmExplanation);
	m_pSoundManager->End();
}

void SceneOption::BackDraw()
{
	Size bg1Size;
	GetGraphSize(m_bgGraph, &bg1Size.m_width, &bg1Size.m_height);

	// スクロール量を計算
	int scrollBg = static_cast<int>(m_scrollX) % static_cast<int>(bg1Size.m_width * kBgScale);

	for (int index = 0; index < 4; index++)
	{
		DrawRotaGraph2(-scrollBg + index * bg1Size.m_width * kBgScale,
			kScreenHeight - bg1Size.m_height * kBgScale,
			0, 0,
			kBgScale, 0.0f,
			m_bgGraph, true);
	}
}

bool SceneOption::IsSceneEnd() const
{
	return m_isSceneEnd && (m_fadeAlpha >= 255);
}
