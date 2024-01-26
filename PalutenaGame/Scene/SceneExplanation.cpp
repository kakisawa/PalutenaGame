#include "SceneExplanation.h"
#include "DxLib.h"
#include "Pad.h"
#include "Game.h"

namespace
{
	// 文字の表示位置
	constexpr int kChirPosX = kScreenWidth * 0.4;
	constexpr int kChirPosY = kScreenHeight * 0.8;
}

SceneExplanation::SceneExplanation():
	m_isSceneEnd(false),
	m_fadeAlpha(255)
{
}

SceneExplanation::~SceneExplanation()
{
}

void SceneExplanation::Init()
{
	Graph = LoadGraph("data/Explanation.png");
	m_isSceneEnd = false;
	m_fadeAlpha = 255;
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
	}

	m_fadeAlpha -= 8;
	if (m_fadeAlpha < 0)
	{
		m_fadeAlpha = 0;
	}
}

void SceneExplanation::Draw()
{
	DrawGraph(0, 0, Graph, false);
	DrawString(120, 120, "ゲームクリア画面", GetColor(255, 255, 255));
	DrawString(120, 120 + 64, "Aキーを押してください", GetColor(255, 255, 255));

	// フェードの描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeAlpha);	// 半透明で表示開始
	DrawBox(0, 0, kScreenWidth, kScreenHeight, GetColor(255, 255, 255), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		// 不透明に戻しておく

	SetFontSize(64);

	DrawString(kChirPosX, kChirPosY, "Aボタンでタイトルに戻る", 0xffffff);
}

void SceneExplanation::End()
{
	// 背景をメモリから削除
	DeleteGraph(Graph);
}

bool SceneExplanation::IsSceneEnd() const
{
	return m_isSceneEnd;
}
