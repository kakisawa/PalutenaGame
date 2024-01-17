#pragma once
#include <vector>
#include "Vec2.h"

class Bg;
class ScenePause;
class Player;
class ShotBase;
class EnemyBase;
class RecoveryBase;

/// <summary>
/// ゲーム画面のクラス
/// </summary>
class SceneMain
{
public:
	SceneMain();
	~SceneMain();

	void Init();
	void End();
	void Update();
	void Draw();

	// ショットの追加
	bool AddShot(ShotBase* pShot);

	// アイテムドロップ
	void DropHpSmallRecovery(int enemyIndex);	// HP小回復
	void DropHpGreatRecovery(int enemyIndex);	// HP大回復
	void DropShotSmallRecovery(int enemyIndex);	// 弾小回復
	void DropShotGreatRecovery(int enemyIndex);	// 弾大回復
	void DropLifeRecovery(int enemyIndex);		// 残機回復
	void DropFullHpRecovery();					// HP全回復

	// アイテム2号の表示状態を取得
	bool GetIsExistLineMove() const {return m_isExistLineMove; }

	// シーン移動の取得
	bool IsSceneGameOver() const { return m_isSceneGameOver; }	// ゲームオーバー画面
	bool IsSceneClear() const { return m_isSceneClear; }		// クリア画面

private:
	// 敵キャラクターの生成
	void CreateMatasaburo(); // またさぶろうの生成

private:
	// グラフィックのハンドル
	int m_bgHandle;			// 背景
	int m_mapHandle;		// マップチップ
	int m_playerHandle;		// プレイヤー
	int m_enemyHandle;		// 敵
	// HPの回復バーの長さ
	int m_drawValue;

	// プレイヤーがE缶を取得したか true:取得した
	bool m_isGetFullHpRecovery;
	// アイテム2号が画面上に存在するか
	bool m_isExistLineMove;

	// シーン移動するか true:シーン移動する
	bool m_isSceneGameOver;	// ゲームオーバー画面に移動
	bool m_isSceneClear;	// クリア画面に移動

	// 背景
	Bg* m_pBg;
	// ポーズ画面
	ScenePause* m_pPause;
	// プレイヤー
	Player* m_pPlayer;
	// ショット
	std::vector<ShotBase*> m_pShot;
	// 敵
	std::vector<EnemyBase*> m_pEnemy;
	// 回復アイテム
	std::vector<RecoveryBase*> m_pRecovery;

	// プレイヤーの現在地
	Vec2 m_playerPos;
};

