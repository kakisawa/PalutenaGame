#pragma once
#include <vector>
#include "Vec2.h"

namespace
{
	// モズアイ出現数
	constexpr int MozuMax = 1;	// 17
	// 死出現数
	constexpr int DeathMax = 1;	// 3
	// かぼちゃ出現数
	constexpr int PumpMax = 1;	// 10仮、覚えてない
}

// クラス宣言
class Player;
class Back;
class MozueyeEnemy;
class DeathYourEnemy;
class PumpkinEnemy;

class SceneMain
{
public:
	SceneMain();
	virtual ~SceneMain();

	void Init();
	void Update();
	void Draw();

	void End();

	// シーンを終了させたいか
	bool IsSceneEnd() const;

private:
	//// 敵キャラクターの生成
	//void CreateEnemyLeft();
	//void CreateEnemyRight();
	//void CreateEnemyToPlayer();

	// グラフィックのハンドル
	int m_gameScreenHandle;	// ゲーム画面

	int m_playerHandle;		// プレイヤー
	int m_enemyHandle;		// 敵
	int m_backHandle;		// 背景

	// エネミー
	int m_mozueyeEnemy;			// モズアイ
	int m_deathYourEnemyGraph;	// お前たちの死
	int m_pumpkinEnemyGraph;	// パンプキン君

	int m_fadeAlpha;		// フェードイン、アウト

	// シーン処理
	bool m_isSceneEnd;		// シーンを終了する時trueにする


	// プレイヤー
	Player* m_pPlayer;
	// 背景
	Back* m_pBack;

	// エネミー
	MozueyeEnemy* m_pMozueyeEnemy[MozuMax];
	DeathYourEnemy* m_pDeathYourEnemy[DeathMax];
	PumpkinEnemy* m_pPumpkinEnemy[PumpMax];
};