#pragma once
#include "Vec2.h"
class Player
{
public:

	// 向いている方向
	enum Dir
	{
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
	int Graph;
	// プレイヤーの画像サイズ
	int W, H;

	// 重力
	float Gravity;
	// 落下移動量
	float FallPowor;
	// ジャンプ移動量
	float JumpPower;
	// 表示位置
	Vec2 m_pos;
	// 向いている方向
	Dir m_dir;

public:
	// プレイヤー反転フラグ
	bool isTurn;
	// 移動中かどうかのフラグ
	bool isMove;
	// ジャンプ中かどうかのフラグ
	int isPushFlag;
};

