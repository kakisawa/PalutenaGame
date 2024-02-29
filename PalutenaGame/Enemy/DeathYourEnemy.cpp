#include "DeathYourEnemy.h"
#include "DxLib.h"
#include "Game.h"

#include <cassert>

namespace
{
	// エネミーのサイズ
	constexpr int kWidth = 63;
	constexpr float kHeight = 103.5f;

	// エネミーの画像元サイズ
	constexpr int SrcWidth = 28;
	constexpr int SrcHeight = 46;

	// 移動速度
	constexpr float kSpeed = 3.0f;
	// プレイヤーHP初期値
	constexpr int kHP = 1;
	// プレイヤーAtk初期値
	constexpr int kAtk = 10;

	// 所持スコア
	constexpr int kScore = 100;

	// 基本キャラアニメーション		// モーションのフレームごとに作り直す
	constexpr int DefFrame[] = { 0,1,2,3,4,5,6 };
	// 基本キャラアニメーションの1コマのフレーム数
	constexpr int DefAnimFrameNum = 7;
	// 基本キャラアニメーション1サイクルのフレーム数
	constexpr int DefFrameCycle = _countof(DefFrame) * DefAnimFrameNum;
}

DeathYourEnemy::DeathYourEnemy()
{
	m_graph = LoadGraph("data/Enemy/DeathYourEnemy.png");

	m_hp = kHP;			// HP
	m_atk = kAtk;			// 攻撃力
	m_score = kScore;		// 倒した際に得られるスコア

	m_gravity = 0.0f;		// 敵の初期重力
	m_isTurn = false;		// 右を向いているのfalseを挿入
	m_angle = 0;			// 敵の移動角度
	m_enemyAnim = 0;		// 敵のアニメーションの初期化
	m_damageFrame = 0;
}

DeathYourEnemy::~DeathYourEnemy()
{
	DeleteGraph(m_graph);
}

void DeathYourEnemy::Init(Player* pPlayer)
{
	m_pPlayer = pPlayer;
}

void DeathYourEnemy::Update()
{
	//m_basePos += m_vec;
	//m_pos += m_basePos;

	// ダメージ演出の進行
	m_damageFrame--;
	if (m_damageFrame < 0)	m_damageFrame = 0;

	//当たり判定の更新
	m_colRect.SetCenter(m_pos.x + kWidth / 2, m_pos.y + kHeight / 2,
		kWidth, kHeight);

	// 移動量を持つようにする
	Vec2 move{ 0.0f,0.0f };
	// ベクトルの正規化
	move.normalize();
	// ベクトルの長さをkSpeedにする
	move *= kSpeed;

	//敵移動
	if (m_isTurn == false)
	{
		m_angle++;
		float angle2 = m_angle * (DX_PI / 180.0f);
		m_pos.y = sin(angle2) * 200.0f + 550.0f;
		m_pos.x += kSpeed;

	}
	else if (m_isTurn == true)
	{
		m_angle++;
		float angle2 = m_angle * (DX_PI / 180.0f);
		m_pos.y = sin(angle2) * 200.0f + 320.0f;
		m_pos.x -= kSpeed;
	}
	// エネミーが画面端からでそうになっていたら画面内の座標に戻してあげ、移動する方向も反転する
	if (m_pos.x > kScreenWidth - kWidth)
	{
		m_pos.x = kScreenWidth - kWidth;
		m_isTurn = true;
	}
	else if (m_pos.x < 0)
	{
		m_pos.x = 0;
		m_isTurn = false;
	}

	// アニメーションフレーム
	m_enemyAnim++;
	if (m_enemyAnim >= DefFrameCycle)
	{
		m_enemyAnim = 0;
	}
}

void DeathYourEnemy::Draw()
{
	int EnemyFrame = m_enemyAnim / DefAnimFrameNum;
	int srcX = DefFrame[EnemyFrame] * SrcWidth;

	// 存在しない敵は描画しない
	if (!m_isExist) return;
	// グラフィックが設定されていなければ止まる
	assert(m_graph != -1);

	if (m_damageFrame % 4 >= 2) return;

	if (m_isTurn == false)
	{
			DrawRectExtendGraph(m_pos.x + kWidth, m_pos.y,
			m_pos.x, m_pos.y + kHeight,
			srcX, 0,
			SrcWidth, SrcHeight,
			m_graph, true);
	}
	else if (m_isTurn == true)
	{
		DrawRectExtendGraph(m_pos.x, m_pos.y,
			m_pos.x + kWidth, m_pos.y + kHeight,
			srcX , 0,
			SrcWidth, SrcHeight,
			m_graph, true);
	}
#ifdef _DEBUG
	// 当たり判定の表示
	m_colRect.Draw(GetColor(255, 0, 0), false);
#endif // DEBUG
}

void DeathYourEnemy::Start(float x, float y)
{
	m_isExist = true;

	m_pos.x =  x;
	m_pos.y = y;
}
