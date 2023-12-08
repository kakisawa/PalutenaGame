#pragma once
#include <vector>
#include "Vec2.h"

class Player;
class Bg;
class EnemyBase;
class ShotBase;
class SceneMain
{
public:
	SceneMain();
	virtual ~SceneMain();

	void Init();
	void End();
	void Update();
	void Draw();

	// 特定の座標から一番近くにいる敵の座標を返す関数
	Vec2 GetNearEnemyPos(Vec2 pos) const;
	// ショットを追加する
	// 登録できなかった場合はfalseを返す
	// 登録できなかった場合は内部でpShot解放する
	bool AddShot(ShotBase* pShot);

private:
	// 敵キャラクターの生成
	void CreateEnemyLeft();
	void CreateEnemyRight();
	void CreateEnemyToPlayer();

private:
	// グラフィックのハンドル
	int m_gameScreenHandle;	// ゲーム画面

	int m_playerHandle;
	int m_enemyHandle;
	int m_bgHandle;

	// プレイヤー
	Player* m_pPlayer;
	// 背景
	Bg* m_pBg;
	// 敵
	std::vector<EnemyBase*> m_pEnemy;	// 配列のサイズは実行時に決める(今回はコンストラクタ)
	// EnemyBase* m_pEnemy[16];	

	// ショット
	std::vector<ShotBase*> m_pShot;

	// 
	int m_wipeFrame;

	// 敵の登場間隔
	int m_enemyInterval;

	// ダメージを受けた時の画面揺れ演出
	int m_shakeFrame;
};