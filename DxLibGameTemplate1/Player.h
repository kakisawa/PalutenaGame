#pragma once
#include "Vec2.h"
#include "Rect.h"
class Player
{
public:

	// 向いている方向
	enum Dir
	{
		kDirFront,	// 正面
		kDirDown,	// 下
		kDirLeft,	// 左
		kDirRight,	// 右
		kDirUp,		// 上
	};


	Player();
	~Player();

	void Init();
	void Update();
	void Draw();

private:
	// プレイヤーの画像
	int Graph;		// 通常待機
	// プレイヤーの画像サイズ
	int W, H;
	// プレイヤーの体力
	int HP;

	// 表示位置
	Vec2 m_pos;
	// 向いている方向
	Dir m_dir;
	// 待機状態アニメーション
	float IdleAnimation;
	// 左右移動アニメーション
	float RunAnimation;
	// しゃがみアニメーション
	float SquatAnimation;

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
};

