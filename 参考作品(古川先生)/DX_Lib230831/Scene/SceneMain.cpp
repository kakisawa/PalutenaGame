#include "SceneMain.h"
#include "DxLib.h"
#include "Player.h"
#include "Bg.h"
#include "Pad.h"
#include "Rect.h"

// 登場する敵
// #include "EnemyBase.h"
#include "EnemyLeft.h"
#include "EnemyRight.h"
#include "EnemyToPlayer.h"

// 登場するショット
#include "ShotMagicWand.h"
#include <cassert>

namespace
{
	// 一度に登場できる敵の最大数
	constexpr int kEnemyMax = 32;
	// 何フレームおきに敵が登場するか
	constexpr int kEnemyInterval = 60;

	// 画面内に一度に出てくる弾の最大数
	constexpr int kShotMax = 260;

	// 画面がワイプするのにかかるフレーム数
	constexpr int kWipeFrame = 30;
}

SceneMain::SceneMain():
	m_enemyInterval(0),
	m_shakeFrame(0),
	m_wipeFrame(0)
{
	// ゲーム画面描画先の生成
	// 画面サイズと同じ大きさのグラフィックデータを作成する
	m_gameScreenHandle = MakeScreen(Game::kScreenWidth, Game::kScreenHeight, true);

	// グラフィックのロード
	m_playerHandle = LoadGraph("data/image/player.png");
	assert(m_playerHandle != -1);
	m_enemyHandle = LoadGraph("data/image/Enemy.bmp");
	assert(m_enemyHandle != -1);
	m_bgHandle = LoadGraph("data/image/bg.png");
	assert(m_bgHandle != -1);

	// プレイヤーのメモリ確保
	m_pPlayer = new Player{this};
	m_pPlayer->SetHandle(m_playerHandle);	// Playerにグラフィックのハンドルを渡す

	// 背景のメモリ確保
	m_pBg = new Bg;
	m_pBg->SetHandle(m_bgHandle);
	
	// 敵の準備
	// m_pEnemy(vector)何もしなければサイズは0

	// resize関数でkEnemyMaxだけデータを保存できるようにする
	m_pEnemy.resize(kEnemyMax);

	// いつもはコンストラクタでメモリを確保して
	// デストラクタで解放してください
	// ランダムにEnemyLeft,EnemyRight,EnemyToPlayerを確保したい
	// どれかわからないのであらかじめ確保することが出来ない
	// ->動的にメモリを確保する Update()中に必要に応じて

	// 初期状態ではメモリを確保していないことが分かるようにしておく
	// 未使用状態にする nullptrを入れておく
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		m_pEnemy[i] = nullptr;

			// m_pEnemyの中には何が入るかわからない
			// ↓のいずれかが入る
			// 現時点ではどれが入るのか決定できない
		// new EnemyLeft;
		// new EnemyRighr;
		// new EnemyToPlayer;
	}

	// ショットの準備
	m_pShot.resize(kShotMax);
	for (int i = 0; i < m_pShot.size(); i++)
	{
		m_pShot[i] = nullptr;	// 未使用
	}

	//m_pShot = new ShotMagicWand;
	//// SceneMainの関数を使いたいのでポインタを渡しておく
	//// thisで自身のポインタを取得可能
	//m_pShot->SetMain(this);
}

SceneMain::~SceneMain()
{
	// MakeScreenで作成したらグラフィックを削除する
	DeleteGraph(m_gameScreenHandle);
	
	// メモリからグラフィックを削除
	DeleteGraph(m_playerHandle);
	DeleteGraph(m_enemyHandle);
	DeleteGraph(m_bgHandle);

	// メモリの解放
	delete m_pPlayer;
	m_pPlayer = nullptr;

	delete m_pBg;
	m_pBg = nullptr;
	
	// メモリが確保されている敵を探して開放していく
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		// nullpte以外の物が入っているということは、そこにはポインタが入っているということ
		if (m_pEnemy[i] != nullptr)	
		{
			delete m_pEnemy[i];
			m_pEnemy[i] = nullptr;	// 未使用状態と分かるようにしておく
		}
	}

	for (int i = 0; i < m_pShot.size(); i++)
	{
		if (m_pShot[i])
		{
			// nullptrではない場合
			delete m_pShot[i];
			m_pShot[i] = nullptr;
		}
	}
}

void SceneMain::Init()
{
	assert(m_pPlayer);	// m_pPlayer == nullptr	の場合止まる

	m_pPlayer->Init();
	m_pBg->Init();
}

void SceneMain::End()
{
	// メモリからグラフィックを削除
}

void SceneMain::Update()
{
	m_pPlayer->Update();
	m_pBg->Update();

	Rect playerRect = m_pPlayer->GetColRect();
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		if (m_pEnemy[i])	// nullptrではないチェック
		{
			m_pEnemy[i]->Update();
		
			// 使用済みの敵キャラクタを削除する必要がある
			if (!m_pEnemy[i]->IsExist())
			{
				// メモリを解放する
				delete m_pEnemy[i];
				m_pEnemy[i] = nullptr;	// 使っていないとわかるようにする
			}
			else
			{
				// 存在している敵とプレイヤーの当たり判定
				Rect enemyRect = m_pEnemy[i]->GetColRect();
				if (playerRect.IsCollsion(enemyRect))
				{
				//	// test
					printfDx("当たっている\n");
					m_pPlayer->OnDamage();
					// プレイヤーがダメージを受けた瞬間、画面が揺れ始まる
					m_shakeFrame = 8;
				}
			}
		}
	}
	
	for (int i = 0; i < m_pShot.size(); i++)
	{
		// nullptrなら処理は行わない
		if (!m_pShot[i])	continue;

		m_pShot[i]->Update();
		// 画面外に出たらメモリ解放
		if (!m_pShot[i]->IsExist())
		{
			delete m_pShot[i];
			m_pShot[i] = nullptr;
		}
	}

	// ワイプ処理
	m_wipeFrame++;
	if (m_wipeFrame > kWipeFrame)	m_wipeFrame = kWipeFrame;


	// 敵キャラクターを登場させる
	// kEnemyIntervalフレーム経過するごとにランダムに敵を登場させる
	m_enemyInterval++;
	if (m_enemyInterval >= kEnemyInterval)
	{
		m_enemyInterval = 0;

		// ランダムに敵を選択
		switch (GetRand(2))
		{
		case 0:	// Left
			CreateEnemyLeft();
			break;

		case 1:		// Right
			CreateEnemyRight();
			break;

		default:	assert(false);	// breakなし

		case 2:		// ToPlayer
			CreateEnemyToPlayer();
			break;
		}
	}
	// 画面揺れフレームのカウントダウン
	m_shakeFrame--;
	if (m_shakeFrame < 0)	m_shakeFrame = 0;
}

void SceneMain::Draw()
{
	// バックバッファに直接書き込むのではなく、
	// 自分で生成したグラフィックデータに対して書き込みを行う
	SetDrawScreen(m_gameScreenHandle);

	// 描画先スクリーンをクリアする
	ClearDrawScreen();

	m_pBg->Draw();
	m_pPlayer->Draw();

	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		if (m_pEnemy[i])	// nullptrではないチェック
		{
			m_pEnemy[i]->Draw();
		}
	}

	for (int i = 0; i < m_pShot.size(); i++)
	{
		// nullptrかどうかをチェックする
		if (!m_pShot[i])	continue;// nullptrなら以降の処理は行わない
		m_pShot[i]->Draw();
	}

	// デバッグ表示
	DrawString(8, 8, "SceneMain", GetColor(255, 255, 255));

	// キャラクターをデバッグ表示する
	Vec2 playerPos = m_pPlayer->GetPos();
	DrawFormatString(8, 24, GetColor(255, 255, 255),
		"プレイヤーの座標(%.2f,%.2f)", playerPos.x, playerPos.y);

	// 弾が何発あるか表示
	int shotNum = 0;
	for (int i = 0; i < m_pShot.size(); i++)
	{
		if (m_pShot[i])	 shotNum++;
	}
	DrawFormatString(8, 40, GetColor(255, 255, 255), "ShotNum:%d", shotNum);

	// バックバッファに書き込む設定に戻しておく
	SetDrawScreen(DX_SCREEN_BACK);

	// ゲーム画面をバックバッファに描画する
	int screenX = 0;
	int screenY = 0;

		if (m_shakeFrame > 0)
		{
			// 画面揺れ
			screenX = GetRand(8) - 4;
			screenY = GetRand(8) - 4;
		}

		// m_wipeFrameから描画する範囲を計算する
		// m_wipeFrameはゲーム開始時に0、
		// 舞フレーム加算されてkWipeFrame(30)まで変化する
		// wipeRate はm_wipeFrameの変化に合わせて0.0->1.0に変化する

		float wipeRate = static_cast<float>(m_wipeFrame) / static_cast<float>(kWipeFrame);
		int wipeHeight = Game::kScreenHeight * wipeRate;

		// 画面揺れ
		//DrawRectGraph(screenX, screenY,
		//	0, 0, Game::kScreenWidth, wipeHeight,
		//	m_gameScreenHandle, true, false);

		// offsetの値をwipeの進行に合わせて320->0に変化させたい
		// 0->320に変化させるのはわかりやすい	320*wipeRate

		int offset = 320 * (1.0 - wipeRate);

		// 画面の上から1ラインずつ描画を行っている

		// ぐにゃぐにゃ
		for (int y = 0; y < Game::kScreenHeight; y++)
		{
			int x = sinf(y*0.05f) * offset;
			DrawRectGraph(x, y,
				0, y, Game::kScreenWidth, 1,
				m_gameScreenHandle, true, false);
		}

	//	printfDx("rate:%f\n", wipeRate);

	// DrawGraph(0, 0, m_gameScreenHandle, true);
}

Vec2 SceneMain::GetNearEnemyPos(Vec2 pos) const
{
	// 敵がいない場合は適当な座標を返す
	Vec2 result{ 0,0 };
	// 最初の敵チェック済みフラグ
	bool isFirst = true;

	// 一番近い敵キャラクターの座標をresultに入れる
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		// 使われていない敵はチェックしない
		if (!m_pEnemy[i])	continue;

		// ここにきている時点でm_pEnemy[i]はnullptrでないことは確定

		// すでに消えることが確定している敵はチェックしない
		if (!m_pEnemy[i]->IsExist()) continue;

		// posとm_pEnemyの距離をチェックする

		if (isFirst)
		{
			// 一体目の敵
			// 距離がいくら離れていようと現時点では一番近い敵
			result = m_pEnemy[i]->GetPos();
			isFirst = false;
		}
		else
		{
			// 2体目以降の敵
			// resultの中には一番近い敵の座標が入っている

			// 今までチェックした中で一番近い敵との距離
			Vec2 toNear = result - pos;	// posから暫定一位の座標に向かうベクトル
			
			// チェックする敵との距離
			Vec2 toEnemy = m_pEnemy[i]->GetPos() - pos;	// posからチェック中の敵に向かうベクトル

			// 処理を軽くするため距離の比較を行う場合は距離の二乗で比較を行う
			if (toNear.sqLength() > toEnemy.sqLength())
			{
				// 今チェックしている敵への距離が暫定一位よりも短い場合
				// 今チェックしている敵を暫定一位に
				result = m_pEnemy[i]->GetPos();
			}
			// 暫定一位の方が今チェックしている敵より近い場合は何もしない
		}
	}

	// 全ての敵のチェックを行ったのでこいつが一位で確定
	return result;
}

bool SceneMain::AddShot(ShotBase* pShot)
{
	// nullptrを渡されたら止まる
	assert(pShot);

	for (int i = 0; i < m_pShot.size(); i++)
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

void SceneMain::CreateEnemyLeft()
{
	// 使われていない箱を探してそこにアドレスを保存する
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		if (!m_pEnemy[i]) // nullptrであることをチェックする
		{
			m_pEnemy[i] = new EnemyLeft;
			m_pEnemy[i]->Init();
			m_pEnemy[i]->SetHandle(m_enemyHandle);
			m_pEnemy[i]->Start();
			return;	// メモリを確保できた以降はチェックしない
		}
	}
}

void SceneMain::CreateEnemyRight()
{
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		if (!m_pEnemy[i]) // nullptrであることをチェックする
		{
			m_pEnemy[i] = new EnemyRight;
			m_pEnemy[i]->Init();
			m_pEnemy[i]->SetHandle(m_enemyHandle);
			m_pEnemy[i]->Start();
			return;	// メモリを確保できた以降はチェックしない
		}
	}
}

void SceneMain::CreateEnemyToPlayer()
{
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		if (!m_pEnemy[i]) // nullptrであることをチェックする
		{
			// Baseが持たない独自の関数を呼びたい
			EnemyToPlayer* pEnemy = new EnemyToPlayer;
			
			pEnemy->Init();
			pEnemy->SetHandle(m_enemyHandle);
			pEnemy->SetPlayer(m_pPlayer);	// pPlayerはEnemyToPlayerなので呼べる
			pEnemy->Start();

			// pEnemyはすぐ消えるのでm_pEnemyに確保したアドレスをコピーしておく
			m_pEnemy[i] = pEnemy;

			/*
			m_pEnemy[i] = new EnemyToPlayer;
			m_pEnemy[i]->Init();
			m_pEnemy[i]->SetHandle(m_enemyHandle);
			// Playerを設定する必要がある
			m_pEnemy[i]->setPlayer(m_pPlayer);
			m_pEnemy[i]->Start();
			*/
			return;	// メモリを確保できた以降はチェックしない
		}
	}
}
