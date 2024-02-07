#include "SceneExplanation.h"
#include "SoundManager.h"
#include "DxLib.h"
#include "Pad.h"
#include "Game.h"
#include <cassert>

namespace
{
	// 文字の表示位置
	constexpr int kSelectChirPosX = kScreenWidth * 0.4;
	constexpr int kSelectChirPosY = kScreenHeight * 0.8;

	// スクロール移動量
	constexpr float backGround_scale = 1.2f;
	// 背景の拡大率
	constexpr int kBgScale = 1;
}

SceneExplanation::SceneExplanation():
	m_isSceneEnd(false),
	m_fadeAlpha(255)
{
	// メモリ確保
	m_pSoundManager = new SoundManager;
}

SceneExplanation::~SceneExplanation()
{
	delete m_pSoundManager;
	m_pSoundManager = nullptr;
}

void SceneExplanation::Init()
{
	//サウンドマネージャーの初期化
	m_pSoundManager->Init();

	m_pSoundManager->BGMExplanation();

	Graph = LoadGraph("data/Explanation.png");
	BgGraph = LoadGraph("data/Map/patter2.png");
	m_isSceneEnd = false;
	m_fadeAlpha = 255;
}

void SceneExplanation::Update()
{
	if (Pad::IsTrigger(PAD_INPUT_4))
	{
		m_isSceneEnd = true;

		m_pSoundManager->SoundButton();
	}

	// 背景スクロール
	m_scrollX += backGround_scale;

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

void SceneExplanation::Draw()
{
	BackDraw();
	DrawGraph(0, 0, Graph, true);

	SetFontSize(64);
	DrawString(kSelectChirPosX, kSelectChirPosY, "Aボタンでタイトルに戻る", 0xffffff);

	// フェードの描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeAlpha);	// 半透明で表示開始
	DrawBox(0, 0, kScreenWidth, kScreenHeight, GetColor(255, 255, 255), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		// 不透明に戻しておく
}

void SceneExplanation::BackDraw()
{
	Size bg1Size;
	GetGraphSize(BgGraph, &bg1Size.width, &bg1Size.height);

	// スクロール量を計算
	int scrollBg = static_cast<int>(m_scrollX) % static_cast<int>(bg1Size.width * kBgScale);

	for (int index = 0; index < 4; index++)
	{
		DrawRotaGraph2(-scrollBg + index * bg1Size.width * kBgScale,
			kScreenHeight - bg1Size.height * kBgScale,
			0, 0,
			kBgScale, 0.0f,
			BgGraph, true);
	}
}

void SceneExplanation::End()
{
	// 背景をメモリから削除
	DeleteGraph(Graph);

	StopSoundMem(m_pSoundManager->m_bgmExplanation);
	m_pSoundManager->End();
}

bool SceneExplanation::IsSceneEnd() const
{
	return m_isSceneEnd && (m_fadeAlpha >= 255);
}
