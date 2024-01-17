#include "SceneClear.h"
#include "Game.h"
#include "Pad.h"
#include "DxLib.h"

namespace
{
	// 文字表示位置
	constexpr int kCharPosX = Game::kScreenWidth / 2 - 20;
	constexpr int kCharPosY = Game::kScreenHeight / 2 + 70;
	// 文字間隔
	constexpr int kCharInterval = 50;

	// 選択中四角の初期位置
	constexpr int kInitSelectPosX = kCharPosX - 15;
	constexpr int kInitSelectPosY = kCharPosY - 10;
	// 選択中四角の移動量
	constexpr int kSelectmoveY = 50;
	// 四角の大きさ
	constexpr int kSelectSizeX = 80;
	constexpr int kSelectSizeY = 30;
}


SceneClear::SceneClear():
	m_select(kSelectStage),
	m_isSceneSelectStage(false)
{
}

SceneClear::~SceneClear()
{
}

void SceneClear::Init()
{
	m_isSceneSelectStage = false;
	m_select = kSelectStage;
	m_selectPos.x = kInitSelectPosX;
	m_selectPos.y = kInitSelectPosY;
}

void SceneClear::End()
{
}

void SceneClear::Update()
{
	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	// ↓キーを押したら選択状態を1つ下げる
	if (Pad::IsTrigger(pad & PAD_INPUT_DOWN))
	{
		m_select = (m_select + 1) % kSelectNum;
		m_selectPos.y += kSelectmoveY; // 選択中の四角を下に移動

		// 選択中の四角が一番下にだったら四角を一番上に戻す
		if (m_selectPos.y > kInitSelectPosY + kSelectmoveY * (kSelectNum - 1))
		{
			m_selectPos.y = kInitSelectPosY;
		}
	}
	// ↑キーを押したら選択状態を1つ上げる
	if (Pad::IsTrigger(pad & PAD_INPUT_UP))
	{
		m_select = (m_select + (kSelectNum - 1)) % kSelectNum;
		m_selectPos.y -= kSelectmoveY;	// 選択中の四角を上に移動

		if (m_selectPos.y < kInitSelectPosY)
		{
			m_selectPos.y = kInitSelectPosY + kSelectmoveY * (kSelectNum - 1);
		}
	}

	// Zキーを押したとき
	if (Pad::IsTrigger(PAD_INPUT_1))
	{
		// TODO:選択状態によって移動先を変える
		switch (m_select)
		{
		case kSelectStage:
			m_isSceneSelectStage = true;
			break;
		default:
			break;
		}
	}
}

void SceneClear::Draw()
{
	DrawString(8, 16, "クリア画面", 0xffffff, false);
	//DrawString(Game::kScreenWidth * 0.5f, Game::kScreenHeight * 0.5f, "Cキーでステージ選択", 0xffffff, false);
}
