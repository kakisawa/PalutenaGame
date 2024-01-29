#include "DxLib.h"
#include "SceneMain.h"
#include "Player.h"
#include "MozueyeEnemy.h"
#include "DeathYourEnemy.h"
#include "PumpkinEnemy.h"
#include "Shot/Shot.h"
#include "Time.h"
#include "Back.h"
#include "Game.h"
#include "Rect.h"
#include "Pad.h"

#include <cassert>

SceneMain::SceneMain() :
	m_isSceneEnd(false),
	isFinishStage1(false),
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

	// 制限時間のメモリ確保
	m_pTime = new Time;

	m_pMozueyeEnemy.resize(MozuMax);
	m_pDeathYourEnemy.resize(DeathMax);
	m_pPumpkinEnemy.resize(PumpMax);

	// 初期状態ではメモリを確保していないことが分かるようにしておく
	// 未使用状態にする nullptrを入れておく
	for (int i = 0; i < m_pMozueyeEnemy.size(); i++)
	{
		m_pMozueyeEnemy[i] = nullptr;
	}
	for (int i = 0; i < m_pDeathYourEnemy.size(); i++)
	{
		m_pDeathYourEnemy[i] = nullptr;
	}
	for (int i = 0; i < m_pPumpkinEnemy.size(); i++)
	{
		m_pPumpkinEnemy[i] = nullptr;
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

	delete m_pTime;
	m_pTime = nullptr;

	for (int i = 0; i < m_pMozueyeEnemy.size(); i++)
	{
		if (m_pMozueyeEnemy[i] != nullptr)
		{
			delete m_pMozueyeEnemy[i];
			m_pMozueyeEnemy[i] = nullptr;
		}
	}
	for (int i = 0; i < m_pDeathYourEnemy.size(); i++)
	{
		if (m_pDeathYourEnemy[i] != nullptr)
		{
			delete m_pDeathYourEnemy[i];
			m_pDeathYourEnemy[i] = nullptr;
		}
	}
	for (int i = 0; i < m_pPumpkinEnemy.size(); i++)
	{
		if (m_pPumpkinEnemy[i] != nullptr)
		{
			delete m_pPumpkinEnemy[i];
			m_pPumpkinEnemy[i] = nullptr;
		}
	}
}

void SceneMain::Init()
{
	assert(m_pPlayer);	// m_pPlayer == nullptr	の場合止まる

	m_isSceneEnd = false;
	isFinishStage1 = false;

	m_pPlayer->Init();
	m_pBack->Init();
	m_pTime->Init();

	CreateEnemyDeath();
	CreateEnemyPump();
	CreateEnemyMozu();

	m_fadeAlpha = 255;
}

void SceneMain::Update()
{
	// プレイヤーが死亡したら(ゲームオーバー)
	if (m_pPlayer->PlayerDeath())
	{
		// Aボタンが押されたらゲームオーバー画面へ遷移する
		if (Pad::IsTrigger(PAD_INPUT_4))	  // Aボタンが押された
		{
			isFinishStage1 = true;
			m_isSceneEnd = true;
			isToGameOver = true;

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

	// 制限時間が終わったら(ゲームクリア)
	if (m_pTime->TimeUp())
	{
		// Aボタンが押されたらゲームオーバー画面へ遷移する
		if (Pad::IsTrigger(PAD_INPUT_4))	  // Aボタンが押された
		{
			isFinishStage1 = true;
			m_isSceneEnd = true;
			isToGameClear = true;

			// フェードアウト
			m_fadeAlpha += 8;
			if (m_fadeAlpha < 255)
			{
				m_fadeAlpha = 255;
			}
		}
		Clear();
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
	m_pTime->Update();

	// 弾との当たり判定
	for (int j = 0; j < kShotMax; j++)
	{
		// nullptrなら処理は行わない
		if (!m_pShot[j])	continue;

		m_pShot[j]->Update();
		// 画面外に出たらメモリ解放
		if (!m_pShot[j]->IsExist())
		{
			delete m_pShot[j];
			m_pShot[j] = nullptr;
		}
	}

	Rect playerRect = m_pPlayer->GetColRect();
	for (int i = 0; i < m_pMozueyeEnemy.size(); i++)
	{
		if (m_pMozueyeEnemy[i])
		{
			m_pMozueyeEnemy[i]->Update();
			m_pPlayer->SetMozu(m_pMozueyeEnemy[i]);

			// 存在している敵とプレイヤーの当たり判定
			if (m_pMozueyeEnemy[i]->isExist()) {
				Rect enemyRect = m_pMozueyeEnemy[i]->GetColRect();
				if (playerRect.IsCollsion(enemyRect))
				{
					m_pPlayer->OnDamage_Mozu();
					m_pMozueyeEnemy[i]->OnDamage();
				}

				// 弾との当たり判定
				for (int shotIndex = 0; shotIndex < kShotMax; shotIndex++)
				{
					// nullptrなら処理は行わない
					if (!m_pShot[shotIndex])	continue;

					if (m_pShot[shotIndex]->IsExist()) {
						// 存在している敵との当たり判定
						Rect shotRect = m_pShot[shotIndex]->GetColRect();
						if (shotRect.IsCollsion(enemyRect))
						{
							m_pMozueyeEnemy[i]->OnDamage();
							m_pShot[shotIndex]->colShot();
						}
					}
				}
			}
		}
	}

	for (int i = 0; i < m_pDeathYourEnemy.size(); i++)
	{
		if (m_pDeathYourEnemy[i])
		{
			m_pDeathYourEnemy[i]->Update();
			m_pPlayer->SetDeath(m_pDeathYourEnemy[i]);

			// 存在している敵とプレイヤーの当たり判定
			if (m_pDeathYourEnemy[i]->isExist()) {
				Rect enemyRect = m_pDeathYourEnemy[i]->GetColRect();
				if (playerRect.IsCollsion(enemyRect))
				{
					m_pPlayer->OnDamage_Death();
					m_pDeathYourEnemy[i]->OnDamage();
				}

				// 弾との当たり判定
				for (int shotIndex = 0; shotIndex < kShotMax; shotIndex++)
				{
					// nullptrなら処理は行わない
					if (!m_pShot[shotIndex])	continue;

					if (m_pShot[shotIndex]->IsExist()) {
						// 存在している敵との当たり判定
						Rect shotRect = m_pShot[shotIndex]->GetColRect();
						if (shotRect.IsCollsion(enemyRect))
						{
							m_pDeathYourEnemy[i]->OnDamage();
							m_pShot[shotIndex]->colShot();
						}
					}
				}
			}
		}
	}
	for (int i = 0; i < m_pPumpkinEnemy.size(); i++)
	{
		if (m_pPumpkinEnemy[i])
		{
			m_pPumpkinEnemy[i]->SetPlayer(m_pPlayer);

			m_pPumpkinEnemy[i]->Update();
			m_pPlayer->SetPump(m_pPumpkinEnemy[i]);

			// 存在している敵とプレイヤーの当たり判定
			if (m_pPumpkinEnemy[i]->isExist()) {
				Rect enemyRect = m_pPumpkinEnemy[i]->GetColRect();
				if (playerRect.IsCollsion(enemyRect))
				{
					m_pPlayer->OnDamage_Pump();
					m_pPumpkinEnemy[i]->OnDamage();
				}

				// 弾との当たり判定
				for (int shotIndex = 0; shotIndex < kShotMax; shotIndex++)
				{
					// nullptrなら処理は行わない
					if (!m_pShot[shotIndex])	continue;

					if (m_pShot[shotIndex]->IsExist()) {
						// 存在している敵との当たり判定
						Rect shotRect = m_pShot[shotIndex]->GetColRect();
						if (shotRect.IsCollsion(enemyRect))
						{
							m_pPumpkinEnemy[i]->OnDamage();
							m_pShot[shotIndex]->colShot();
						}
					}
				}
			}
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
	m_pTime->Draw();

	for (int i = 0; i < m_pMozueyeEnemy.size(); i++)
	{
		if (m_pMozueyeEnemy[i]) {
			m_pMozueyeEnemy[i]->Draw();
		}
	}
	for (int i = 0; i < m_pDeathYourEnemy.size(); i++)
	{
		if (m_pDeathYourEnemy[i])
		{
			m_pDeathYourEnemy[i]->Draw();
		}
	}
	for (int i = 0; i < m_pPumpkinEnemy.size(); i++)
	{
		if (m_pPumpkinEnemy[i])
		{
			m_pPumpkinEnemy[i]->Draw();
		}
	}

	// 弾描画
	for (int i = 0; i < kShotMax; i++)
	{
		// nullptrかどうかをチェックする
		if (!m_pShot[i])	continue;// nullptrなら以降の処理は行わない
		m_pShot[i]->Draw();
	}

	DrawGraph(0, 0, m_gameScreenHandle, true);

	// バックバッファに書き込む設定に戻しておく
	//SetDrawScreen(DX_SCREEN_BACK);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeAlpha);	// 半透明で表示開始
	DrawBox(0, 0, kScreenWidth, kScreenHeight, GetColor(255, 255, 255), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		// 不透明に戻しておく
}

void SceneMain::Clear()
{
	SetDrawBlendMode(DX_BLENDMODE_PMA_ALPHA, 128);

	SetFontSize(32);
	DrawString(kScreenWidth * 0.5 - 100, kScreenHeight * 0.5 - 100, "ゲームクリア！！！", GetColor(255, 255, 255));
	SetFontSize(16);
	DrawString(kScreenWidth * 0.5 - 80, kScreenHeight * 0.5 - 65, "Aキーを押してください", GetColor(255, 255, 255));
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
	// 弾との当たり判定
	for (int j = 0; j < kShotMax; j++)
	{
		delete m_pShot[j];
		m_pShot[j] = nullptr;

	}

	// エネミーの解放
	for (int i = 0; i < m_pMozueyeEnemy.size(); i++)
	{
		if (m_pMozueyeEnemy[i] != nullptr)
		{
			delete m_pMozueyeEnemy[i];
			m_pMozueyeEnemy[i] = nullptr;
		}
	}
	for (int i = 0; i < m_pDeathYourEnemy.size(); i++)
	{
		if (m_pDeathYourEnemy[i] != nullptr)
		{
			delete m_pDeathYourEnemy[i];
			m_pDeathYourEnemy[i] = nullptr;
		}
	}
	for (int i = 0; i < m_pPumpkinEnemy.size(); i++)
	{
		if (m_pPumpkinEnemy[i] != nullptr)
		{
			delete m_pPumpkinEnemy[i];
			m_pPumpkinEnemy[i] = nullptr;
		}
	}
}

bool SceneMain::IsSceneEnd() const
{
	return m_isSceneEnd && (m_fadeAlpha >= 255);
}

bool SceneMain::ToGameOver() const
{
	return isToGameOver;
}

bool SceneMain::ToGameClear() const
{
	return isToGameClear;
}

bool SceneMain::AddShot(Shot* pShot)
{
	// nullptrを渡されたら止まる
	assert(pShot);

	for (int i = 0; i < kShotMax; i++)
	{
		// 使用中なら次のチェックへ
		if (m_pShot[i])	continue;

		// ここに来たということはm_pShot[i] == nullptr
		m_pShot[i] = pShot;
		// 登録したら終了
		return true;
	}

	// ここに来た、という事はm_pShotにポインタを登録できなかった
	delete pShot;
	return false;
}

void SceneMain::CreateEnemyMozu()
{
	// 敵のメモリ確保
	for (int i = 0; i < m_pMozueyeEnemy.size(); i++)
	{
		if (!m_pMozueyeEnemy[i])	// nullptrであることをチェック
		{
			m_pMozueyeEnemy[i] = new MozueyeEnemy;
			m_pMozueyeEnemy[i]->Init();
			m_pMozueyeEnemy[i]->Start(kScreenWidth * 0.3, Ground - 32 * 0.5);
			return;
		}
	}
}

void SceneMain::CreateEnemyDeath()
{
	for (int i = 0; i < m_pDeathYourEnemy.size(); i++)
	{
		if (!m_pDeathYourEnemy[i])	// nullptrであることをチェック
		{
			m_pDeathYourEnemy[i] = new DeathYourEnemy;
			m_pDeathYourEnemy[i]->Init();
			m_pDeathYourEnemy[i]->Start(kScreenWidth * 0.5, Ground - 46 * 0.5);
			return;
		}
	}
}

void SceneMain::CreateEnemyPump()
{
	for (int i = 0; i < m_pPumpkinEnemy.size(); i++)
	{
		m_pPumpkinEnemy[i] = new PumpkinEnemy;
		m_pPumpkinEnemy[i]->Init();
		m_pPumpkinEnemy[i]->Start(kScreenWidth * 0.5, Ground - 22 * 0.5);
		return;
	}
}