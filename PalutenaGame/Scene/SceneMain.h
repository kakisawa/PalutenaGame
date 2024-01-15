#pragma once
#include <vector>
#include "Vec2.h"

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

	// シーン処理
	bool m_isSceneEnd;		// シーンを終了する時trueにする


	// プレイヤー
	Player* m_pPlayer;
	// 背景
	Back* m_pBack;

	// エネミー
	std::vector<EnemyBase>* m_pEnemy;

	/*std::vector<MozueyeEnemy> m_pMozueyeEnemy;
	std::vector<DeathYourEnemy> m_pDeathYourEnemy;
	std::vector<PumpkinEnemy> m_pPumpkinEnemy;*/
};

