#include "BulletBase.h"
#include "DxLib.h"
#include "Player.h"

BulletBase::BulletBase():
	Se(0),
	x(0),
	y(0)
{
}

BulletBase::~BulletBase()
{
}

void BulletBase::init()
{
}

void BulletBase::Update()
{
}

void BulletBase::Draw()
{
}

void BulletBase::RightShot()
{
	x = x + m_pPlayer->OutPos().x;

}

void BulletBase::LeftShot()
{
}

void BulletBase::UpShot()
{
}
