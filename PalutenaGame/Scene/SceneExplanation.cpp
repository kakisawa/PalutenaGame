#include "SceneExplanation.h"
#include "SoundManager.h"
#include "DxLib.h"
#include "Pad.h"
#include "Game.h"

namespace
{
	// 文字の表示位置
	constexpr int kChirPosX = kScreenWidth * 0.4;
	constexpr int kChirPosY = kScreenHeight * 0.8;

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
	// メモリ解放
	delete m_pSoundManager;
	m_pSoundManager = nullptr;
}

void SceneExplanation::Init()
{
	Graph = LoadGraph("data/Explanation.png");
	BgGraph = LoadGraph("data/Map/patter2.png");
	m_isSceneEnd = false;
	m_fadeAlpha = 255;

	//サウンドマネージャーの初期化
	m_pSoundManager->Init();
}

void SceneExplanation::Update()
{
	if (Pad::IsTrigger(PAD_INPUT_4))
	{
		m_isSceneEnd = true;

		m_fadeAlpha += 8;
		if (m_fadeAlpha > 255)
		{
			m_fadeAlpha = 255;
		}

		m_pSoundManager->SoundButton();
	}

	// 背景スクロール
	m_scrollX += backGround_scale;

	m_fadeAlpha -= 8;
	if (m_fadeAlpha < 0)
	{
		m_fadeAlpha = 0;
	}
}

void SceneExplanation::Draw()
{
	BackDraw();
	DrawGraph(0, 0, Graph, false);

	SetFontSize(64);
	DrawString(kChirPosX, kChirPosY, "Aボタンでタイトルに戻る", 0xffffff);

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

	m_pSoundManager->End();
}

bool SceneExplanation::IsSceneEnd() const
{
	return m_isSceneEnd;
}
