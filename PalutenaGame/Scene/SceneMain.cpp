#include "DxLib.h"
#include "SceneMain.h"
#include "Player.h"
#include "MozueyeEnemy.h"
#include "DeathYourEnemy.h"
#include "PumpkinEnemy.h"
#include "Back.h"
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

	m_mozueyeEnemy = LoadGraph("data/Fairy.png");
	assert(m_mozueyeEnemy != -1);
	m_deathYourEnemyGraph = LoadGraph("data/Fairy2.png");
	assert(m_deathYourEnemyGraph != -1);
	m_pumpkinEnemyGraph = LoadGraph("data/Fairy3.png");
	assert(m_pumpkinEnemyGraph != -1);


	// プレイヤーのメモリ確保
	m_pPlayer = new Player{ this };
	m_pPlayer->SetHandle(m_playerHandle);	// Playerにグラフィックのハンドルを渡す

	// 背景のメモリ確保
	m_pBack = new Back;
	m_pBack->SetHandle(m_backHandle);

	// 敵のメモリ確保
	m_pMozueyeEnemy = new MozueyeEnemy;
	m_pMozueyeEnemy->SetHandle(m_mozueyeEnemy);
	m_pDeathYourEnemy = new DeathYourEnemy;
	m_pDeathYourEnemy->SetHandle(m_deathYourEnemyGraph);
	m_pPumpkinEnemy = new PumpkinEnemy;
	m_pPumpkinEnemy->SetHandle(m_pumpkinEnemyGraph);


}

SceneMain::~SceneMain()
{
	// MakeScreenで作成したらグラフィックを削除する
	DeleteGraph(m_gameScreenHandle);

	// メモリからグラフィックを削除
	DeleteGraph(m_playerHandle);
	DeleteGraph(m_enemyHandle);
	DeleteGraph(m_backHandle);

	DeleteGraph(m_mozueyeEnemy);
	DeleteGraph(m_deathYourEnemyGraph);
	DeleteGraph(m_pumpkinEnemyGraph);

	// メモリの解放
	delete m_pPlayer;
	m_pPlayer = nullptr;

	delete m_pBack;
	m_pBack = nullptr;

	delete m_pMozueyeEnemy;
	m_pMozueyeEnemy = nullptr;
	delete m_pDeathYourEnemy;
	m_pDeathYourEnemy = nullptr;
	delete m_pPumpkinEnemy;
	m_pPumpkinEnemy = nullptr;
}

void SceneMain::Init()
{
	assert(m_pPlayer);	// m_pPlayer == nullptr	の場合止まる

	m_pPlayer->Init();
	m_pBack->Init();

	m_pMozueyeEnemy->Init();
	m_pDeathYourEnemy->Init();
	m_pPumpkinEnemy->Init();
}

void SceneMain::Update()
{
	Pad::Update();

	m_pBack->Update();
	m_pPlayer->Update();

	m_pMozueyeEnemy->Update();
	m_pDeathYourEnemy->Update();
	m_pPumpkinEnemy->Update();

}

void SceneMain::Draw()
{
	// 自分で生成したグラフィックデータに対して書き込みを行う
	SetDrawScreen(m_gameScreenHandle);

	// 描画先スクリーンをクリアする
	ClearDrawScreen();

	m_pBack->Draw();
	m_pPlayer->Draw();

	m_pMozueyeEnemy->Draw();
	m_pDeathYourEnemy->Draw();
	m_pPumpkinEnemy->Draw();

	// バックバッファに書き込む設定に戻しておく
	SetDrawScreen(DX_SCREEN_BACK);

	DrawGraph(0, 0, m_gameScreenHandle, true);
}

void SceneMain::End()
{
}

bool SceneMain::IsSceneEnd() const
{
	
}
