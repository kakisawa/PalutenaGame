#include "PumpkinEnemy.h"
#include "DxLib.h"
#include "Game.h"

namespace
{
	// エネミーのサイズ
	constexpr int kWidth = 16;
	constexpr int kHeight = 22;

	// 移動速度
	constexpr float kSpeed = 3.0f;
}

PumpkinEnemy::PumpkinEnemy()
{
	HP = 1;		// HP
	Atk = 10;	// 攻撃力
	Item;		// ドロップアイテム
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		enemy[i].x = kScreenWidth / 5;		// 敵座標
		enemy[i].y = 400 - i * kHeight;
	}


	Gravity = 0.0f;				// 敵の初期重力
	isTurn = false;				// 右を向いているのfalseを挿入
}

void PumpkinEnemy::Init()
{
}

void PumpkinEnemy::Update()
{// 移動量を持つようにする
	Vec2 move{ 0.0f,0.0f };

	// ベクトルの正規化
	move.normalize();
	// ベクトルの長さをkSpeedにする
	move *= kSpeed;
	// 座標とベクトルの足し算
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		enemy[ENEMY_NUM] += move;
	}

	// 敵移動
	//for (int i = 0; i < ENEMY_NUM; i++)
	//{
	//	// エネミーの座標を移動している方向に移動する
	//	if (isTurn == false)
	//	{
	//		enemy[i].x += kSpeed;
	//	}
	//	else if (isTurn == true)
	//	{
	//		enemy[i].x -= kSpeed;
	//	}
	//	// エネミーが画面端からでそうになっていたら画面内の座標に戻してあげ、移動する方向も反転する
	//	if (enemy[i].x > kScreenWidth - kWidth)
	//	{
	//		enemy[i].x = kScreenWidth - kWidth;
	//		isTurn = true;
	//	}
	//	else if (enemy[i].x < 0)
	//	{
	//		enemy[i].x = 0;
	//		isTurn = false;
	//	}
	//}

	for (int i = 0; i < ENEMY_NUM; i++)
	{
		// 当たり判定の更新
		m_colRect[i].SetCenter(enemy[i].x + kWidth / 2, enemy[i].y + kHeight / 2, kWidth, kHeight);
	}
}

void PumpkinEnemy::Draw()
{
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		if (isTurn == false)
		{
			DrawGraph(enemy[i].x, enemy[i].y, EGraph, true);
		}
		else if (isTurn == true)
		{
			DrawTurnGraph(enemy[i].x, enemy[i].y, EGraph, true);
		}
	}

#ifdef _DEBUG
	// 当たり判定の表示
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		m_colRect[i].Draw(GetColor(0, 0, 255), false);
	}
#endif
}

void PumpkinEnemy::Damage(int damage)
{
	// HPを減らす
	HP -= damage;
	// もしHPが0以下なら死亡処理をする
	if (HP <= 0)
	{
		Death();
	}
}
