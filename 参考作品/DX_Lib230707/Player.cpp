#include "Player.h"
#include "DxLib.h"
#include <cassert>
#include "Game.h"

namespace
{
	// 移動速度
	constexpr float kSpeed = 8.0f;
}


Player::Player() :
	m_handle(-1),
	m_width(0),
	m_height(0),
	m_posX(Game::kScreenWidth / 2),
	m_posY(600.0f),
	m_isTurn(false)
{
}

Player::~Player()
{
}

void Player::Init()
{
	m_posX = Game::kScreenWidth / 2;
	m_posY = 600.0f;
	m_isTurn = false;
}

void Player::Update()
{
	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if (pad & PAD_INPUT_LEFT)
	{
		m_posX -= kSpeed;
		m_isTurn = false;	// 左に移動したら通常表示
		if (m_posX < 0.0f)
		{
			m_posX = 0.0f;
		}
	}
	if (pad & PAD_INPUT_RIGHT)
	{
		m_posX += kSpeed;
		m_isTurn = true;	// 右に移動したら左右反転表示
		if (m_posX > Game::kScreenWidth - m_width)
		{
			m_posX = Game::kScreenWidth - m_width;
		}
	}
}

void Player::Draw()
{
	// ここに来た時にm_handleが-1だとグラフィックは絶対に表示されない(バグ)
	assert(m_handle != -1);

	if (m_isTurn)
	{
		DrawTurnGraph(static_cast<int>(m_posX), static_cast<int>(m_posY), m_handle, false);	// 左右反転表示
	}
	else
	{
		DrawGraph(static_cast<int>(m_posX), static_cast<int>(m_posY), m_handle, false);
	}
}

void Player::SetGraphHandle(int handle)
{
	m_handle = handle;
	// グラフィックの幅と高さを取得する
	GetGraphSize(m_handle, &m_width, &m_height);
}

float Player::GetLeft() const
{
	return m_posX;
}

float Player::GetTop() const
{
	return m_posY;
}

float Player::GetRight() const
{
	return m_posX + m_width;
}

float Player::GetBottom() const
{
	return m_posY + m_height;
}
