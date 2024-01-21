#include "Shot.h"
#include "DxLib.h"
#include "Player.h"

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
	/*if (m_Player->OutDir() == kDirRight)
	{
		RightShot();
	}
	else if (m_Player->OutDir() == kDirLeft)
	{
		LeftShot();
	}
	else if (m_Player->OutDir() == kDirUp)
	{
		UpShot();
	}*/
}

void Shot::Update()
{
	if (!m_isExist)	return;

	/*if (m_Player->OutDir() == kDirRight)
	{
		x += kShotSpeed;
	}
	else if (m_Player->OutDir() == kDirLeft)
	{
		x += kShotSpeed;
	}
	else if (m_Player->OutDir() == kDirUp)
	{
		y += kShotSpeed;
	}*/
}

void Shot::Draw()
{
	if (!m_isExist) return;		// ���݂��邩

	DrawBox(x, y, kShotWidth, kShotHeight, GetColor(255, 0, 0),false);
}

void Shot::RightShot()
{
	m_isExist = true;

	// �E�����ւ̒e�̔��ˈʒu
	// �v���C���[�̉E��,�����͔���
	x = m_Player->OutPos().x + kPlayerWidth;
	y = m_Player->OutPos().y + kPlayerHeight * 0.5;

}

void Shot::LeftShot()
{
	m_isExist = true;

	// �������ւ̒e�̔��ˈʒu
	// �v���C���[�̍���,�����͔���
	x = m_Player->OutPos().x;
	y = m_Player->OutPos().y + kPlayerHeight * 0.5;
}

void Shot::UpShot()
{
	m_isExist = true;

	// �E�����ւ̒e�̔��ˈʒu
	// �v���C���[�̏㑤
	x = m_Player->OutPos().x + kPlayerWidth * 0.5;
	y = m_Player->OutPos().y;
}
