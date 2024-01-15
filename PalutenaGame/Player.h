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

public:

	// メンバー変数にアクセスする
	void SetHandle(int handle) { Graph = handle; }
	// プレイヤーの当たり判定を取得する
	Rect GetColRect() const { return m_colRect; }
	// プレイヤーの体力
	int PlayerHP;

	// プレイヤーがダメージを受けた
	void OnDamage();

private:

	SceneMain* m_pMain;

	// プレイヤーの画像
	int Graph;		
	// プレイヤーの画像サイズ
	int W, H;

	int m_damageFrame;		// ダメージを受けてからのフレーム数
							// 普段は0で、当たった時にフレーム数を設定して
							// 以降毎フレーム減らしていく

	// 向いている方向
	enum Dir
	{
		kDirFront,	// 正面
		kDirDown,	// 下
		kDirLeft,	// 左
		kDirRight,	// 右
		kDirUp,		// 上
	};

	// 表示位置
	Vec2 m_pos;
	// 向いている方向
	Dir m_dir;
	// プレイヤーアニメーション
	float PlayerAnim;
	// enumでboolを変える
	// 重力
	float Gravity;
	// ジャンプ移動量
	float JumpPower;

	// 当たり判定用の矩形
	Rect m_colRect;

	// プレイヤーが移動中かどうかのフラグ
	bool isMove;
	// ジャンプ中かどうかのフラグ
	bool isJumpFlag;
	// プレイヤーが攻撃したかどうかのフラグ
	bool isAttack;
};