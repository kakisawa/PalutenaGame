#pragma once
#include "Vec2.h"
#include "Rect.h"

class SceneMain;
class MozueyeEnemy;
class DeathYourEnemy;
class PumpkinEnemy;

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

	int OutHp = HP;			// プレイヤーHP
	Vec2 OutPos() const { return m_pos; }	// プレイヤー座標
	bool PlayerDeath() const { return isDeath; }



	// 敵の攻撃力を獲得するため
	void SetMozu(MozueyeEnemy* pMozu) { m_mozueyeEnemy = pMozu; }
	void SetDeath(DeathYourEnemy* pDeath) { m_dethYourEnemy = pDeath; }
	void SetPump(PumpkinEnemy* pPump) { m_pumpkinEnemy = pPump; }
private:
	SceneMain* m_pMain;
	MozueyeEnemy* m_mozueyeEnemy;
	DeathYourEnemy* m_dethYourEnemy;
	PumpkinEnemy* m_pumpkinEnemy;

	int HP;		// プレイヤーの体力
	int Atk;	// プレイヤーの攻撃力
	int Graph;	// プレイヤーの画像
	int W, H;	// プレイヤーの画像サイズ
	int m_damageFrame;	// ダメージを受けてからのフレーム数
							// 普段は0で、当たった時にフレーム数を設定して
							// 以降毎フレーム減らしていく
	float Gravity;		// 重力
	float JumpPower;	// ジャンプ移動量
	float PlayerAnim;	// プレイヤーアニメーション

	// 向いている方向
	enum Dir
	{
		kDirFront,	// 正面
		kDirDown,	// 下
		kDirLeft,	// 左
		kDirRight,	// 右
		kDirUp,		// 上
	};

	Vec2 m_pos;			// 表示位置
	Dir m_dir;			// 向いている方向
	Rect m_colRect;		// 当たり判定用の矩形

	bool isMove;		// プレイヤーが移動中かどうかのフラグ
	bool isJumpFlag;	// プレイヤーがジャンプ中かどうかのフラグ
	bool isAttack;		// プレイヤーが攻撃したかどうかのフラグ
	bool isDeath;		// プレイヤーが死亡したかどうかのフラグ
};