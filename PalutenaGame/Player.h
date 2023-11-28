#pragma once

// プロトタイプ宣言
struct Shot;

struct Player 
{
	// プレイヤーの初期位置
	int X;
	int Y;

	// プレイヤーの画像
	int Graph;
	// プレイヤーの画像サイズ
	int W;
	int H;

	// 移動速度
	float kSpeed;
	// 落下移動量
	float FallPowor;
	// ジャンプ移動量
	float JumpPowor;

	// ジャンプ中かどうかのフラグ
	int PushFlag;
	// ショットボタンが前フレームで押されたかどうかのフラグ
	bool PrevshotFlag;
};

// プロトタイプ宣言
void InitPlayer(Player& player);
void UpdatePlayer(Player& player, Shot shot[], int shotArraySize);
void DrawPlayer(Player& player);