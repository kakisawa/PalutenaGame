#include "Enemy.h"
#include "Map.h"
#include "DxLib.h"

// プラットフォーマータイプのゲームはプレイヤーの横中心縦足元をposにした方がやりやすい

namespace
{
	constexpr int kWidth = 24;
	constexpr int kHeight = 24;
}

Enemy::Enemy() :
	m_x(400.0f),
	m_y(300.0f)
{
}

void Enemy::Update()
{
}

void Enemy::Draw()
{
	// 足元座標を左上座標に変換
	int x = static_cast<int>(m_x - kWidth / 2);
	int y = static_cast<int>(m_y - kHeight);

	// スクロール量を反映
	x -= m_pMap->GetScrollX();
	y -= m_pMap->GetScrollY();
	DrawBox(x, y, x + kWidth, y + kHeight, 0x0000ff, true);
}
