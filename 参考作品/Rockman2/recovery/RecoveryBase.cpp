#include "RecoveryBase.h"
#include "Player.h"
#include "SceneMain.h"
#include "DxLib.h"

RecoveryBase::RecoveryBase():
	m_pMain(nullptr),
	m_handle(-1),
	m_frame(0),
	m_isExist(false)
{
}

RecoveryBase::~RecoveryBase()
{
}

void RecoveryBase::Init()
{
}

void RecoveryBase::Update()
{
	// ���݂��Ȃ��A�C�e���̏����͂��Ȃ�
	if (!m_isExist) return;
}

void RecoveryBase::Draw()
{
}
