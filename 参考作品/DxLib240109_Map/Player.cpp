#include "DxLib.h"
#include "Player.h"
#include "Map.h"

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

		m_x += m_moveX;
		// 横から当たったかをチェックする
		Rect chipRect;	// 当たったマップチップの矩形
		if (m_pMap->IsCol(getRect(), chipRect))
		{
			// 横からぶつかった場合の処理
			m_x -= m_moveX;

			// 左右どちらからあたったかをデバッグ表示
			if (m_moveX > 0.0f)	// プレイヤーが右方向に移動している
			{
				//printfDx("プレイヤーの右側がマップにぶつかった\n");
				m_x = chipRect.left - kWidth / 2 - 1;	// マップチップの左側丁度にぶつからない位置に補正
			}
			else if (m_moveX < 0.0f)
			{
				//printfDx("プレイヤーの左側がマップにぶつかった\n");
				m_x = chipRect.right + kWidth / 2 + 1;	// マップチップの右側丁度にぶつからない位置に補正
			}
		}
		m_y += m_moveY;
		// 横からあたったかをチェックする
		if (m_pMap->IsCol(getRect(),chipRect))
		{
			if (m_moveY > 0.0f)	// プレイヤーが下方向に移動している
			{
				// 着地
				m_y = chipRect.top - 1;
				m_moveY = 0.0f;
				m_isJump = false;
			}
			else if (m_moveY < 0.0f)	// プレイヤーが上方向に移動している
			{
				m_y = chipRect.bottom+kHeight+1;	// めり込まない位置に戻す
				m_moveY *= -1.0f;	// 上方向への加速を下方に変換
			}
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

		m_x += m_moveX;
		// 横から当たったかをチェックする
		Rect chipRect;	// 当たったマップチップの矩形
		if (m_pMap->IsCol(getRect(), chipRect))
		{
			// 横からぶつかった場合の処理
			m_x -= m_moveX;

			// 左右どちらからあたったかをデバッグ表示
			if (m_moveX > 0.0f)	// プレイヤーが右方向に移動している
			{
				//printfDx("プレイヤーの右側がマップにぶつかった\n");
				m_x = chipRect.left - kWidth / 2-1;	// マップチップの左側丁度にぶつからない位置に補正
			}
			else if (m_moveX < 0.0f)
			{
				//printfDx("プレイヤーの左側がマップにぶつかった\n");
				m_x = chipRect.right + kWidth / 2 + 1;	// マップチップの右側丁度にぶつからない位置に補正
			}
		}

		m_y += m_moveY;
		// 縦から当たったかをチェックする
		if (m_pMap->IsCol(getRect(),chipRect))
		{
			if (m_moveY > 0.0f)	// プレイヤーが下方向に移動している
			{
				// 地面に立っている何もしない
				m_y = chipRect.top - 1;
			}
			else if (m_moveY < 0.0f)	// プレイヤーが上方向に移動している
			{
				m_y = chipRect.bottom + kHeight + 1;	// めり込まない位置に戻す
				m_moveY *= -1.0f;	// 上方向への加速を下方に変換

				//printfDx("プレイヤーの上側がマップにぶつかった\n");
			}
		}
		else
		{
			// 地面にすらぶつかっていない
			m_isJump = true;
		}

		// 接地していない
		if (!m_pMap->IsCol(getRect(),chipRect))
		{
			m_isJump = true;
		}
	}
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
	return m_y;
}

Rect Player::getRect()
{
	Rect rect;
	rect.top = GetTop();
	rect.bottom = GetBottom();
	rect.left = GetLeft();
	rect.right = GetRight();

	return rect;
}
