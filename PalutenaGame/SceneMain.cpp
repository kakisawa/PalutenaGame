#include "DxLib.h"
#include "SceneMain.h"
#include "Back.h"
#include "Player.h"
#include "Game.h"
#include "Rect.h"
#include "Pad.h"

#include <cassert>

SceneMain::SceneMain()
{
	// ゲーム画面描画先の生成
	// 画面サイズと同じ大きさのグラフィックデータを作成する
	m_gameScreenHandle = MakeScreen(kScreenWidth, kScreenHeight, true);

	// グラフィックのロード
	m_playerHandle = LoadGraph("data/Player.png");
	assert(m_playerHandle != -1);
	m_enemyHandle = LoadGraph("data/Fairy.png");
	assert(m_enemyHandle != -1);
	m_backHandle = LoadGraph("data/Map/Back.png");
	assert(m_backHandle != -1);

	// プレイヤーのメモリ確保
	m_pPlayer = new Player{ this };
	m_pPlayer->SetHandle(m_playerHandle);	// Playerにグラフィックのハンドルを渡す

	// 背景のメモリ確保
	m_pBack = new Back;
	m_pBack->SetHandle(m_backHandle);
}

SceneMain::~SceneMain()
{
	// MakeScreenで作成したらグラフィックを削除する
	DeleteGraph(m_gameScreenHandle);

	// メモリからグラフィックを削除
	DeleteGraph(m_playerHandle);
	DeleteGraph(m_enemyHandle);
	DeleteGraph(m_backHandle);

	// メモリの解放
	delete m_pPlayer;
	m_pPlayer = nullptr;

	delete m_pBack;
	m_pBack = nullptr;
}

void SceneMain::Init()
{
	assert(m_pPlayer);	// m_pPlayer == nullptr	の場合止まる

	m_pPlayer->Init();
	m_pBack->Init();
}

void SceneMain::End()
{
}

void SceneMain::Update()
{
	Pad::Update();

	m_pBack->Update();
	m_pPlayer->Update();
}

void SceneMain::Draw()
{
	// 自分で生成したグラフィックデータに対して書き込みを行う
	SetDrawScreen(m_gameScreenHandle);

	// 描画先スクリーンをクリアする
	ClearDrawScreen();

	m_pBack->Draw();
	m_pPlayer->Draw();

	// バックバッファに書き込む設定に戻しておく
	SetDrawScreen(DX_SCREEN_BACK);

	DrawGraph(0, 0, m_gameScreenHandle, true);
}
