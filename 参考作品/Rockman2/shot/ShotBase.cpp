#include "ShotBase.h"
#include <DxLib.h>

ShotBase::ShotBase() :
	m_pMain(nullptr),
	m_pPlayer(nullptr),
	m_handle(-1),
	m_isExist(false)
{
}

ShotBase::~ShotBase()
{
}
