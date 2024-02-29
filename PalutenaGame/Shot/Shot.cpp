#include "Shot.h"
#include "DxLib.h"
#include "Player.h"
#include "Game.h"

Shot::Shot() :
	m_x(0),
	m_y(0),
	m_isExist(false)
{
}

Shot::~Shot()
{
}

void Shot::init()
{
	m_x = m_pos.x;
	m_y = m_pos.y;

	m_dir = m_pPlayer->GetShotDir();
}

void Shot::Update()
{
	if (!m_isExist)	return;

	if (m_dir == kShotDirRight)
	{
		m_pos.x += kShotSpeed;
		if (m_pos.x >= kScreenWidth)
		{
			m_isExist = false;
		}
	}
	else if (m_dir == kShotDirLeft)
	{
		m_pos.x -= kShotSpeed;
		if (m_pos.x <= 0)
		{
			m_isExist = false;
		}
	}
	else if (m_dir == kShotDirUp)
	{
		m_pos.y -= kShotSpeed;
		if (m_pos.y <= 0)
		{
			m_isExist = false;
		}
	}

	// “–‚½‚è”»’è‚ÌXV
	m_colRect.SetCenter(m_pos.x + kPlayerWidth * 0.5f,
		m_pos.y + kPlayerHeight * 0.5f,
		kShotWidth * 0.5f, kShotHeight * 0.5f);
}

void Shot::Draw()
{
	if (!m_isExist) return;		// ‘¶Ý‚·‚é‚©

	m_colRect.Draw(GetColor(255, 255, 0), true);

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
