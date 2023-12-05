#pragma once
#include "Rect.h"
#include "Vec2.h"
#include "Game.h"

// プロトタイプ宣言
struct Shot;

class Player 
{
public:
	Player();
	~Player();

	void Init();
	void Update(Shot shotArray[], int shotArraySize);
	void Draw();

	// 当たり判定用の矩形
	Rect m_colRect;
	// プレイヤーの現在位置を取得する
	Vec2 GetPos() const { return m_pos; }
	// プレイヤーの当たり判定を取得する
	Rect GetColRect() const { return m_colRect; }

private:
	// プレイヤーの画像
	int Graph;
	// プレイヤーの画像サイズ
	int W;
	int H;

	// 落下移動量
	float FallPowor;
	// ジャンプ移動量
	float JumpPower;

	// グラフィックのハンドル
	int m_handle;
	// 表示位置
	Vec2 m_pos;

public:

	// プレイヤー反転フラグ
	bool isTurn;
	// プレイヤーが上を向いているかのフラグ
	bool isLookUp;
	// プレイヤーがしゃがんでいるかのフラグ
	bool isSquat;
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
};