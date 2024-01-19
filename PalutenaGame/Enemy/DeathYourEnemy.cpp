#include "DeathYourEnemy.h"
#include "DxLib.h"
#include "Game.h"

#include "SceneMain.h"

namespace
{
	// 移動速度
	constexpr float kSpeed = 3.0f;
}

DeathYourEnemy::DeathYourEnemy()
{
	EGraph = LoadGraph("data/Fairy2.png");		// 敵画像のロード

	W = 0;		// 敵画像サイズ
	H = 0;

	HP = 5;		// HP
	Atk = 30;	// 攻撃力
	Item;		// ドロップアイテム

	Gravity = 0.0f;		// 敵の初期重力
	isTurn = false;		// 右を向いているのfalseを挿入

	m_pos.x = 400;	// 敵の初期位置
	m_pos.y = 400;
}

DeathYourEnemy::~DeathYourEnemy()
{
	DeleteGraph(EGraph);	// 敵画像の削除
}

void DeathYourEnemy::Update()
{
	m_basePos += m_vec;
	m_pos += m_basePos;

	//当たり判定の更新
	UpdateCollision();

	// 敵のサイズを取得
	GetGraphSize(EGraph, &W, &H);

	if (m_pos.x > kScreenWidth + W / 2)
	{
		m_isExist = false;
	}

	// 移動量を持つようにする
	Vec2 move{ 0.0f,0.0f };

	// ベクトルの正規化
	move.normalize();
	// ベクトルの長さをkSpeedにする
	move *= kSpeed;
	// 座標とベクトルの足し算
	m_pos += move;
	

	// //敵移動
		// エネミーの座標を移動している方向に移動する
	if (isTurn == false)
	{
		//m_pos += move;
		m_pos.x += kSpeed;
	}
	else if (isTurn == true)
	{
		//m_pos -= move;
		m_pos.x -= kSpeed;
	}
	// エネミーが画面端からでそうになっていたら画面内の座標に戻してあげ、移動する方向も反転する
	if (m_pos.x > kScreenWidth - W)
	{
		m_pos.x = kScreenWidth - W;
		isTurn = true;
	}
	else if (m_pos.x < 0)
	{
		m_pos.x = 0;
		isTurn = false;
	}
}
