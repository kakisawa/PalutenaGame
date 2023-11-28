#pragma once

// ショットの数
#define SHOT 20

struct Shot {

	// ショットの座標
	int X;
	int Y;

	// ショットの画像
	int Graph;

	// 弾が画面上に存在しているか保持する変数
	bool Flag;

	// ショットの画像サイズ
	int W;
	int H;
};

void InitShot(Shot& shot);
void UpdateShot(Shot& shot);
void DrawShot(Shot& shot);



// x=16
// y=8