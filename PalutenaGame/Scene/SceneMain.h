#pragma once
#include <vector>
#include "Vec2.h"

namespace
{
	constexpr int MozuMax = 4;			// モズアイ最大出現数
	constexpr int DeathMax = 10;		// 死最大出現数
	constexpr int PumpMax = 3;			// かぼちゃ最大出現数
	constexpr int kShotMax = 30;		// 画面内に同時に出せる弾の数
	constexpr int kEnemyInterval = 50;	// 何フレームおきに敵が登場するか
}

// クラス宣言
class Player;
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

	void BgDraw();			// 背景の描画
	void DrawDoor();		// 敵の出現位置扉描画
	void CharactorDraw();	// キャラクター系の描画
	void StartDraw();		// ゲーム開始前の説明描画
	void CoundownDraw();	// 説明後ゲーム開始カウントダウン描画

	void Clear();	// クリア時の処理
	void Death();	// 死亡時の処理

	bool AddShot(Shot* pShot);	// ショットを追加する

	bool IsSceneEnd() const;	// シーンを終了させるか
	bool IsToGameOver() const;	// ゲーム終了時ゲームオーバーシーンに向かう
	bool IsToGameClear() const;	// ゲームクリア時ゲームクリアシーンに向かう

private:
	// 敵キャラクターの生成
	void CreateEnemyMozu();	// モズアイ
	void CreateEnemyDeath();// 死
	void CreateEnemyPump();	// パンプキン

	int m_gameScreenHandle;	// ゲーム画面サイズのグラフィックデータ
	int m_enemyHandle;		// 敵
	int m_backHandle;		// 背景
	int m_backGroundHandle;	// 背景(床)
	int m_door;				// 敵出現扉

	int m_explanation;		// 説明
	int m_key_A;			//「Aボタンで決定」グラフ
	int m_count1;			// カウント1
	int m_count2;			// カウント2
	int m_count3;			// カウント3

	int m_mozueyeEnemy;			// モズアイ
	int m_deathYourEnemyGraph;	// 死
	int m_pumpkinEnemyGraph;	// パンプキン

	int m_fadeAlpha;		// フェードイン、アウト
	int m_enemyInterval;	// 敵の登場間隔
	int m_startCount;		// ゲームスタートカウント
	int m_doorCount;		// 敵出現扉の描画カウント

	bool m_isStartFlag;		// ゲームが始まる前の説明フラグ
	bool m_isStartCountFlag;// 説明後ゲーム開始カウントフラグ
	bool m_isSceneEnd;		// シーンフラグ

	bool m_isToGameOver;		// ゲームオーバー画面に行くかのフラグ
	bool m_isToGameClear;		// ゲームクリア画面に行くかのフラグ

	// プレイヤー
	Player* m_pPlayer;
	// 弾
	Shot* m_pShot[kShotMax];
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