#include "DeathYourEnemy.h"
#include "DxLib.h"
#include "Game.h"

#include "SceneMain.h"

namespace
{
	// �ړ����x
	constexpr float kSpeed = 3.0f;
}

DeathYourEnemy::DeathYourEnemy()
{
	EGraph = LoadGraph("data/Fairy2.png");		// �G�摜�̃��[�h

	W = 0;		// �G�摜�T�C�Y
	H = 0;

	HP = 5;		// HP
	Atk = 30;	// �U����
	Item;		// �h���b�v�A�C�e��

	Gravity = 0.0f;		// �G�̏����d��
	isTurn = false;		// �E�������Ă����false��}��

	m_pos.x = 400;	// �G�̏����ʒu
	m_pos.y = 400;
}

DeathYourEnemy::~DeathYourEnemy()
{
	DeleteGraph(EGraph);	// �G�摜�̍폜
}

void DeathYourEnemy::Update()
{
	m_basePos += m_vec;
	m_pos += m_basePos;

	//�����蔻��̍X�V
	UpdateCollision();

	// �G�̃T�C�Y���擾
	GetGraphSize(EGraph, &W, &H);

	if (m_pos.x > kScreenWidth + W / 2)
	{
		m_isExist = false;
	}

	// �ړ��ʂ����悤�ɂ���
	Vec2 move{ 0.0f,0.0f };

	// �x�N�g���̐��K��
	move.normalize();
	// �x�N�g���̒�����kSpeed�ɂ���
	move *= kSpeed;
	// ���W�ƃx�N�g���̑����Z
	m_pos += move;
	

	// //�G�ړ�
		// �G�l�~�[�̍��W���ړ����Ă�������Ɉړ�����
	if (isTurn == false)
	{
		//m_pos += move;
		m_pos.x += kSpeed;
	}
	else if (isTurn == true)
	{
		//m_pos -= move;
		m_pos.x -= kSpeed;
	}
	// �G�l�~�[����ʒ[����ł����ɂȂ��Ă������ʓ��̍��W�ɖ߂��Ă����A�ړ�������������]����
	if (m_pos.x > kScreenWidth - W)
	{
		m_pos.x = kScreenWidth - W;
		isTurn = true;
	}
	else if (m_pos.x < 0)
	{
		m_pos.x = 0;
		isTurn = false;
	}
}
