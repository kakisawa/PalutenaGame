#include "DeathYourEnemy.h"
#include "DxLib.h"
#include "Game.h"

#include <cassert>

namespace
{
	// エネミーのサイズ
	constexpr int kWidth = 42;
	constexpr int kHeight = 69;

	// エネミーの画像元サイズ
	constexpr int SrcWidth = 28;
	constexpr int SrcHeight = 46;

	// 移動速度
	constexpr float kSpeed = 3.0f;

	// 基本キャラアニメーション		// モーションのフレームごとに作り直す
	constexpr int DefFrame[] = { 0,1,2,3,4,5,6 };
	// 基本キャラアニメーションの1コマのフレーム数
	constexpr int DefAnimFrameNum = 7;
	// 基本キャラアニメーション1サイクルのフレーム数
	constexpr int DefFrameCycle = _countof(DefFrame) * DefAnimFrameNum;
}

DeathYourEnemy::DeathYourEnemy()
{
	EGraph = LoadGraph("data/Enemy/DeathYourEnemy.png");

	HP = 10;		// HP
	Atk = 10;	// 攻撃力
	Score = 100;	// 倒した際に得られるスコア

	Gravity = 0.0f;				// 敵の初期重力
	isTurn = false;				// 右を向いているのfalseを挿入
	angle = 0;					// 敵の移動角度
	EnemyAnim = 0;				// 敵のアニメーションの初期化
}

DeathYourEnemy::~DeathYourEnemy()
{
	DeleteGraph(EGraph);
}

void DeathYourEnemy::Init()
{
	HP = 10;		// HP
	Atk = 10;	// 攻撃力

	Gravity = 0.0f;				// 敵の初期重力
	isTurn = false;				// 右を向いているのfalseを挿入
	angle = 0;					// 敵の移動角度
	EnemyAnim = 0;				// 敵のアニメーション初期化
}

void DeathYourEnemy::Update()
{
	//m_basePos += m_vec;
	//m_pos += m_basePos;

	//当たり判定の更新
	m_colRect.SetCenter(m_pos.x + kWidth / 2, m_pos.y + kHeight / 2, kWidth, kHeight);

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

	// アニメーションフレーム
	EnemyAnim++;
	if (EnemyAnim >= DefFrameCycle)
	{
		EnemyAnim = 0;
	}
}

void DeathYourEnemy::Draw()
{
	int EnemyFrame = EnemyAnim / DefAnimFrameNum;
	int srcX = DefFrame[EnemyFrame] * SrcWidth;

	// 存在しない敵は描画しない
	if (!m_isExist) return;
	// グラフィックが設定されていなければ止まる
	assert(EGraph != -1);

	if (m_damageFrame % 4 >= 2) return;

	if (isTurn == false)
	{
			DrawRectExtendGraph(m_pos.x + kWidth, m_pos.y,
			m_pos.x, m_pos.y + kHeight,
			srcX+2, 0,
			SrcWidth, SrcHeight,
			EGraph, true);
	}
	else if (isTurn == true)
	{
		DrawRectExtendGraph(m_pos.x, m_pos.y,
			m_pos.x + kWidth, m_pos.y + kHeight,
			srcX+2, 0,
			SrcWidth, SrcHeight,
			EGraph, true);
	}
#ifdef _DEBUG
	// 当たり判定の表示
	m_colRect.Draw(GetColor(255, 0, 0), false);
#endif // DEBUG
}

void DeathYourEnemy::Start(float x, float y)
{
	m_isExist = true;

	m_pos.x = x;
	m_pos.y = y;

}
