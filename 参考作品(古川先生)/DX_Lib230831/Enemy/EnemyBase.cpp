#include "EnemyBase.h"
#include "DxLib.h"
#include "Game.h"
#include <cassert>

namespace 
{
}

EnemyBase::EnemyBase():
	m_handle(-1),
	m_isExist(false)
//	m_pos�͈����Ȃ��̃R���X�g���N�^���Ă΂��
// �����Ȃ��̃R���X�g���N�^���Ăԏꍇ�͏ȗ��ł���
{
}

EnemyBase::~EnemyBase()
{
}

void EnemyBase::Init()
{
}

void EnemyBase::Update()
{
	// ���݂��Ȃ��G�̏����͂��Ȃ�
	if (!m_isExist) return;
}

void EnemyBase::Draw()
{
	//float fNum = 1.0f;	// 32bit
	//double dNum = 1.0f;	// 64bit
	
	// ���݂��Ȃ��G�͕`�悵�Ȃ�
	if (!m_isExist) return;

	// �O���t�B�b�N���ݒ肳��Ă��Ȃ���Ύ~�܂�
	assert(m_handle != -1);

	// DrawGraph(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y), m_handle, false);
	
	// ���S�ʒu����Ƃ��Ĕ��肷��
	DrawRotaGraph(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y),
		1.0, 0.0,
		m_handle, true, false);

#ifdef _DEBUG
	// �����蔻��̕\��
	m_colRect.Draw(GetColor(255, 0, 0), false);
#endif // DEBUG
}

void EnemyBase::Start()
{
	m_isExist = false;
}

void EnemyBase::UpdateCollision()
{
	int width = 0;
	int height = 0;
	GetGraphSize(m_handle, &width, &height);
//	m_colRect.SetLT(m_pos.x, m_pos.y, width, height);
	// ���S���W���w�肵�ē����蔻���Rect�𐶐�����
	m_colRect.SetCenter(m_pos.x, m_pos.y, width, height);
}