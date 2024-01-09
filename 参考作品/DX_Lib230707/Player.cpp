#include "Player.h"
#include "DxLib.h"
#include <cassert>
#include "Game.h"

namespace
{
	// �ړ����x
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
		m_isTurn = false;	// ���Ɉړ�������ʏ�\��
		if (m_posX < 0.0f)
		{
			m_posX = 0.0f;
		}
	}
	if (pad & PAD_INPUT_RIGHT)
	{
		m_posX += kSpeed;
		m_isTurn = true;	// �E�Ɉړ������獶�E���]�\��
		if (m_posX > Game::kScreenWidth - m_width)
		{
			m_posX = Game::kScreenWidth - m_width;
		}
	}
}

void Player::Draw()
{
	// �����ɗ�������m_handle��-1���ƃO���t�B�b�N�͐�΂ɕ\������Ȃ�(�o�O)
	assert(m_handle != -1);

	if (m_isTurn)
	{
		DrawTurnGraph(static_cast<int>(m_posX), static_cast<int>(m_posY), m_handle, false);	// ���E���]�\��
	}
	else
	{
		DrawGraph(static_cast<int>(m_posX), static_cast<int>(m_posY), m_handle, false);
	}
}

void Player::SetGraphHandle(int handle)
{
	m_handle = handle;
	// �O���t�B�b�N�̕��ƍ������擾����
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
