#include "DeathYourEnemy.h"
#include "DxLib.h"
#include "Game.h"

namespace
{
	// エネミーのサイズ
	constexpr int kWidth = 26;
	constexpr int kHeight = 46;

	// 移動速度
	constexpr float kSpeed = 3.0f;
}

DeathYourEnemy::DeathYourEnemy()
{
	EGraph = LoadGraph("data/Fairy2.png");

	HP = 10;		// HP
	Atk = 10;	// 攻撃力

	Gravity = 0.0f;				// 敵の初期重力
	isTurn = false;				// 右を向いているのfalseを挿入
	angle = 0;					// 敵の移動角度

	m_pos.x = kScreenWidth * 0.7;
	m_pos.y = Ground - kHeight * 0.5;
}

DeathYourEnemy::~DeathYourEnemy()
{
	DeleteGraph(EGraph);
}

void DeathYourEnemy::Init()
{
}

void DeathYourEnemy::Update()
{
	EnemyBase::Update();

	//m_basePos += m_vec;
	//m_pos += m_basePos;

	//当たり判定の更新
	UpdateCollision();

	// 移動量を持つようにする
	Vec2 move{ 0.0f,0.0f };

	// ベクトルの正規化
	move.normalize();
	// ベクトルの長さをkSpeedにする
	move *= kSpeed;


	//敵移動
	if (isTurn == false)
	{
		angle++;
		float angle2 = angle * (DX_PI / 180);
		m_pos.y = sin(angle2) * 200 + 320;
		m_pos.x += kSpeed;

	}
	else if (isTurn == true)
	{
		angle++;
		float angle2 = angle * (DX_PI / 180);
		m_pos.y = sin(angle2) * 200 + 320;
		m_pos.x -= kSpeed;
	}
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

void DeathYourEnemy::Start()
{
	m_isExist = true;
}
