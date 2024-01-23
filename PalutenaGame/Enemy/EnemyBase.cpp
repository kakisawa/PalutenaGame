#include "EnemyBase.h"
#include "DxLib.h"
#include <cassert>

namespace
{
	// �_���[�W���o�t���[����
	constexpr int kDamageFrame = 60;
}

EnemyBase::EnemyBase():
	EGraph(-1),
	W(0),
	H(0),
	HP(0),
	Atk(0), 
	EnemyAnim(0),
	Gravity(0),
	isTurn(false),	// �G�l�~�[�̌����t���O,�E�������Ă����false��}��
	isDeath(false),	// ���S�t���O,����ł��Ȃ���false��}��
	m_isExist(true), 
	m_damageFrame(0)
{
}

void EnemyBase::Init(int x, int y)
{
	m_pos.x = x;
	m_pos.y = y;
}

void EnemyBase::Update()
{
	// �_���[�W���o�̐i�s
	m_damageFrame--;
	if (m_damageFrame < 0)	m_damageFrame = 0;

	// ���݂��Ȃ��G�̏����͂��Ȃ�
	if (!m_isExist) return;
}

void EnemyBase::Draw()
{
	// ���݂��Ȃ��G�͕`�悵�Ȃ�
	if (!m_isExist) return;

	// �O���t�B�b�N���ݒ肳��Ă��Ȃ���Ύ~�܂�
	assert(EGraph != -1);

	if (m_damageFrame % 4 >= 2) return;

	if (isTurn == false)
	{
		DrawGraph(m_pos.x, m_pos.y, EGraph, true);
	}
	else if (isTurn == true)
	{
		DrawTurnGraph(m_pos.x, m_pos.y, EGraph, true);
	}
#ifdef _DEBUG
	// �����蔻��̕\��
	m_colRect.Draw(GetColor(255, 0, 0), false);
#endif // DEBUG
}

void EnemyBase::OnDamage()
{
	// �_���[�W���o���͍ēx�H���Ȃ�
	if (m_damageFrame > 0)
	{
		return;
	}
	// HP -= m_pPlayer->GetPlayerAtk();

	HP -= 1;
	
	// ���o�t���[������ݒ肷��
	m_damageFrame = kDamageFrame;

	if (HP <= 0)
	{
		Death();
	}
}

void EnemyBase::Death()
{
	isDeath = true;		// ���S�t���O���I���ɂ���
	m_isExist = false;
}

void EnemyBase::Start()
{
	m_isExist = false;
}

void EnemyBase::UpdateCollision()
{
	int width = 0;
	int height = 0;
	GetGraphSize(EGraph, &width, &height);
	// ���S���W���w�肵�ē����蔻���Rect�𐶐�����
	m_colRect.SetLT(m_pos.x, m_pos.y, width, height);
}
