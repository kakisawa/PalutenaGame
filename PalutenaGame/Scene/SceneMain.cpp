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

SceneMain::SceneMain() :
	m_isSceneEnd(false),
	m_fadeAlpha(255)		// 不透明で初期化
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

	// 敵のメモリ確保
	for (int i = 0; i < MozuMax; i++)
	{
		m_pMozueyeEnemy[i] = new MozueyeEnemy;
	}
	for (int i = 0; i < DeathMax; i++)
	{
		m_pDeathYourEnemy[i] = new DeathYourEnemy;
	}
	for (int i = 0; i < PumpMax; i++)
	{
		m_pPumpkinEnemy[i] = new PumpkinEnemy;
	}
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
	for (int i = 0; i < MozuMax; i++)
	{
		delete m_pMozueyeEnemy;
		m_pMozueyeEnemy[i] = nullptr;
	}

	for (int i = 0; i < DeathMax; i++)
	{
		delete m_pDeathYourEnemy;
		m_pDeathYourEnemy[i] = nullptr;
	}

	for (int i = 0; i < PumpMax; i++)
	{
		delete m_pPumpkinEnemy;
		m_pPumpkinEnemy[i] = nullptr;
	}
}

void SceneMain::Init()
{
	assert(m_pPlayer);	// m_pPlayer == nullptr	の場合止まる

	m_isSceneEnd = false;

	m_pPlayer->Init();
	m_pBack->Init();

	for (int i = 0; i < MozuMax; i++)
	{
		m_pMozueyeEnemy[i]->Init();
	}
	for (int i = 0; i < DeathMax; i++)
	{
		m_pDeathYourEnemy[i]->Init();
	}
	for (int i = 0; i < PumpMax; i++)
	{
		m_pPumpkinEnemy[i]->Init();
	}

	m_fadeAlpha = 255;
}

void SceneMain::Update()
{
	if (m_pPlayer->PlayerDeath())
	{
		// Aボタンが押されたらゲームオーバー画面へ遷移する
		if (Pad::IsTrigger(PAD_INPUT_4))	  // Aボタンが押された
		{
			m_isSceneEnd = true;

			// フェードアウト
			m_fadeAlpha += 8;
			if (m_fadeAlpha < 255)
			{
				m_fadeAlpha = 255;
			}
		}
		m_pPlayer->Update();
		m_pPlayer->Death();
		Death();

		return;
	}

	// フェードイン
	m_fadeAlpha -= 8;
	if (m_fadeAlpha < 0)
	{
		m_fadeAlpha = 0;
	}

	m_pBack->Update();
	m_pPlayer->Update();

	Rect playerRect = m_pPlayer->GetColRect();
	for (int i = 0; i < MozuMax; i++)
	{
		m_pMozueyeEnemy[i]->Update();

		// 存在している敵とプレイヤーの当たり判定
		Rect enemyRect = m_pMozueyeEnemy[i]->GetColRect();
		if (playerRect.IsCollsion(enemyRect))
		{
			m_pPlayer->OnDamage_Mozu();
		}
	}

	for (int i = 0; i < DeathMax; i++)
	{
		m_pDeathYourEnemy[i]->Update();

		// 存在している敵とプレイヤーの当たり判定
		Rect enemyRect = m_pDeathYourEnemy[i]->GetColRect();
		if (playerRect.IsCollsion(enemyRect))
		{
			m_pPlayer->OnDamage_Death();
		}
	}
	for (int i = 0; i < PumpMax; i++)
	{
		m_pPumpkinEnemy[i]->Update();

		// 存在している敵とプレイヤーの当たり判定
		Rect enemyRect = m_pPumpkinEnemy[i]->GetColRect();
		if (playerRect.IsCollsion(enemyRect))
		{
			m_pPlayer->OnDamage_Pump();
		}
	}
}

void SceneMain::Draw()
{
	//// 自分で生成したグラフィックデータに対して書き込みを行う
	//SetDrawScreen(m_gameScreenHandle);

	//// 描画先スクリーンをクリアする
	//ClearDrawScreen();

	m_pBack->Draw();
	m_pPlayer->Draw();
	m_pPlayer->Death();

	for (int i = 0; i < MozuMax; i++)
	{
		m_pMozueyeEnemy[i]->EnemyBase::Draw();
	}
	for (int i = 0; i < DeathMax; i++)
	{
		m_pDeathYourEnemy[i]->EnemyBase::Draw();
	}
	for (int i = 0; i < PumpMax; i++)
	{
		m_pPumpkinEnemy[i]->EnemyBase::Draw();
	}

	DrawGraph(0, 0, m_gameScreenHandle, true);

	// バックバッファに書き込む設定に戻しておく
	//SetDrawScreen(DX_SCREEN_BACK);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeAlpha);	// 半透明で表示開始
	DrawBox(0, 0, kScreenWidth, kScreenHeight, GetColor(255, 255, 255), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		// 不透明に戻しておく
}

void SceneMain::Death()
{
	SetDrawBlendMode(DX_BLENDMODE_PMA_ALPHA, 128);

	SetFontSize(32);
	DrawString(kScreenWidth * 0.5 - 100, kScreenHeight * 0.5 - 100, "死んじゃった...", GetColor(255, 255, 255));
	SetFontSize(16);
	DrawString(kScreenWidth * 0.5 - 80, kScreenHeight * 0.5 - 65, "Aキーを押してください", GetColor(255, 255, 255));
}

void SceneMain::End()
{
}

bool SceneMain::IsSceneEnd() const
{
	return m_isSceneEnd && (m_fadeAlpha >= 255);
}
