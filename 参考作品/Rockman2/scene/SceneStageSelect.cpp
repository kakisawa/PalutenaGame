#include "SceneStageSelect.h"
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
	constexpr int kInitSelectPosX = kCharPosX - 20;
	constexpr int kInitSelectPosY = kCharPosY - 10;
	// 選択中四角の移動量
	constexpr int kSelectmoveY = 50;
	// 四角の大きさ
	constexpr int kSelectSizeX = 90;
	constexpr int kSelectSizeY = 30;
}

SceneStageSelect::SceneStageSelect() :
	m_select(kStage1),
	m_isSceneEnd(false),
	m_logoHandle(-1),
	m_selectPos(kInitSelectPosX, kInitSelectPosY)
{
	m_logoHandle = LoadGraph("data/image/Logo/TitleLogo.png");
}

SceneStageSelect::~SceneStageSelect()
{
}

void SceneStageSelect::Init()
{
	m_isSceneEnd = false;
	m_select = kStage1;
	m_selectPos.x = kInitSelectPosX;
	m_selectPos.y = kInitSelectPosY;
}

void SceneStageSelect::Update()
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
		case kStage1:
			m_isSceneEnd = true;
			break;
		case kStage2:
			break;
		case kStage3:
			break;
		case kBackTitle:
			break;
		default:
			break;
		}
	}
}

void SceneStageSelect::Draw()
{
	// ロゴ表示
	DrawRotaGraph(Game::kScreenWidth / 2, Game::kScreenHeight / 4, 0.8f, 0.0f, m_logoHandle, true);

	// TODO:文字サイズ、フォント変更
	DrawString(8, 16, "ステージ選択画面", 0xffffff, false);
	DrawString(kCharPosX, kCharPosY, "STAGE1", 0xffffff);
	DrawString(kCharPosX, kCharPosY + kCharInterval, "STAGE2", 0xffffff);
	DrawString(kCharPosX, kCharPosY + kCharInterval * 2, "STAGE3", 0xffffff);
	DrawString(kCharPosX - 15, kCharPosY + kCharInterval * 3, "BACKTITLE", 0xffffff);

	// 選択中の部分を四角で描画
	DrawBox(m_selectPos.x, m_selectPos.y, m_selectPos.x + kSelectSizeX, m_selectPos.y + kSelectSizeY, 0x00bfff, false);
}

void SceneStageSelect::End()
{
}
