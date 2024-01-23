#include "DeathYourEnemy.h"
#include "DxLib.h"
#include "Game.h"

namespace
{
	// �G�l�~�[�̃T�C�Y
	constexpr int kWidth = 26;
	constexpr int kHeight = 46;

	// �ړ����x
	constexpr float kSpeed = 3.0f;
}

DeathYourEnemy::DeathYourEnemy()
{
	EGraph = LoadGraph("data/Fairy2.png");

	HP = 10;		// HP
	Atk = 10;	// �U����

	Gravity = 0.0f;				// �G�̏����d��
	isTurn = false;				// �E�������Ă����false��}��
	angle = 0;					// �G�̈ړ��p�x

	m_pos.x = kScreenWidth * 0.7;
	m_pos.y = Ground - kHeight * 0.5;
}

DeathYourEnemy::~DeathYourEnemy()
{
	DeleteGraph(EGraph);
}

void DeathYourEnemy::Init()
{
}

void DeathYourEnemy::Update()
{
	EnemyBase::Update();

	//m_basePos += m_vec;
	//m_pos += m_basePos;

	//�����蔻��̍X�V
	UpdateCollision();

	// �ړ��ʂ����悤�ɂ���
	Vec2 move{ 0.0f,0.0f };

	// �x�N�g���̐��K��
	move.normalize();
	// �x�N�g���̒�����kSpeed�ɂ���
	move *= kSpeed;


	//�G�ړ�
	if (isTurn == false)
	{
		angle++;
		float angle2 = angle * (DX_PI / 180);
		m_pos.y = sin(angle2) * 200 + 320;
		m_pos.x += kSpeed;

	}
	else if (isTurn == true)
	{
		angle++;
		float angle2 = angle * (DX_PI / 180);
		m_pos.y = sin(angle2) * 200 + 320;
		m_pos.x -= kSpeed;
	}
	// �G�l�~�[����ʒ[����ł����ɂȂ��Ă������ʓ��̍��W�ɖ߂��Ă����A�ړ�������������]����
	if (m_pos.x > kScreenWidth - kWidth)
	{
		m_pos.x = kScreenWidth - kWidth;
		isTurn = true;
	}
	else if (m_pos.x < 0)
	{
		m_pos.x = 0;
		isTurn = false;
	}
}

void DeathYourEnemy::Start()
{
	m_isExist = true;
}
