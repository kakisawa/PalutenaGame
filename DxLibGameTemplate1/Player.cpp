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
	// �W�����v����
	constexpr float kJump = 13.0f;

	// �L�����N�^�[�̃A�j���[�V����
	constexpr int kUseFrame[] = { 0,1,2,3,4,5,4,3,2,1 };
	// �A�j���[�V������1�R�}�̃t���[����
	constexpr int kAnimFrameNum = 8;
	// �A�j���[�V����1�T�C�N���̃t���[����
	constexpr int kAnimFrameCycle = _countof(kUseFrame) * kAnimFrameNum;
}

Player::Player():
	HP(100),						// �v���C���[�̏���HP
	m_pos(kScreenWidth / 2, 100),	// �v���C���[�̏����ʒu
	m_dir(kDirFront),				// �v���C���[�̏�������
	JumpPower(0.0f),				// �v���C���[�̏����W�����v
	Gravity(0.0f),					// �v���C���[�̏����d��
	IdleAnimation(0)				// �ҋ@��ԃA�j���[�V�����̏�����
{
}

Player::~Player()
{
}

void Player::Init()
{
	// �v���C���[�̉摜�ǂݍ���&���W�̏�����
	Graph = LoadGraph("data/Player.png");
}

void Player::Update()
{
	// �v���C���[���ړ������ǂ���
	isMove = false;				// �ړ����Ă��Ȃ���false
	// �v���C���[���ǂ̕����������Ă��邩
	m_dir = kDirFront;			// ���ʂ������Ă���̐��ʂ������Ă����kDirFront

	// �L�[���͎擾
	int Key = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	// �ړ��ʂ����悤�ɂ���
	Vec2 move{ 0.0f,0.0f };

	// �d�͏���
	m_pos.y += Gravity;
	// ���������x��������
	Gravity += 0.3f;

	// �����n�ʂɂ��Ă�����~�܂�
	if (m_pos.y > Ground)
	{
		m_pos.y = Ground;

		if (m_pos.y == Ground)
		{
			Gravity = 0;
			JumpPower = 0;

			isJumpFlag = false;
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
	if ((Key & PAD_INPUT_A) && m_pos.y == Ground)
	{
		// �W�����v�����x
		for (int i = 0; i < kJump; i++) {
			JumpPower += 0.5f;
		}
		isJumpFlag = true;
		isMove = true;
	}

	// �W�����v����
	m_pos.y -= JumpPower;


	// �x�N�g���̐��K��
	move.normalize();

	// �x�N�g���̒�����kSpeed�ɂ���
	move *= kSpeed;

	// ���W�ƃx�N�g���̑����Z
	m_pos += move;

	// �����蔻��̍X�V
	m_colRect.SetCenter(m_pos.x + kWidth / 2, m_pos.y + kHeight / 2, kWidth, kHeight);

	// x���W...�v���C���[�����E��ʊO�ɏo��ƁA���Α�����v���C���[���o�Ă���
	if (m_pos.x > kScreenWidth - kWidth)
	{
		m_pos.x = 0;
	}
	if (m_pos.x < 0)
	{
		m_pos.x = kScreenWidth - kWidth;
	}




	if (isMove = false)
	{
		// �ҋ@��ԃA�j���[�V����
		IdleAnimation++;
		if (IdleAnimation >= kAnimFrameCycle)
		{
			IdleAnimation = 0;
		}
	}
}

void Player::Draw()
{
	int animFrame = IdleAnimation / kAnimFrameNum;

	int srcX = kUseFrame[animFrame] * 16;
	


	// �v���C���[�̒ʏ헧���G(�摜�̒�����؂蔲���Ċg�傷��)
	DrawRectExtendGraph(m_pos.x, m_pos.y, m_pos.x + kWidth, m_pos.y + kHeight,
		srcX, 0, 16, 16,
		Graph, true);

	//if(m_dir = kDirLeft)
	//{
	//	// �v���C���[���E�ړ��������G(�摜�̒�����؂蔲���Ċg�傷��)
	//	DrawRectExtendGraph(m_pos.x, m_pos.y, m_pos.x + kWidth, m_pos.y + kHeight,
	//		srcX, 32, 16, 16,
	//		Graph, true);
	//}
	//else if(m_dir = kDirRight)
	//{
	//	// �v���C���[���E�ړ��������G(�摜�̒�����؂蔲���Ċg�傷��)
	//	DrawRectExtendGraph(m_pos.x, m_pos.y, m_pos.x + kWidth, m_pos.y + kHeight,
	//		srcX,16, 16, 16,
	//		Graph, true);
	//}



	//if (isTurn)
	//{
	//	// �v���C���[���]�`��(������)
	//	DrawTurnGraph(m_pos.x, m_pos.y, Graph, false);
	//}
	//else
	//{
	//	// �v���C���[�`��(�E����)
	//	DrawGraph(m_pos.x, m_pos.y, Graph, false);
	//}

	// �v���C���[�̌��ݍ��W�\��
	DrawFormatString(0,0,GetColor( 255 , 255 , 255 ),
		"���ݍ��W:(%.2f,%.2f)",m_pos.x, m_pos.y);
	// �v���C���[�̌��ݑ̗͕\��
	DrawFormatString(0, 19, GetColor(255, 255, 255),
		"HP:(%d)", HP);

#ifdef _DEBUG
	// �����蔻��̕\��
	m_colRect.Draw(GetColor(255, 0, 0), false);
#endif
}

// �n�ʏ����܂ŏI����Ă�͂�
// 1,�v���C���[�̃A�j���[�V����
// 4,�P�����ŃW�����v(�D��x��)
// �Z5,�����蔻��
// �ZHP�Ǘ��E�\��

// �w�i�\��
// �V�[���J��(�^�C�g���A�Q�[�����)
// �X�N���[��

// �V���b�g

