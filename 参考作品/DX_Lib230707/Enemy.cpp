#include "Enemy.h"
#include "DxLib.h"
#include <cassert>
#include "Game.h"

namespace
{
	// 移動速度
	constexpr float kSpeed = 8.0f;
}

Enemy::Enemy():
	m_handle(-1),
	m_width(0),
	m_height(0),
	m_isExist(false),
//	m_posX(0.0f),
//	m_posY(0.0f),
	m_moveY(0.0f)
{
	for (int i = 0; i < kPosLogFrame; i++)
	{
		m_posX[i] = 0.0f;
		m_posY[i] = 0.0f;
	}
}

Enemy::~Enemy()
{
}

void Enemy::Init()
{
	m_isExist = false;
}

void Enemy::Update()
{
	// 存在していない敵の処理は行わない
	if (!m_isExist) return;

	// 過去ログを一つずつずらしていく
	for (int i = kPosLogFrame - 1; i >= 1; i--)
	{
		m_posX[i] = m_posX[i - 1];
		m_posY[i] = m_posY[i - 1];
	}

#if 0
	m_posX[7] = m_posX[6];
	m_posX[6] = m_posX[5];
	m_posX[5] = m_posX[4];
	m_posX[4] = m_posX[3];
	m_posX[3] = m_posX[2];
	m_posX[2] = m_posX[1];
	m_posX[1] = m_posX[0];
#endif

//	m_posY += kSpeed;
	m_posY[0] += m_moveY;
	m_moveY += 1.0f;	// 移動速度をだんだん大きくする

	if (m_posY[0] > Game::kScreenHeight)
	{
		// 画面外に出た敵を再利用
	//	SetStartPos();
	
		// 画面外に出出たら消す
		m_isExist = false;
	}
}

void Enemy::Draw() const
{
	// 存在していない敵の表示は行わない
	if (!m_isExist) return;

	// ここに来た時にm_handleが-1だとグラフィックは絶対に表示されない(バグ)
	assert(m_handle !=-1);

	for (int i = 0; i < kPosLogFrame; i++)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - i * 32);
		DrawGraph(static_cast<int>(m_posX[i]), static_cast<int>(m_posY[i]), m_handle, false);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);	// 通常描画に戻す
}

void Enemy::SetGrahpHandle(int handle)
{
	m_handle = handle;
	// グラフィックのサイズを取得しておく
	GetGraphSize(m_handle, &m_width, &m_height);
}

void Enemy::Start()
{
	m_isExist = true;
	SetStartPos();	// ランダムな初期位置に設定
	m_moveY = 0.0f;
}

void Enemy::SetStartPos()
{
	// グラフィックの決定が行われていないと適切な位置が設定できない
	assert(m_handle != -1);
	// 画面上部ランダムな横位置に設定
	m_posX[0] = static_cast<float>(GetRand(Game::kScreenWidth - m_width));
	m_posY[0] = 0.0f - m_height;

	for (int i = 0; i < kPosLogFrame; i++)
	{
		m_posX[i] = m_posX[0];
		m_posY[i] = m_posY[0];
	}
}

float Enemy::GetLeft() const
{
	return m_posX[0];
}

float Enemy::GetTop() const
{
	return m_posY[0];
}

float Enemy::GetRight() const
{
	return m_posX[0] + m_width;
}

float Enemy::GetBottom() const
{
	return m_posY[0] + m_height;
}
