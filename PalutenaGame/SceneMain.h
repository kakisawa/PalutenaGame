#pragma once
#include <vector>
#include "Vec2.h"

class Player;
class EnemyBase;
class Back;

class SceneMain
{
public:
	SceneMain();
	virtual ~SceneMain();

	void Init();
	void End();
	void Update();
	void Draw();

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

	// プレイヤー
	Player* m_pPlayer;
	// 背景
	Back* m_pBack;
	// 敵
	std::vector<EnemyBase*> m_pEnemy;

};

