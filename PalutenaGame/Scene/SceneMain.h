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

	// 画面内に同時に出せる弾の数
	constexpr int kShotMax = 20;
}

// クラス宣言
class Player;
class Back;
class MozueyeEnemy;
class DeathYourEnemy;
class PumpkinEnemy;
class Shot;
class Time;

class SceneMain
{
public:
	SceneMain();
	virtual ~SceneMain();

	void Init();
	void Update();
	void Draw();

	void Death();	// 死亡時の処理
	void End();

	// シーンを終了させたいか
	bool IsSceneEnd() const;

	// ショットを追加する
	// 登録できなかった場合はfalseを返す
	// 登録できなかった場合は内部でpShot解放する
	bool AddShot(Shot* pShot);
	
	// 直前にこのステージを遊んでいたかどうかのフラグ
	bool JustStage1() const { return isSrage1; }

private:
	// 敵キャラクターの生成
	void CreateEnemyMozu();
	void CreateEnemyDeath();
	void CreateEnemyPump();

	// グラフィックのハンドル
	int m_gameScreenHandle;	// ゲームオーバー時画面

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

	bool isSrage1;	// 直前にプレイしたステージを判定するためのフラグ
					// ゲーム終了時にtrueにする

	// プレイヤー
	Player* m_pPlayer;
	// 弾
	Shot* m_pShot[kShotMax];
	// 背景
	Back* m_pBack;
	// 制限時間
	Time* m_pTime;

	// エネミー
	std::vector<MozueyeEnemy*> m_pMozueyeEnemy;
	std::vector<DeathYourEnemy*> m_pDeathYourEnemy;
	std::vector<PumpkinEnemy*> m_pPumpkinEnemy;
};