#include "DxLib.h"
#include "SceneMain.h"
#include "Player.h"
#include "MozueyeEnemy.h"
#include "DeathYourEnemy.h"
#include "PumpkinEnemy.h"
#include "Shot/Shot.h"
#include "SoundManager.h"
#include "SceneManager.h"
#include "ColorManager.h"
#include "Pause.h"
#include "Time.h"
#include "Game.h"
#include "Rect.h"
#include "Pad.h"
#include <cassert>

namespace 
{
	// 背景描画位置(地面)
	constexpr float BgGroundX = 0;
	constexpr float BgGroundY = static_cast<float>(kScreenHeight) * 0.815f;
	// ゲーム内容説明描画位置
	constexpr float ExplanationX = static_cast<float>(kScreenWidth) * 0.07f;
	constexpr float ExplanationY = static_cast<float>(kScreenHeight) * 0.07f;
	// モズアイ出現位置
	constexpr float MozuX = static_cast<float>(kScreenWidth) * 0.15f;
	constexpr float MozuY = kGround + 9.0f;
	// 死出現位置
	constexpr float DeathX = static_cast<float>(kScreenWidth) * 0.3f;
	constexpr float DeathY = static_cast<float>(kScreenHeight) * 0.4f;
	// パンプキン出現位置
	constexpr float PumpX_1 = static_cast<float>(kScreenWidth) * 0.4;
	constexpr float PumpX_2 = static_cast<float>(kScreenWidth) * 0.8;
	constexpr float PumpX_3 = static_cast<float>(kScreenWidth) * 0.5;
	constexpr float PumpY = static_cast<float>(kScreenHeight) * 0.5f;

	// カウントダウン画像描画位置
	constexpr float CountDownX = static_cast<float>(kScreenWidth) * 0.5f - 53;
	constexpr float CountDownY = static_cast<float>(kScreenHeight) * 0.5f - 114;
}

SceneMain::SceneMain() :
	m_deathYourEnemyGraph(-1),
	m_enemyHandle(-1),
	m_mozueyeEnemy(-1),
	m_pumpkinEnemyGraph(-1),
	m_isSceneEnd(false),
	m_isToGameClear(false),
	m_isToGameOver(false),
	m_fadeAlpha(255),		// 不透明で初期化
	m_enemyInterval(0),
	m_startCount(180),
	m_doorCount(0),
	m_isStartFlag(false),
	m_isStartCountFlag(false),
	m_pShot()
{
	// ゲーム画面描画先の生成
	m_gameScreenHandle = MakeScreen(kScreenWidth, kScreenHeight, true);

	// グラフィックのロード
	m_backHandle = LoadGraph("data/Map/Back1.png");
	assert(m_backHandle != -1);
	m_backGroundHandle = LoadGraph("data/Map/Ground.png");
	assert(m_backGroundHandle != -1);
	m_explanation = LoadGraph("data/explanation2.png");
	assert(m_explanation != -1);
	m_key_A = LoadGraph("data/pxkb_a.png");
	assert(m_key_A != -1);
	m_count1= LoadGraph("data/Count1.png");
	assert(m_count1 != -1);
	m_count2 = LoadGraph("data/Count2.png");
	assert(m_count2 != -1);
	m_count3 = LoadGraph("data/Count3.png");
	assert(m_count3 != -1);
	m_door = LoadGraph("data/01.png");
	assert(m_door != -1);

	// プレイヤーのメモリ確保
	m_pPlayer = new Player{ this };
	// 制限時間のメモリ確保
	m_pTime = new Time;
	// SE/BGMメモリ確保
	m_pSoundManager = new SoundManager;
	// 色メモリ確保
	m_pColorManager = new ColorManager;
	// ポーズ
	m_pPause = new Pause(m_pSoundManager);

	m_pMozueyeEnemy.resize(MozuMax);
	m_pDeathYourEnemy.resize(DeathMax);
	m_pPumpkinEnemy.resize(PumpMax);

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
	DeleteGraph(m_enemyHandle);
	DeleteGraph(m_backGroundHandle);
	DeleteGraph(m_backHandle);
	DeleteGraph(m_count1);
	DeleteGraph(m_count2);
	DeleteGraph(m_count3);
	DeleteGraph(m_explanation);
	DeleteGraph(m_key_A);

	// メモリの解放
	delete m_pPlayer;
	m_pPlayer = nullptr;
	delete m_pTime;
	m_pTime = nullptr;
	delete m_pSoundManager;
	m_pSoundManager = nullptr;
	delete m_pColorManager;
	m_pColorManager = nullptr;
	delete m_pPause;
	m_pPause = nullptr;

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

	m_isToGameClear = false;
	m_isToGameOver = false;
	m_isSceneEnd = false;
	m_isStartFlag = false;
	m_isStartCountFlag = false;

	m_pPlayer->Init();
	m_pTime->Init();
	m_pSoundManager->Init();

	m_fadeAlpha = 255;
	m_enemyInterval = 0;
	m_startCount = 180;
	m_doorCount = 0;

	m_pSoundManager->BGMButtle();
	m_pPause->Init();
}

void SceneMain::Update()
{
	m_pPause->Update();
	m_pSoundManager->SetBgmVolume();
	m_pSoundManager->SetSeVolume();

	// フェードイン
	m_fadeAlpha -= 8;
	if (m_fadeAlpha < 0)
	{
		m_fadeAlpha = 0;
	}

	if (m_isStartFlag == true)
	{
		if (m_startCount <= 0)
		{
			m_isStartCountFlag = true;
			m_startCount = 0;
		}
		m_startCount--;
	}

	// スタートのカウントダウンを始めるフラグ
	if (m_isStartFlag == false)
	{
		if (Pad::IsTrigger(PAD_INPUT_4)) {

			m_isStartFlag = true;
		}
	}
	else if (m_isStartCountFlag)
	{
		if (!m_pPause->GetPauseFlag())
		{
			// プレイヤーが死亡したら(ゲームオーバー)
			if (m_pPlayer->GetPlayerDeath())
			{
				Death();
				m_pPlayer->Death();
			}
			else {
				// 制限時間が終わったら(ゲームクリア)
				if (m_pTime->TimeUp()) {
					Clear();
				}

				m_pPlayer->Update();
				m_pTime->Update();

				Rect playerRect = m_pPlayer->GetColRect();

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
				// モズアイ当たり判定等
				for (int i = 0; i < m_pMozueyeEnemy.size(); i++)
				{
					if (m_pMozueyeEnemy[i])
					{
						m_pMozueyeEnemy[i]->Update();
						m_pPlayer->SetMozu(m_pMozueyeEnemy[i]);

						// 使用済みの敵を削除
						if (!m_pMozueyeEnemy[i]->isExist())
						{
							delete m_pMozueyeEnemy[i];
							m_pMozueyeEnemy[i] = nullptr;
						}
						else {			// 存在している敵とプレイヤーの当たり判定
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
				// 死当たり判定等
				for (int i = 0; i < m_pDeathYourEnemy.size(); i++)
				{
					if (m_pDeathYourEnemy[i])
					{
						m_pDeathYourEnemy[i]->Update();
						m_pPlayer->SetDeath(m_pDeathYourEnemy[i]);

						// 使用済みの敵を削除
						if (!m_pDeathYourEnemy[i]->isExist())
						{
							delete m_pDeathYourEnemy[i];
							m_pDeathYourEnemy[i] = nullptr;
						}
						else {			// 存在している敵とプレイヤーの当たり判定
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
				// パンプキン当たり判定等
				for (int i = 0; i < m_pPumpkinEnemy.size(); i++)
				{

					if (m_pPumpkinEnemy[i])
					{
						//m_pPumpkinEnemy[i]->SetPlayer(m_pPlayer);
						m_pPumpkinEnemy[i]->Update();
						m_pPlayer->SetPump(m_pPumpkinEnemy[i]);

						// 使用済みの敵を削除
						if (!m_pPumpkinEnemy[i]->isExist())
						{
							delete m_pPumpkinEnemy[i];
							m_pPumpkinEnemy[i] = nullptr;
						}
						else
						{		// 存在している敵とプレイヤーの当たり判定
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

				//敵キャラクターの登場
				m_enemyInterval++;
				if (m_enemyInterval >= kEnemyInterval)
				{
					m_enemyInterval = 0;
					// ランダムに生成する敵を選択
					switch (GetRand(2))
					{
					case 0:
						CreateEnemyMozu();
						break;
					case 1:
						CreateEnemyDeath();
						break;
					case 2:
						CreateEnemyPump();
						break;
					}
				}

				// 敵出現扉の点滅
				m_doorCount++;
				if (m_doorCount >= 80)
				{
					m_doorCount = 0;
				}
			}
		}
	}
}


void SceneMain::Draw()
{
	DrawGraph(0, 0, m_gameScreenHandle, true);

	// 描画先スクリーンをクリアする
	ClearDrawScreen();

	BgDraw();			// 背景描画	
	m_pTime->Draw();	// 制限時間描画
	DrawDoor();			// 敵出現扉描画
	CharactorDraw();	// プレイヤー・エネミー描画

	// 弾描画
	for (int i = 0; i < kShotMax; i++)
	{
		if (!m_pShot[i])	continue;
		m_pShot[i]->Draw();
	}

	m_pPause->Draw();			// ポーズ画面描画
	CoundownDraw();				// ゲーム開始前のカウントダウン描画
	StartDraw();				// ゲーム開始前の説明描画

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeAlpha);	// 半透明で表示開始
	DrawBox(0, 0, kScreenWidth, kScreenHeight,
		m_pColorManager->GetColorBlack(), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		// 不透明に戻しておく
}

void SceneMain::End()
{
	// プレイヤーが獲得したスコアを他のシーンに入れる
	SceneManager::s_ResultScore = m_pPlayer->GetScore();

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

	// サウンドの解放
	m_pSoundManager->End();
}

void SceneMain::CharactorDraw()
{
	// プレイヤーの描画
	if (m_pPlayer->GetPlayerDeath())
	{
		m_pPlayer->Death();
		Death();
	}
	if (m_pTime->TimeUp())
	{
		Clear();
	}
	m_pPlayer->Draw();

	// エネミーの描画
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
}

void SceneMain::StartDraw()
{
	if (m_isStartFlag == false)
	{
		DrawExtendGraphF(ExplanationX, ExplanationY,
			ExplanationX + static_cast<float>(kScreenWidth) * 0.85f,
			ExplanationY + static_cast<float>(kScreenHeight) * 0.85f,
			m_explanation, false);
		DrawExtendGraphF((ExplanationX + static_cast<float>(kScreenWidth) * 0.8f - 65),
			ExplanationY + static_cast<float>(kScreenHeight * 0.8f) - 75,
			ExplanationX + static_cast<float>(kScreenWidth) * 0.83f,
			ExplanationY + static_cast<float>(kScreenHeight) * 0.83f,
			m_key_A, true);
	}
}

void SceneMain::CoundownDraw()
{
	if (m_startCount >= 121)
	{
		DrawExtendGraphF(CountDownX,CountDownY,
			CountDownX + 106, CountDownY + 228,
			m_count3, true);
	}
	else if (m_startCount <= 120 && m_startCount >= 61)
	{
		DrawExtendGraphF(CountDownX, CountDownY,
			CountDownX + 106, CountDownY + 228,
			m_count2, true);
	}
	else if (m_startCount <= 60 && m_startCount >= 1)
	{
		DrawExtendGraphF(CountDownX, CountDownY,
			CountDownX + 106, CountDownY + 228,
			m_count1, true);
	}
}

void SceneMain::DrawDoor()
{
	// 文字の点滅描画
	if (m_doorCount < 40)
	{
		// モズアイ出現
		DrawExtendGraphF(static_cast<float>(MozuX), static_cast<float>(MozuY),
			MozuX+56, MozuY+60,
			m_door, true);

		// 死出現位置
		DrawExtendGraphF(static_cast<float>(DeathX), static_cast<float>(DeathY),
			DeathX + 56, DeathY + 60,
			m_door, true);

		// パンプキン出現
		DrawExtendGraphF(static_cast<float>(PumpX_1), static_cast<float>(PumpY),
			PumpX_1+56, PumpY+60,
			m_door, true);
		DrawExtendGraphF(static_cast<float>(PumpX_2), static_cast<float>(PumpY),
			PumpX_2 + 56, PumpY + 60,
			m_door, true);
		DrawExtendGraphF(static_cast<float>(PumpX_3), static_cast<float>(PumpY),
			PumpX_3 + 56, PumpY + 60,
			m_door, true);
	}
}

void SceneMain::BgDraw()
{
	DrawGraphF(0, 0, m_backHandle, false);
	DrawGraphF(BgGroundX, BgGroundY, m_backGroundHandle, true);
}

void SceneMain::Clear()
{
	StopSoundMem(m_pSoundManager->m_bgmButtle);

	m_isSceneEnd = true;
	m_isToGameClear = true;

	// フェードアウト
	m_fadeAlpha += 1;
	if (m_fadeAlpha < 255)
	{
		m_fadeAlpha = 255;
	}
}

void SceneMain::Death()
{
	m_isSceneEnd = true;
	m_isToGameOver = true;

	// フェードアウト
	m_fadeAlpha += 8;
	if (m_fadeAlpha < 255)
	{
		m_fadeAlpha = 255;
	}
}

bool SceneMain::IsSceneEnd() const
{
	return m_isSceneEnd && (m_fadeAlpha >= 255);
}

bool SceneMain::IsToGameOver() const
{
	return m_isToGameOver;
}

bool SceneMain::IsToGameClear() const
{
	return m_isToGameClear;
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
			m_pMozueyeEnemy[i]->Init(m_pPlayer);
			m_pMozueyeEnemy[i]->Start(kScreenWidth * 0.15f, kGround+9);
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
			m_pDeathYourEnemy[i]->Init(m_pPlayer);
			m_pDeathYourEnemy[i]->Start(kScreenWidth * 0.3f, kScreenHeight * 0.4f);
			return;
		}
	}
}

void SceneMain::CreateEnemyPump()
{
	for (int i = 0; i < m_pPumpkinEnemy.size(); i++)
	{
		if (!m_pPumpkinEnemy[i])
		{
			m_pPumpkinEnemy[i] = new PumpkinEnemy;
			m_pPumpkinEnemy[i]->Init(m_pPlayer);

			float EnemyX = kScreenWidth * 0.3f;
			switch (GetRand(2))
			{
			case 0:
				EnemyX = kScreenWidth * 0.4f;
				break;
			case 1:
				EnemyX = kScreenWidth * 0.8f;
				break;
			case 2:
				EnemyX = kScreenWidth * 0.5f;
				break;
			}
			m_pPumpkinEnemy[i]->Start(EnemyX, static_cast<float>(kScreenHeight) * 0.5f);
			return;
		}
	}
}