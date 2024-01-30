#pragma once
#include "Vec2.h"
#include "Rect.h"

class SceneMain;
class SceneSecond;
class MozueyeEnemy;
class DeathYourEnemy;
class PumpkinEnemy;
class Shot;

// 向いている方向
enum Dir
{
	kDirFront,	// 正面
	kDirDown,	// 下
	kDirLeft,	// 左
	kDirRight,	// 右
	kDirUp,		// 上
};

// 弾を撃つ方向
enum ShotDir
{
	kShotDirLeft,	// 左
	kShotDirRight,	// 右
	kShotDirUp,		// 上
};

class Player
{
public:
	Player(SceneMain* pMain);
	~Player();

	void Init();
	void Update();
	void Draw();
	void End();

	void OnDamage_Mozu();	// プレイヤー被ダメ処理(敵_モズアイ)
	void OnDamage_Death();	// プレイヤー被ダメ処理(敵_死)
	void OnDamage_Pump();	// プレイヤー被ダメ処理(敵_パンプキン)
	void Death();		// プレイヤー死亡時処理

public:

	void SetHandle(int handle) { Graph = handle; }		// メンバー変数にアクセスする
	Rect GetColRect() const { return m_colRect; }		// プレイヤーの当たり判定を取得する
	Vec2 OutPos() const { return m_pos; }				// プレイヤーの座標を取得する
	bool PlayerDeath() const { return isDeath; }		// プレイヤーの生死状態を取得する

	ShotDir OutShotDir() const { return m_shotDir; }				// プレイヤーがどの方向を向いているかを取得する

	int OutHp = HP;			// プレイヤーHP
	
	// 敵の攻撃力を獲得するため
	void SetMozu(MozueyeEnemy* pMozu) { m_mozueyeEnemy = pMozu; }
	void SetDeath(DeathYourEnemy* pDeath) { m_dethYourEnemy = pDeath; }
	void SetPump(PumpkinEnemy* pPump) { m_pumpkinEnemy = pPump; }
private:
	SceneMain* m_pMain;
	MozueyeEnemy* m_mozueyeEnemy;
	DeathYourEnemy* m_dethYourEnemy;
	PumpkinEnemy* m_pumpkinEnemy;
	Shot* m_shot;

	int HP;		// プレイヤーの体力
	int Atk;	// プレイヤーの攻撃力
	int Score;	// プレイヤーが敵を倒した際に獲得したスコア
	int Graph;	// プレイヤーの画像
	int W, H;	// プレイヤーの画像サイズ
	int m_damageFrame;	// ダメージを受けてからのフレーム数
							// 普段は0で、当たった時にフレーム数を設定して
							// 以降毎フレーム減らしていく
	float Gravity;		// 重力
	float JumpPower;	// ジャンプ移動量
	float PlayerAnim;	// プレイヤーアニメーション

	Vec2 m_pos;			// 表示位置
	Dir m_dir;			// 向いている方向
	ShotDir m_shotDir;	
	Rect m_colRect;		// 当たり判定用の矩形

	bool isMove;		// プレイヤーが移動中かどうかのフラグ
	bool isJumpFlag;	// プレイヤーがジャンプ中かどうかのフラグ
	bool isAttack;		// プレイヤーが攻撃したかどうかのフラグ
	bool isDeath;		// プレイヤーが死亡したかどうかのフラグ
};