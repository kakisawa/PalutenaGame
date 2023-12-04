#pragma once
#include "Rect.h"
#include "Vec2.h"

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

	// 落下移動量
	float FallPowor;

	// グラフィックのハンドル
	int m_handle;
	// 表示位置
	Vec2 m_pos;
	// 当たり判定用の矩形
	Rect m_colRect;

	// プレイヤー反転フラグ
	bool isTurn;
	// プレイヤーが上を向いているかのフラグ
	bool isLookUp;
	// 移動中かどうかのフラグ
	bool isMove;
	// ジャンプ中かどうかのフラグ
	int isPushFlag;
	// ショットボタンが前フレームで押されたかどうかのフラグ
	bool isPrevshotFlag;

	// 弾の左方向フラグ
	bool LeftDir;
	// 弾の上方向フラグ
	bool TopDir;

	// プレイヤーの現在位置を取得する
	Vec2 GetPos() const { return m_pos; }
	// プレイヤーの当たり判定を取得する
	Rect GetColRect() const { return m_colRect; }
};

// プロトタイプ宣言
void InitPlayer(Player& player);
void UpdatePlayer(Player& player, Shot shot[], int shotArraySize);
void DrawPlayer(Player& player);