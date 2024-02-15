#pragma once
#include <vector>
#include "Vec2.h"

namespace
{
	// モズアイ最大出現数
	constexpr int MozuMax = 4;
	// 死最大出現数
	constexpr int DeathMax = 10;
	// かぼちゃ最大出現数
	constexpr int PumpMax = 3;

	// 画面内に同時に出せる弾の数
	constexpr int kShotMax = 30;

	// 何フレームおきに敵が登場するか
	constexpr int kEnemyInterval = 50;
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
class ColorManager;
class Pause;

class SceneMain
{
public:
	SceneMain();
	virtual ~SceneMain();

	void Init();
	void Update();
	void Draw();
	void End();

	// キャラクター系の描画
	void CharactorDraw();
	void StartDraw();
	void CoundownDraw();

	void DrawDoor();

	void Clear();	// クリア時の処理
	void Death();	// 死亡時の処理

	// ショットを追加する
		// 登録できなかった場合はfalseを返す
		// 登録できなかった場合は内部でpShot解放する
	bool AddShot(Shot* pShot);

	// シーンを終了させたいか
	bool IsSceneEnd() const;
	
	// 次どのステージに行くか
	bool ToGameOver() const;
	bool ToGameClear() const;

private:
	// 敵キャラクターの生成
	void CreateEnemyMozu();
	void CreateEnemyDeath();
	void CreateEnemyPump();

	void AppEnemyAnim();

	// グラフィックのハンドル
	int m_gameScreenHandle;	

	int m_playerHandle;		// プレイヤー
	int m_enemyHandle;		// 敵
	int m_backHandle;		// 背景
	int m_backHandle2;		// 背景(床)
	int m_door;				// 敵出現扉

	int m_explanation;		// 説明
	int m_key_A;
	int m_count1;			// カウント1
	int m_count2;			// カウント2
	int m_count3;			// カウント3

	// エネミー
	int m_mozueyeEnemy;			// モズアイ
	int m_deathYourEnemyGraph;	// お前たちの死
	int m_pumpkinEnemyGraph;	// パンプキン君

	int m_fadeAlpha;		// フェードイン、アウト
	int m_enemyInterval;	// 敵の登場間隔
	int m_startCount;		// ゲームスタートカウント

	int m_doorCount;		// 敵出現扉の描画カウント

	// シーン処理
	bool m_isStartFlag;		// ゲームが始まる前の説明
	bool m_isStartCountFlag;
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
	// 色
	ColorManager* m_pColorManager;
	// ポーズ
	Pause* m_pPause;
	// エネミー
	std::vector<MozueyeEnemy*> m_pMozueyeEnemy;
	std::vector<DeathYourEnemy*> m_pDeathYourEnemy;
	std::vector<PumpkinEnemy*> m_pPumpkinEnemy;
};