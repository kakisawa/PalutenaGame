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
	EGraph= LoadGraph("data/Fairy.png");

	HP = 2;		// HP
	Atk = 10;	// 攻撃力
	Item;		// ドロップアイテム

	Gravity = 0.0f;				// 敵の初期重力
	isTurn = false;				// 右を向いているのfalseを挿入

	m_pos.x = 300;
	m_pos.y = 300;
}

MozueyeEnemy::~MozueyeEnemy()
{
	DeleteGraph(EGraph);
}

void MozueyeEnemy::Update()
{
	EnemyBase::Update();

	m_basePos += m_vec;

	m_pos += m_basePos;


	//当たり判定の更新
	UpdateCollision();

	int width = 0;
	int height = 0;
	GetGraphSize(EGraph, &width, &height);

	if (m_pos.x > kScreenWidth + width / 2)
	{
		m_isExist = false;
	}

	// 移動量を持つようにする
	Vec2 move{ 0.0f,0.0f };

	// ベクトルの正規化
	move.normalize();
	// ベクトルの長さをkSpeedにする
	move *= kSpeed;

	//// 座標とベクトルの足し算
	//enemy += move;

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
}
