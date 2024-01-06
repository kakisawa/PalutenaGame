#include "DxLib.h"
#include "MozueyeEnemy.h"
#include "Player.h"
#include "Game.h"

namespace 
{
	// エネミーのサイズ
	constexpr int kWidth = 32;
	constexpr int kHeight = 32;

	// 移動速度
	constexpr float kSpeed = 3.0f;
}

MozueyeEnemy::MozueyeEnemy()
{
	HP = 1;		// HP
	Atk = 10;	// 攻撃力
	Item;		// ドロップアイテム

	enemy.x = kScreenWidth / 3;		// 敵座標
	enemy.y = 400;
	Gravity = 0.0f;				// 敵の初期重力
	isTurn = false;				// 右を向いているのfalseを挿入
}

void MozueyeEnemy::Init()
{
	EGraph = LoadGraph("data/Fairy.png");
}

void MozueyeEnemy::Update()
{
	// 移動量を持つようにする
	Vec2 move{ 0.0f,0.0f };

	// ベクトルの正規化
	move.normalize();
	// ベクトルの長さをkSpeedにする
	move *= kSpeed;
	// 座標とベクトルの足し算
	enemy += move;
	

	// エネミーの座標を移動している方向に移動する
	if (isTurn == false)
	{
		enemy.x += kSpeed;
	}
	else if (isTurn == true)
	{
		enemy.x -= kSpeed;
	}
	// エネミーが画面端からでそうになっていたら画面内の座標に戻してあげ、移動する方向も反転する
	if (enemy.x > kScreenWidth - kWidth)
	{
		enemy.x = kScreenWidth - kWidth;
		isTurn = true;
	}
	else if (enemy.x < 0)
	{
		enemy.x = 0;
		isTurn = false;
	}


	// 当たり判定の更新
	m_colRect.SetCenter(enemy.x + kWidth / 2, enemy.y + kHeight / 2, kWidth, kHeight);
}

void MozueyeEnemy::Draw()
{
	if (isTurn == false)
	{
		DrawGraph(enemy.x, enemy.y, EGraph, true);
	}
	else if (isTurn == true)
	{
		DrawTurnGraph(enemy.x, enemy.y, EGraph, true);
	}

#ifdef _DEBUG
	// 当たり判定の表示
	m_colRect.Draw(GetColor(0, 0, 255), false);
#endif
}

void MozueyeEnemy::Damage(int damage)
{
	// HPを減らす
	HP -= damage;
	// もしHPが0以下なら死亡処理をする
	if (HP <= 0) 
	{
		Death();
	}
}
