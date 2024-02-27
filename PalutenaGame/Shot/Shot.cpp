#include "Shot.h"
#include "DxLib.h"
#include "Player.h"
#include "Game.h"

Shot::Shot() :
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

	dir = m_pPlayer->GetShotDir();
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
		}
	}
	else if (dir == kShotDirLeft)
	{
		m_pos.x -= kShotSpeed;
		if (m_pos.x <= 0)
		{
			m_isExist = false;
		}
	}
	else if (dir == kShotDirUp)
	{
		m_pos.y -= kShotSpeed;
		if (m_pos.y <= 0)
		{
			m_isExist = false;
		}
	}

	// �����蔻��̍X�V
	m_colRect.SetCenter(m_pos.x + kPlayerWidth * 0.5f,
		m_pos.y + kPlayerHeight * 0.5f,
		kShotWidth * 0.5f, kShotHeight * 0.5f);
}

void Shot::Draw()
{
	if (!m_isExist) return;		// ���݂��邩

	m_colRect.Draw(GetColor(255, 255, 0), true);

#ifdef _DEBUG
	// �����蔻��̕\��
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
