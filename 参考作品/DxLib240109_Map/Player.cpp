#include "Player.h"
#include "Map.h"
#include "DxLib.h"

// プラットフォーマータイプのゲームはプレイヤーの横中心縦足元をposにした方がやりやすい

namespace
{
	constexpr int kWidth = 24;
	constexpr int kHeight = 24;

	// 重力
	constexpr float kGravity = 0.5f;
	// ジャンプ力
	constexpr float kJumpAcc = -8.0f;
}

Player::Player() :
	m_isJump(false),
	m_x(320.0f),
	m_y(240.0f),
	m_moveX(0.0f),
	m_moveY(0.0f)
{
}

Player::~Player()
{
}

void Player::Update()
{
	// 上下左右キーでプレイヤー移動
	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	if (m_isJump)
	{
		// 空中にいる場合の処理

		// 毎フレーム下方向に加速する(重力の影響を受ける)
		m_moveY += kGravity;

		// 地面に着地する処理
		if (m_pMap->IsColPlayer())
		{
			m_y -= m_moveY;
			m_moveY = 0.0f;
			m_isJump = false;
		}
	}
	else
	{
		// 地面に立っている場合の処理
		m_moveX = 0.0f;
		if (pad & PAD_INPUT_RIGHT)
		{
			m_moveX = 4.0f;
		}
		if (pad & PAD_INPUT_LEFT)
		{
			m_moveX = -4.0f;
		}
		// ジャンプ
		if (pad & PAD_INPUT_1)
		{
			m_moveY = kJumpAcc;
			m_isJump = true;
		}
		// 接地していない
		if (!m_pMap->IsColPlayer())
		{
			m_isJump = true;
		}
	}

	m_x += m_moveX;
	m_y += m_moveY;
}

void Player::Draw()
{
	unsigned int color = 0xff0000;
	if (m_pMap->IsColPlayer())	color = 0xffff00;

	// 足元座標を左上座標に変換
	int x = static_cast<int>(m_x - kWidth / 2);
	int y = static_cast<int>(m_y - kHeight);

	// スクロール量を反映
	x -= m_pMap->GetScrollX();
	y -= m_pMap->GetScrollY();
	DrawBox(x, y, x + kWidth, y + kHeight, color, true);


}

float Player::GetLeft()
{
	return m_x - kWidth / 2;
}
float Player::GetRight()
{
	return m_x + kWidth / 2;
}
float Player::GetTop()
{
	return m_y - kHeight;
}
float Player::GetBottom()
{
	return m_y + kHeight;
}