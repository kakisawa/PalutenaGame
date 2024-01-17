#include "SceneGameOver.h"
#include "DxLib.h"
#include "Game.h"
#include "Pad.h"

SceneGameOver::SceneGameOver():
	m_isSceneSelect(false)
{
}

SceneGameOver::~SceneGameOver()
{
}

void SceneGameOver::Init()
{
	m_isSceneSelect = false;
}

void SceneGameOver::Update()
{
	if (Pad::IsTrigger(PAD_INPUT_3)) // Cキーを押したとき
	{
		// ステージ選択画面に移動する
		m_isSceneSelect = true;
	}
}

void SceneGameOver::Draw()
{
	DrawString(Game::kScreenWidth / 2 - 30, Game::kScreenHeight / 2 - 30, "ゲームオーバー", 0xff0000);
	DrawString(Game::kScreenWidth / 2, Game::kScreenHeight / 2, "Press C", 0xff0000);
}

void SceneGameOver::End()
{
}

