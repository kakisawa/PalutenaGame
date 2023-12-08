#include "DxLib.h"
#include "Player.h"

#include "Game.h"

namespace
{
	// �L�����N�^�[�̃T�C�Y
	constexpr int kWidth = 32;
	constexpr int kHeight = 32;

	// �ړ����x
	constexpr float kSpeed = 3.0f;
}


Player::Player():
	m_pos(kScreenWidth / 2, 100),
	m_dir(kDirRight),
	JumpPower(8.0f),
	Gravity(8.0f)
{
}

Player::~Player()
{
}

void Player::Init()
{
	// �v���C���[�̉摜�ǂݍ���&���W�̏�����
	Graph = LoadGraph("data/Fairy.png");

	// �v���C���[�̏c����
	GetGraphSize(Graph, &W, &H);
}

void Player::Update()
{
	// �L�[���͎擾
	int Key = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	// �ړ��ʂ����悤�ɂ���
	Vec2 move{ 0.0f,0.0f };

	// �d�͏���
	m_pos.y += JumpPower;

	// �����n�ʂɂ��Ă�����~�܂�
	if (m_pos.y > Ground)
	{
		m_pos.y = Ground;

		if (m_pos.y == Ground)
		{
			FallPowor = 0;

			isPushFlag = false;
		}
	}


	// ���L�[�������Ă�����v���C���[���ړ�������
	// �����
	if (Key && CheckHitKey(KEY_INPUT_UP) == 1)
	{
		isMove = true;
		isTurn = false;
		m_dir = kDirUp;
	}
	// ����
	if (Key && CheckHitKey(KEY_INPUT_DOWN) == 1)
	{
		isMove = true;
		isTurn = false;
		m_dir = kDirDown;
	}
	// ���ړ�
	if (Key && CheckHitKey(KEY_INPUT_LEFT) == 1)
	{
		m_pos.x -= kSpeed;
		isMove = true;
		isTurn = true;
		m_dir = kDirLeft;
	}
	// �E�ړ�
	if (Key && CheckHitKey(KEY_INPUT_RIGHT) == 1)
	{
		m_pos.x += kSpeed;
		isMove = true;
		isTurn = false;
		m_dir = kDirRight;
	}

	// �W�����v�{�^���������Ă��āA�n�ʂɂ��Ă�����W�����v
	if ((Key & PAD_INPUT_A) && m_pos.y == 400)
	{
		m_pos.y -= JumpPower;
		isPushFlag = true;
		isMove = true;
	}

	// �x�N�g���̐��K��
	move.normalize();

	// �x�N�g���̒�����kSpeed�ɂ���
	move *= kSpeed;

	// ���W�ƃx�N�g���̑����Z
	m_pos += move;
}

void Player::Draw()
{
	if (isTurn)
	{
		// �v���C���[���]�`��(������)
		DrawTurnGraph(m_pos.x, m_pos.y, Graph, false);
	}
	else
	{
		// �v���C���[�`��(�E����)
		DrawGraph(m_pos.x, m_pos.y, Graph, false);
	}
}



// �n�ʏ����܂ŏI����Ă�͂�
// 1,�v���C���[�̃A�j���[�V����(���E�W�����v)
// 2,�d�͉����x
// 3,�W�����v�ʂ�傫��
// 4,�P�����ŃW�����v(�D��x��)
// 5,�����蔻��
// HP�Ǘ��E�\��

// �w�i�\��
// �V�[���J��(�^�C�g���A�Q�[�����)
// �X�N���[��

// �V���b�g

