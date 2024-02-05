#include "SceneExplanation.h"
#include "SoundManager.h"
#include "Player.h"
#include "DeathYourEnemy.h"
#include "Shot/Shot.h"
#include "DxLib.h"
#include "Pad.h"
#include "Game.h"
#include <cassert>

namespace
{
	// 文字の表示位置
	constexpr int kSelectChirPosX = kScreenWidth * 0.4;
	constexpr int kSelectChirPosY = kScreenHeight * 0.8;

	// スクロール移動量
	constexpr float backGround_scale = 1.2f;
	// 背景の拡大率
	constexpr int kBgScale = 1;
}

SceneExplanation::SceneExplanation():
	m_isSceneEnd(false),
	m_fadeAlpha(255)
{
	// ゲーム画面描画先の生成
	// 画面サイズと同じ大きさのグラフィックデータを作成する
	m_gameScreenHandle = MakeScreen(kScreenWidth, kScreenHeight, true);

	// メモリ確保
	m_pSoundManager = new SoundManager;

	// グラフィックのロード
	m_playerHandle = LoadGraph("data/Player.png");
	assert(m_playerHandle != -1);

	// プレイヤーのメモリ確保
	m_pPlayer = new Player{ this };
	m_pPlayer->SetHandle(m_playerHandle);	// Playerにグラフィックのハンドルを渡す

	m_pDeathYourEnemy.resize(DeathMax);
	for (int i = 0; i < m_pDeathYourEnemy.size(); i++)
	{
		m_pDeathYourEnemy[i] = nullptr;
	}
}

SceneExplanation::~SceneExplanation()
{
	// MakeScreenで作成したらグラフィックを削除する
	DeleteGraph(m_gameScreenHandle);
	// メモリからグラフィックを削除
	DeleteGraph(m_playerHandle);


	// メモリ解放
	delete m_pPlayer;
	m_pPlayer = nullptr;
	for (int i = 0; i < m_pDeathYourEnemy.size(); i++)
	{
		if (m_pDeathYourEnemy[i] != nullptr)
		{
			delete m_pDeathYourEnemy[i];
			m_pDeathYourEnemy[i] = nullptr;
		}
	}
	delete m_pSoundManager;
	m_pSoundManager = nullptr;
}

void SceneExplanation::Init()
{
	assert(m_pPlayer);	// m_pPlayer == nullptr	の場合止まる

	m_pPlayer->Init();
	//サウンドマネージャーの初期化
	m_pSoundManager->Init();

	Graph = LoadGraph("data/Explanation.png");
	BgGraph = LoadGraph("data/Map/patter2.png");
	m_isSceneEnd = false;
	m_fadeAlpha = 255;
}

void SceneExplanation::Update()
{
	if (Pad::IsTrigger(PAD_INPUT_4))
	{
		m_isSceneEnd = true;

		m_pSoundManager->SoundButton();
	}

	// 背景スクロール
	m_scrollX += backGround_scale;

	// フェードイン
	if (m_isSceneEnd)
	{
		m_fadeAlpha += 8;
		if (m_fadeAlpha > 255)
		{
			m_fadeAlpha = 255;
		}
	}
	else
	{
		m_fadeAlpha -= 8;
		if (m_fadeAlpha < 0)
		{
			m_fadeAlpha = 0;
		}
	}

	m_pPlayer->Update();

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
}

void SceneExplanation::Draw()
{
	DrawGraph(0, 0, m_gameScreenHandle, true);

	BackDraw();

	SetFontSize(64);
	DrawString(kSelectChirPosX, kSelectChirPosY, "Aボタンでタイトルに戻る", 0xffffff);

	// フェードの描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeAlpha);	// 半透明で表示開始
	DrawBox(0, 0, kScreenWidth, kScreenHeight, GetColor(255, 255, 255), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		// 不透明に戻しておく
}

void SceneExplanation::BackDraw()
{
	Size bg1Size;
	GetGraphSize(BgGraph, &bg1Size.width, &bg1Size.height);

	// スクロール量を計算
	int scrollBg = static_cast<int>(m_scrollX) % static_cast<int>(bg1Size.width * kBgScale);

	for (int index = 0; index < 4; index++)
	{
		DrawRotaGraph2(-scrollBg + index * bg1Size.width * kBgScale,
			kScreenHeight - bg1Size.height * kBgScale,
			0, 0,
			kBgScale, 0.0f,
			BgGraph, true);
	}
}

void SceneExplanation::End()
{
	// 背景をメモリから削除
	DeleteGraph(Graph);

	m_pSoundManager->End();
}

bool SceneExplanation::IsSceneEnd() const
{
	return m_isSceneEnd && (m_fadeAlpha >= 255);
}
