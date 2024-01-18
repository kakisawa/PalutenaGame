#pragma once
#include "Player.h"
#include "Enemy.h"

// ゲームシーンをクラス化する
class SceneMain
{
public:
	SceneMain();
	~SceneMain();

	void Init();
	void Update();
	void Draw();
	void End();		// シーンの終了処理
	
	// シーンを終了させるかどうか
	bool IsSceneEnd() const;

	bool IsCollision(const Player& player, const Enemy& enemy);

private:
	// 画面内に同時に存在できる敵の最大数
	static constexpr int kEnemyMax = 16;

private:

	int m_hk;		// 背景
	int m_playerHandle;	// プレイヤーのグラフィック
	int m_enemyHandle;	// 敵のグラフィック

	int m_bgmHandle;	// BGMのハンドル
	int m_enemyStartSe;	// 敵が登場する時の効果音
	int m_playerDath;

	Player m_player;
	Enemy m_enemy[kEnemyMax];

	bool m_isGameOver;		// ゲームオーバーかどうかのフラグ
	bool m_isSceneEnd;		// シーンを終了する時trueにする
	int m_playFrameCount;	// 生き残っている時間

	// Enemyの生成制御
	int m_enemyCreateNum;	// 今までに生産した敵の数
	int m_enemyWaitFrame;	// 敵生成までの待ち時間

	// フェードイン、アウト
	int m_fadeAlpha;
};

