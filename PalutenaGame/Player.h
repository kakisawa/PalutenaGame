#pragma once
#include "Vec2.h"
#include "Rect.h"

class SceneMain;
class Player
{
public:
	Player(SceneMain* pMain);
	~Player();

	void Init();
	void Update();
	void Draw();
	void End();

	void OnDamage();	// プレイヤー被ダメ処理
	void Death();		// プレイヤー死亡時処理

public:

	void SetHandle(int handle) { Graph = handle; }		// メンバー変数にアクセスする

	Rect GetColRect() const { return m_colRect; }		// プレイヤーの当たり判定を取得する

	int OutHp = HP;		// プレイヤーHPの引数
	bool PlayerDeath() const { return isDeath; }
private:

	SceneMain* m_pMain;

	int HP;		// プレイヤーの体力
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