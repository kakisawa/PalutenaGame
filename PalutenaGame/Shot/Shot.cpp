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
	x = m_pos.x;
	y = m_pos.y;

	dir = m_pPlayer->OutShotDir();
}

void Shot::Update()
{
	if (!m_isExist)	return;
	
	if (dir == kShotDirRight)
	{
		m_pos.x += kShotSpeed;
		if (m_pos.x >= kScreenWidth)
		{
			m_isExist = false;
			return;
		}
	}
	else if (dir == kShotDirLeft)
	{
		m_pos.x -= kShotSpeed;
		if (m_pos.x <= 0)
		{
			m_isExist = false;
			return;
		}
	}
	else if (dir == kShotDirUp)
	{
		m_pos.y -= kShotSpeed;
		if (m_pos.y <= 0)
		{
			m_isExist = false;
			return;
		}
	}

	// “–‚½‚è”»’è‚ÌXV
	m_colRect.SetCenter(m_pos.x + kPlayerWidth * 0.5, m_pos.y + kPlayerHeight * 0.5, kShotWidth, kShotHeight);
}

void Shot::Draw()
{
	if (!m_isExist) return;		// ‘¶Ý‚·‚é‚©

	DrawBox(m_pos.x + kPlayerWidth * 0.5, m_pos.y + kPlayerHeight * 0.5, m_pos.x + kShotWidth, m_pos.y + kShotHeight, GetColor(255, 255, 0),true);

#ifdef _DEBUG
	// “–‚½‚è”»’è‚Ì•\Ž¦
	m_colRect.Draw(GetColor(255, 0, 0), false);
#endif
}

void Shot::Start(Vec2 pos)
{
	m_isExist = true;

	m_pos = pos;
}

void Shot::colShot()
{
        m_isExist = false;
}
