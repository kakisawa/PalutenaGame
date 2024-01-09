#include "SceneResult.h"
#include "DxLib.h"
#include "Game.h"

SceneResult::SceneResult() :
	m_gameoverHandle(-1),
	m_isSceneEnd(false)
{
}

SceneResult::~SceneResult()
{
}

void SceneResult::Init()
{
	m_gameoverHandle = LoadGraph("data/GameOver2.jpg");

	// 変数の初期化
	m_isSceneEnd = false;

}

void SceneResult::Update()
{	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if (pad & PAD_INPUT_2)	// パッドの2ボタン or キーボードのZキー
	{
		// タイトル画面を終了してSceneMainに移動する処理を書きたい!
		m_isSceneEnd = true;
	}
}

void SceneResult::Draw()
{
	int width = 0;
	int height = 0;
	GetGraphSize(m_gameoverHandle, &width, &height);

	DrawGraph(Game::kScreenWidth / 2 -width / 2,
			  Game::kScreenHeight / 2 - height / 2,
			  m_gameoverHandle, false);

	DrawString(500, 600, "2ボタンを押してください", GetColor(255, 255, 255));
}

void SceneResult::End()
{
	DeleteGraph(m_gameoverHandle);

}
