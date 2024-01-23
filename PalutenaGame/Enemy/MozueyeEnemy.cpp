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
	float kSpeed = 3.0f;
}

MozueyeEnemy::MozueyeEnemy()
{
	EGraph= LoadGraph("data/Fairy.png");

	HP = 2;		// HP
	Atk = 10;	// 攻撃力
	Item;		// ドロップアイテム

	Gravity = 0.0f;				// 敵の初期重力
	isTurn = false;				// 右を向いているのfalseを挿入

	m_pos.x = kScreenWidth * 0.3;
	m_pos.y = Ground - kHeight*0.5;
}

MozueyeEnemy::~MozueyeEnemy()
{
	DeleteGraph(EGraph);
}

void MozueyeEnemy::Update()
{
	EnemyBase::Update();

	//当たり判定の更新
	UpdateCollision();

	// 移動量を持つようにする
	Vec2 move{ 0.0f,0.0f };

	//敵移動
	if (isTurn == false)
	{
		if (kSpeed <= 40.0f)
		{
			kSpeed = 3.0f;
		}

		kSpeed += 5.0f;
		m_pos.x += kSpeed;
	}
	else if (isTurn == true)
	{
		m_pos.x -= kSpeed;
	}

	// ベクトルの正規化
	move.normalize();
	// ベクトルの長さをkSpeedにする
	move *= kSpeed;

	m_pos += move;

	// エネミーが画面端からでそうになっていたら画面内の座標に戻してあげ、移動する方向も反転する
	if (m_pos.x > kScreenWidth - kWidth)
	{
		m_pos.x = kScreenWidth - kWidth;
		isTurn = true;
	}
	else if (m_pos.x < 0)
	{
		m_pos.x = 0;
		isTurn = false;
	}
}
