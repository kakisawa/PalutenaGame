#pragma once
#include <vector>
#include "Vec2.h"

namespace
{
	// モズアイ出現数
	constexpr int MozuSecondMax = 5;	// 17
	// 死出現数
	constexpr int DeathSecondMax = 2;	// 3
	// かぼちゃ出現数
	constexpr int PumpSecondMax = 3;	// 10仮、覚えてない

	// 画面内に同時に出せる弾の数
	constexpr int kShotSecondMax = 30;

	// 何フレームおきに敵が登場するか
	constexpr int kEnemySecondInterval = 60;
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

class SceneSecond
{
public:
	SceneSecond();
	virtual ~SceneSecond();

	void Init();
	void Update();
	void Draw();
	void End();

	void CharactorDraw();

	void Clear();	// クリア時の処理
	void Death();	// 死亡時の処理

	// シーンを終了させたいか
	bool IsSceneEnd() const;

	// 次どのステージに行くか
	bool IsToGameOver() const;
	bool IsToGameClear() const;

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

	bool m_isToGameOver;		// ステージセレクト画面に行くか
	bool m_isToGameClear;		// 説明シーンに行くか 

	// プレイヤー
	Player* m_pPlayer;
	// 弾
	Shot* m_pShot[kShotSecondMax];
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

