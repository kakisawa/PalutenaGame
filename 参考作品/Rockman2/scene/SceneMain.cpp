#include "SceneMain.h"
#include "DxLib.h"
#include "Pad.h"
#include "Rect.h"
#include "Game.h"
#include "Bg.h"
#include "ScenePause.h"

#include "RecoverySmallHp.h"
#include "RecoveryGreatHp.h"
#include "RecoverySmallShot.h"
#include "RecoveryGreatShot.h"
#include "RecoveryLife.h"
#include "RecoveryFullHp.h"

#include "Player.h"

#include "ShotBase.h"

#include "Matasaburo.h"
#include <cassert>

namespace
{
	// 画面内に1度に出せる弾数
	constexpr int kShotMax = 3;
	// 1度に登場できる敵数
	constexpr int kEnemyMax = 20;
	// 画面内に1度に出せる回復アイテム数
	constexpr int kRecoveryMax = 50;

	// プレイヤーの画像サイズ
	constexpr int kPlayerWidth = 32;
	constexpr int kPlayerHeight = 64;

	// マップチップのサイズ
	constexpr int kMapChipWidth = 32;
	constexpr int kMapChipHeight = 32;

	// ポーズ画面の文字表示位置
	constexpr int kTextPosX = 510;
	// バーの表示位置
	constexpr int kBarPosX = 540;
	// バーの表示間隔
	constexpr int kBarInterval = 8;

	// バーの四角のサイズ
	constexpr int kBarWidth = 5;
	constexpr int kBarHeight = 20;

	// Y座標の表示位置の間隔
	constexpr int kInterval = 60;
	// 文字、バーの表示位置
	constexpr int kDisPosY = 200;
}

SceneMain::SceneMain():
	m_drawValue(0),
	m_isGetFullHpRecovery(false),
	m_isExistLineMove(false),
	m_isSceneGameOver(false),
	m_isSceneClear(false)
{
	// プレイヤーのグラフィックロード
	m_playerHandle = LoadGraph("data/image/player.png");
	assert(m_playerHandle != -1);
	m_bgHandle = LoadGraph("data/image/backGround.png");
	assert(m_bgHandle != -1);
	m_mapHandle = LoadGraph("data/image/map.png");
	assert(m_mapHandle != -1);
	m_enemyHandle = LoadGraph("data/image/Enemy/matasaburo.png");
	assert(m_bgHandle != -1);

	// プレイヤーのメモリ確保
	m_pPlayer = new Player{ this };
	m_pPlayer->SetHandle(m_playerHandle);	// Playerにグラフィックのハンドルを渡す

	// 背景のメモリ確保
	m_pBg = new Bg;
	m_pBg->SetHandle(m_bgHandle);
	m_pBg->SetMapHandle(m_mapHandle);
	m_pBg->SetPlayer(m_pPlayer);
	m_pPlayer->SetBg(m_pBg);

	// ポーズ画面のメモリ確保
	m_pPause = new ScenePause{ m_pPlayer };

	// ショットの初期化
	m_pShot.resize(kShotMax);
	for (int i = 0; i < m_pShot.size(); i++)
	{
		m_pShot[i] = nullptr; // 未使用状態にする
	}

	// 敵の初期化
	m_pEnemy.resize(kEnemyMax);
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		m_pEnemy[i] = nullptr; // 未使用状態にする
	}

	// 回復アイテムの初期化
	m_pRecovery.resize(kRecoveryMax);
	for (int i = 0; i < m_pRecovery.size(); i++)
	{
		m_pRecovery[i] = nullptr; // 未使用状態にする
	}
}

SceneMain::~SceneMain()
{
	// メモリからグラフィックを削除
	DeleteGraph(m_playerHandle);
	DeleteGraph(m_bgHandle);
	DeleteGraph(m_enemyHandle);

	// 背景のメモリ解放
	delete m_pBg;
	m_pBg = nullptr;

	// ポーズ画面のメモリ確保
	delete m_pPause;
	m_pPause = nullptr;

	// プレイヤーのメモリ解放
	delete m_pPlayer;
	m_pPlayer = nullptr;

	// ショットのメモリ解放
	for (int i = 0; i < m_pShot.size(); i++)
	{
		if (m_pShot[i])
		{
			// nullptrでない場合、nullptrを入れる
			delete m_pShot[i];
			m_pShot[i] = nullptr;
		}
	}

	// 敵のメモリ解放
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		if (m_pEnemy[i])
		{
			// nullptrでない場合、nullptrを入れる
			delete m_pEnemy[i];
			m_pEnemy[i] = nullptr;
		}
	}

	// 回復アイテムのメモリ解放
	for (int i = 0; i < m_pRecovery.size(); i++)
	{
		if (m_pRecovery[i])
		{
			// nullptrでない場合、nullptrを入れる
			delete m_pRecovery[i];
			m_pRecovery[i] = nullptr;
		}
	}
}

void SceneMain::Init()
{
	// 画面遷移の初期化
	m_isSceneGameOver = false;
	m_isSceneClear = false;
	m_isExistLineMove = false;

	// ポーズ画面の初期化
	m_pPause->Init();

	// プレイヤーの初期化
	assert(m_pPlayer);	// m_pPlayer == nullptrの場合止まる
	m_pPlayer->Init();

	// 背景の初期化
	m_pBg->Init();
	

	// 敵の初期化
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		if (m_pEnemy[i])
		{
			m_pEnemy[i]->Init();
		}
	}

	// 回復アイテムの初期化
	for (int i = 0; i < m_pRecovery.size(); i++)
	{
		if (m_pRecovery[i])
		{
			m_pRecovery[i]->Init();
		}
	}
}

void SceneMain::End()
{
}

void SceneMain::Update()
{
	// プレイヤーの残機が0未満の場合
	if (m_pPlayer->GetLife() < 0)
	{
		m_isSceneGameOver = true; // ゲームオーバー画面に遷移
	}

	// TODO:ボスを倒したらクリア画面に遷移する
	// Cキーでクリア画面に移動するようにする
	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if (Pad::IsTrigger(pad & PAD_INPUT_3))
	{
		m_isSceneClear = true; // クリア画面に遷移
	}

	// ポーズ画面の更新
	m_pPause->Update();

	// ポーズ画面が表示されている場合画面を止める
	if (m_pPause->IsExist())
	{
		return;
	}

	// 背景の更新
	m_pBg->Update();

	// プレイヤーの更新
	m_pPlayer->Update();

	m_playerPos = m_pPlayer->GetPos();		// プレイヤーの現在地を取得
	Rect playerRect = m_pPlayer->GetColRect();	// プレイヤーの当たり判定

	// プレイヤーが一定座標に到達したら敵を登場させる
	if (m_pPlayer->GetPos().x > 100 && m_pPlayer->GetPos().x < 103)
	{
		CreateMatasaburo();
	}

	// プレイヤーが画面内に移動したらE缶を表示する
	if (m_playerPos.x >= 100 && !m_isGetFullHpRecovery)
	{
		DropFullHpRecovery();
	}

	// 弾の更新
	for (int i = 0; i < m_pShot.size(); i++)
	{
		// nullptrなら処理は行わない
		if (!m_pShot[i]) continue;

		m_pShot[i]->Update();

		// アイテム2号の場合
		if (m_pShot[i]->GetShotType() == ShotType::kShotLineMove)
		{
			// 画面上に存在するか
			if (m_pShot[i]->IsExist())
			{
				m_isExistLineMove = true;
			}
			else
			{
				m_isExistLineMove = false;
			}

			// 弾の当たり判定
			Rect shotRect = m_pShot[i]->GetColRect();
			if (playerRect.IsCollision(shotRect))
			{
				m_pPlayer->RideLineMove(shotRect);
			}
		}

		// 画面外に出たらメモリを解放する
		if (!m_pShot[i]->IsExist())
		{
			delete m_pShot[i];
			m_pShot[i] = nullptr;
		}
	}

	// 敵の更新
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		// nullptrなら処理は行わない
		if (!m_pEnemy[i]) continue;
		m_pEnemy[i]->Update();

		// 使用済みの敵キャラクターを削除
		if (!m_pEnemy[i]->IsExist())
		{
			// 確率でアイテムをドロップ
			int getRandDrop = GetRand(100);

			if (getRandDrop <= 10)
			{
				DropHpSmallRecovery(i); // HP回復(小)
			}
			else if (getRandDrop <= 15)
			{
				DropHpGreatRecovery(i);	// HP回復(大)
			}
			else if (getRandDrop <= 25)
			{
				DropShotSmallRecovery(i); // 弾エネルギー(小)
			}
			else if (getRandDrop <= 30)
			{
				DropShotGreatRecovery(i); // 弾エネルギー(大)
			}
			else if (getRandDrop <= 32)
			{
				DropLifeRecovery(i);	// 残機
			}
			
			// メモリを解放する
			delete m_pEnemy[i];
			m_pEnemy[i] = nullptr;	// nullptrを入れる
		}
		else
		{
			// 敵とプレイヤーの当たり判定
			Rect enemyRect = m_pEnemy[i]->GetColRect();
			if (playerRect.IsCollision(enemyRect))
			{
				m_pPlayer->OnDamage();
			}

			for (int j = 0; j < m_pShot.size(); j++)
			{
				// nullptrなら処理は行わない
				if (!m_pShot[j]) continue;

				// 敵と弾の当たり判定
				// アイテム２号の場合は敵との当たり判定を無視する
				if (m_pShot[j]->GetShotType() != ShotType::kShotLineMove)
				{
					Rect shotRect = m_pShot[j]->GetColRect(); // 弾の当たり判定
					if (shotRect.IsCollision(enemyRect))
					{
						m_pEnemy[i]->OnDamage();
					}
					if (enemyRect.IsCollision(shotRect))
					{
						// 弾を削除
						delete m_pShot[j];
						m_pShot[j] = nullptr;
					}
				}
			}
		}
	}

	// 回復アイテムの更新
	for (int i = 0; i < m_pRecovery.size(); i++)
	{
		// nullptrなら処理は行わない
		if (!m_pRecovery[i]) continue;

		m_pRecovery[i]->Update();

		Rect recoveryRect = m_pRecovery[i]->GetColRect();	// 回復アイテムの当たり判定
		// プレイヤーと回復アイテムの当たり判定
		if (playerRect.IsCollision(recoveryRect))
		{
			if (dynamic_cast<RecoverySmallHp*>(m_pRecovery[i])) // HP小回復
			{
				m_pPlayer->HpSmallRecovery();
			}
			else if (dynamic_cast<RecoveryGreatHp*>(m_pRecovery[i])) // HP大回復
			{
				m_pPlayer->HpGreatRecovery();
			}
			else if (dynamic_cast<RecoverySmallShot*>(m_pRecovery[i])) // 弾小回復
			{
				m_pPlayer->ShotSmallRecovery();
			}
			else if (dynamic_cast<RecoveryGreatShot*>(m_pRecovery[i])) // 弾大回復
			{
				m_pPlayer->ShotGreatRecovery();
			}
			else if (dynamic_cast<RecoveryLife*>(m_pRecovery[i])) // 残機回復
			{
				m_pPlayer->LifeRecovery();
			}
			else if (dynamic_cast<RecoveryFullHp*>(m_pRecovery[i])) // HP全回復
			{
				if (!m_isGetFullHpRecovery)  // E缶を取得してない場合
				{
					m_pPlayer->GetHpFullRecovery();
					m_isGetFullHpRecovery = true;
				}
			}

			// 取得したらアイテムを消す
			delete m_pRecovery[i];
			m_pRecovery[i] = nullptr;
		}
	}
}

void SceneMain::Draw()
{
	// 描画先スクリーンをクリアする
	ClearDrawScreen();

	// 背景の描画
	m_pBg->Draw();

	// プレイヤーの描画
	m_pPlayer->Draw();

	// 弾の描画
	for (int i = 0; i < m_pShot.size(); i++)
	{
		// nullptrなら処理は行わない
		if (!m_pShot[i])continue;
		m_pShot[i]->Draw();
	}

	// 敵の描画
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		// nullptrなら処理は行わない
		if (!m_pEnemy[i])continue;
		m_pEnemy[i]->Draw();
	}

	// 回復アイテムの描画
	for (int i = 0; i < m_pRecovery.size(); i++)
	{
		// nullptrなら処理は行わない
		if (!m_pRecovery[i])continue;
		m_pRecovery[i]->Draw();
	}

	// 現在のHP分だけ四角を描画する
	for (int i = 0; i < m_pPlayer->GetHp(); i++)
	{
		DrawBox(10, 10 + 10 * i, 40, (10 + 10 * i) + 5, 0xeee8aa, true);
	}

	// 現在選択中の武器の弾数を左上に表示
	if (m_pPlayer->IsMetal()) // メタル
	{
		for (int i = 0; i < m_pPlayer->GetMetalEnergy(); i++)
		{
			DrawBox(50, 10 + 10 * i, 80, (10 + 10 * i) + 5, 0xc0c0c0, true);
		}
	}
	if (m_pPlayer->IsFire()) // ファイア
	{
		for (int i = 0; i < m_pPlayer->GetFireEnergy(); i++)
		{
			DrawBox(50, 10 + 10 * i, 80, (10 + 10 * i) + 5, 0xff4500, true);
		}
	}
	if (m_pPlayer->IsLineMove()) // 2号
	{
		for (int i = 0; i < m_pPlayer->GetLineEnergy(); i++)
		{
			DrawBox(50, 10 + 10 * i, 80, (10 + 10 * i) + 5, 0xb22222, true);
		}
	}

	// ポーズ画面の表示
	m_pPause->Draw();

	/*ポーズ画面表示中*/
	if (m_pPause->IsExist())
	{
		// 現在のHPを表示
		DrawFormatString(kTextPosX, kDisPosY, 0xffffff, "P :");
		for (int i = 0; i < m_pPlayer->GetHp(); i++) // 現在のHP分だけ四角を描画する
		{
			DrawBox(kBarPosX + kBarInterval * i, kDisPosY, (kBarPosX + kBarInterval * i) + kBarWidth, kDisPosY + kBarHeight, 0xeee8aa, true);
		}

		// 現在の弾エネルギー数を表示
		// メタル
		DrawFormatString(kTextPosX, kDisPosY + kInterval, 0xffffff, "M :");
		for (int i = 0; i < m_pPlayer->GetMetalEnergy(); i++) // 現在のエネルギー分だけ四角を描画する
		{
			DrawBox(kBarPosX + kBarInterval * i, kDisPosY + kInterval, (kBarPosX + kBarInterval * i) + kBarWidth, kDisPosY + kInterval + kBarHeight, 0xeee8aa, true);
		}

		// ファイアー
		DrawFormatString(kTextPosX, kDisPosY + kInterval * 2, 0xffffff, "F :");
		for (int i = 0; i < m_pPlayer->GetFireEnergy(); i++) // 現在のエネルギー分だけ四角を描画する
		{
			DrawBox(kBarPosX + kBarInterval * i, kDisPosY + kInterval * 2, (kBarPosX + kBarInterval * i) + kBarWidth, kDisPosY + kInterval * 2 + kBarHeight, 0xeee8aa, true);
		}

		// アイテム2号
		DrawFormatString(kTextPosX, kDisPosY + kInterval * 3, 0xffffff, "2 :");
		for (int i = 0; i < m_pPlayer->GetLineEnergy(); i++) // 現在のエネルギー分だけ四角を描画する
		{
			DrawBox(kBarPosX + kBarInterval * i, kDisPosY + kInterval * 3, (kBarPosX + kBarInterval * i) + kBarWidth, kDisPosY + kInterval * 3 + kBarHeight, 0xeee8aa, true);
		}

		// 現在のE缶数を表示
		DrawFormatString(kTextPosX, kDisPosY + kInterval * 4, 0xffffff, "E : %d", m_pPlayer->GetFullHpRecovery());

		// 現在の残機数を表示
		DrawFormatString(kTextPosX, kDisPosY + kInterval * 5, 0xffffff, "残機数:%d", m_pPlayer->GetLife());
	}
}

/*弾の生成*/
bool SceneMain::AddShot(ShotBase* pShot)
{
	// nullptrを渡されたら止まる
	assert(pShot);

	for (int i = 0; i < m_pShot.size(); i++)
	{
		// 使用中なら次のチェックを行う
		if (m_pShot[i])continue;

		// m_pShot[i] == nullptrなので新しく登録する
		m_pShot[i] = pShot;

		// 登録したら終了
		return true;
	}

	// m_pShotにポインタを登録できなかった
	delete pShot;
	return false;
}

/*アイテムドロップ*/
void SceneMain::DropHpSmallRecovery(int enemyIndex) // HP小回復
{
	for (int i = 0; i < m_pRecovery.size(); i++)
	{
		if (!m_pRecovery[i])
		{
			m_pRecovery[i] = new RecoverySmallHp;
			m_pRecovery[i]->Start(m_pEnemy[enemyIndex]->GetPos());
			m_pRecovery[i]->Init();
			return;
		}
	}
}

void SceneMain::DropHpGreatRecovery(int enemyIndex) // HP大回復
{
	for (int i = 0; i < m_pRecovery.size(); i++)
	{
		if (!m_pRecovery[i])
		{
			m_pRecovery[i] = new RecoveryGreatHp;
			m_pRecovery[i]->Start(m_pEnemy[enemyIndex]->GetPos());
			m_pRecovery[i]->Init();
			return;
		}
	}
}

void SceneMain::DropShotSmallRecovery(int enemyIndex) // 弾小回復
{
	for (int i = 0; i < m_pRecovery.size(); i++)
	{
		if (!m_pRecovery[i])
		{
			m_pRecovery[i] = new RecoverySmallShot;
			m_pRecovery[i]->Start(m_pEnemy[enemyIndex]->GetPos());
			m_pRecovery[i]->Init();
			return;
		}
	}
}

void SceneMain::DropShotGreatRecovery(int enemyIndex) // 弾大回復
{
	for (int i = 0; i < m_pRecovery.size(); i++)
	{
		if (!m_pRecovery[i])
		{
			m_pRecovery[i] = new RecoveryLife;
			m_pRecovery[i]->Start(m_pEnemy[enemyIndex]->GetPos());
			m_pRecovery[i]->Init();
			return;
		}
	}
}

void SceneMain::DropLifeRecovery(int enemyIndex) // 残機回復
{
	for (int i = 0; i < m_pRecovery.size(); i++)
	{
		if (!m_pRecovery[i])
		{
			m_pRecovery[i] = new RecoveryGreatShot;
			m_pRecovery[i]->Start(m_pEnemy[enemyIndex]->GetPos());
			m_pRecovery[i]->Init();
			return;
		}
	}
}

void SceneMain::DropFullHpRecovery() // HP全回復
{
	for (int i = 0; i < m_pRecovery.size(); i++)
	{
		if (!m_pRecovery[i])
		{
			m_pRecovery[i] = new RecoveryFullHp;
			m_pRecovery[i]->Start({ 500, 500 }); // アイテムの位置を設定
			m_pRecovery[i]->Init();
			return;
		}
	}
}

/*敵の生成*/
void SceneMain::CreateMatasaburo()
{
	//使われていない場所にアドレスを保存する
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		if (!m_pEnemy[i])	// nullptrであることをチェックする
		{
			m_pEnemy[i] = new Matasaburo;
			m_pEnemy[i]->SetHandle(m_enemyHandle);
			m_pEnemy[i]->Start();
			m_pEnemy[i]->Init();
			return;	// 1体分メモリを確保できたらその時点で終了
		}
	}
}
