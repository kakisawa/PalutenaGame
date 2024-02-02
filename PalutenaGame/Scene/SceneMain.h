#pragma once
#include <vector>
#include "Vec2.h"

namespace
{
	// モズアイ最大出現数
	constexpr int MozuMax = 7;
	// 死最大出現数
	constexpr int DeathMax = 5;
	// かぼちゃ最大出現数
	constexpr int PumpMax = 3;

	// 画面内に同時に出せる弾の数
	constexpr int kShotMax = 30;

	// 何フレームおきに敵が登場するか
	constexpr int kEnemyInterval = 60;
}

// クラス宣言
class Player;
class Back;
class MozueyeEnemy;
class DeathYourEnemy;
class PumpkinEnemy;
class Shot;
class Time;
class SoundManager;

class SceneMain
{
public:
	SceneMain();
	virtual ~SceneMain();

	void Init();
	void Update();
	void Draw();

	void Clear();	// クリア時の処理
	void Death();	// 死亡時の処理
	void End();		


	// シーンを終了させたいか
	bool IsSceneEnd() const;
	// ↑これはシーン終了時のフラグ
	// クリアとゲームオーバーは別にした方がいいかもしれない。

	// 次どのステージに行くか
	bool ToGameOver() const;
	bool ToGameClear() const;

	// ショットを追加する
	// 登録できなかった場合はfalseを返す
	// 登録できなかった場合は内部でpShot解放する
	bool AddShot(Shot* pShot);
	
private:
	// 敵キャラクターの生成
	void CreateEnemyMozu();
	void CreateEnemyDeath();
	void CreateEnemyPump();

	// グラフィックのハンドル
	int m_gameScreenHandle;	

	int m_playerHandle;		// プレイヤー
	int m_enemyHandle;		// 敵
	int m_backHandle;		// 背景

	// エネミー
	int m_mozueyeEnemy;			// モズアイ
	int m_deathYourEnemyGraph;	// お前たちの死
	int m_pumpkinEnemyGraph;	// パンプキン君

	int m_fadeAlpha;		// フェードイン、アウト
	int m_enemyInterval;	// 敵の登場間隔

	// シーン処理
	bool m_isSceneEnd;		// シーンを終了する時trueにする

	bool isToGameOver;		// ゲームオーバー画面に行くか
	bool isToGameClear;		// ゲームクリア画面に行くか 

	// プレイヤー
	Player* m_pPlayer;
	// 弾
	Shot* m_pShot[kShotMax];
	// 背景
	Back* m_pBack;
	// 制限時間
	Time* m_pTime;
	// SE/BGM
	SoundManager* m_pSoundManager;
	// エネミー
	std::vector<MozueyeEnemy*> m_pMozueyeEnemy;
	std::vector<DeathYourEnemy*> m_pDeathYourEnemy;
	std::vector<PumpkinEnemy*> m_pPumpkinEnemy;
};