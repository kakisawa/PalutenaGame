#include "Shot.h"
#include "DxLib.h"
#include "Player.h"
#include "Game.h"

Shot::Shot():
	Se(0),
	x(0),
	y(0),
	m_isExist(false)
{
}

Shot::~Shot()
{
}

void Shot::init()
{
}

void Shot::Update()
{
	if (!m_isExist)	return;

	if (m_pPlayer->OutDir() == kDirRight)
	{
		m_pos.x += kShotSpeed;
		if (m_pos.x >= kScreenWidth)
		{
			m_isExist = false;
			return;
		}
	}
	else if (m_pPlayer->OutDir() == kDirLeft)
	{
		m_pos.x -= kShotSpeed;
		if (m_pos.x <= 0)
		{
			m_isExist = false;
			return;
		}
	}
	else if (m_pPlayer->OutDir() == kDirUp)
	{
		m_pos.y -= kShotSpeed;
		if (m_pos.y <= 0)
		{
			m_isExist = false;
			return;
		}
	}

	// 当たり判定の更新
	m_colRect.SetCenter(m_pos.x + kPlayerWidth * 0.5, m_pos.y + kPlayerHeight, kShotWidth, kShotHeight);
}

void Shot::Draw()
{
	if (!m_isExist) return;		// 存在するか

	DrawBox(m_pos.x + kPlayerWidth * 0.5, m_pos.y + kPlayerHeight * 0.5, m_pos.x + kShotWidth, m_pos.y + kShotHeight, GetColor(255, 255, 0),true);

#ifdef _DEBUG
	// 当たり判定の表示
	m_colRect.Draw(GetColor(255, 0, 0), false);
#endif
}

//void Shot::RightShot()
// {
//	// 右方向への弾の発射位置
//	// プレイヤーの右側,高さは半分
//	//x = m_Player->OutPos().x + kPlayerWidth;
//	//y = m_Player->OutPos().y + kPlayerHeight * 0.5;
//
//	x = m_pos.x+kPlayerWidth;
//	y = m_pos.y + kPlayerHeight * 0.5;
//}
//
//void Shot::LeftShot()
//{
//	// 左方向への弾の発射位置
//	// プレイヤーの左側,高さは半分
//	//x = m_Player->OutPos().x;
//	//y = m_Player->OutPos().y + kPlayerHeight * 0.5;
//
//	x = m_pos.x;
//	y = m_pos.y + kPlayerHeight * 0.5;
//}
//
//void Shot::UpShot()
//{
//	// 右方向への弾の発射位置
//	// プレイヤーの上側
//	//x = m_Player->OutPos().x + kPlayerWidth * 0.5;
//	//y = m_Player->OutPos().y;
//
//	x = m_pos.x+kPlayerWidth*0.5;
//	y = m_pos.y;
//}
//
void Shot::Start(Vec2 pos)
{
	m_isExist = true;

	m_pos = pos;

	if (m_pPlayer->OutDir()==kDirRight) // プレイヤーが右を向いている場合
	{
		m_pos.x += kShotSpeed;
	}
	else if(m_pPlayer->OutDir() == kDirLeft) // プレイヤーが左を向いている場合
	{
		m_pos.x = -kShotSpeed;
	}
	else if (m_pPlayer->OutDir() == kDirUp)
	{
		m_pos.y = -kShotSpeed;
	}
}
