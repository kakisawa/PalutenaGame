#include "DxLib.h"
#include "Player.h"
#include "Shot.h"
#include "Game.h"
#include "KeyProcess.h"

#include <cmath>

namespace 
{
	// �L�����N�^�[�̃T�C�Y
	constexpr int kWidth = 32;
	constexpr int kHeight = 32;

	// �ړ����x
	constexpr float kSpeed = 3.0f;
	//// �W�����v�ړ���
	//constexpr float JumpPower = 20.0f;
}


Player::Player():
	FallPowor(0.0f),			// �������x
	JumpPower(0.0f),			// �W�����v�ړ���
	m_handle(-1),
	m_pos(kScreenWidth / 2, 400),
	Graph(0),
	W(0),
	H(0)
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

	// �O���t�B�b�N���]�t���O(���]���Ă��Ȃ���false��}��)
	isTurn = false;
	// �v���C���[����������Ă��邩�̃t���O(�����Ă��Ȃ���false��}��)
	isLookUp = false;
	// �v���C���[�����Ⴊ��ł��邩�̃t���O(���Ⴊ��ł��Ȃ���false��}��)
	isSquat = false;
	// �W�����v�����ǂ����̃t���O�t���O(�W�����v���Ă��Ȃ���false��}��)
	isPushFlag = false;
	// �ړ������ǂ����̃t���O(�ړ����Ă��Ȃ���false��}��)
	isMove = false;
	// �V���b�g�{�^�����O�̃t���[���ŉ����ꂽ���ǂ�����ۑ�����ϐ���false(������Ă��Ȃ�)����
	isPrevshotFlag = false;

	// �e�̍������t���O(���������Ă��Ȃ���false��}��)
	LeftDir = false;
	// �e�̏�����t���O(��������Ă��Ȃ���false��}��)
	TopDir = false;
}

void Player::Update(Shot shotArray[], int shotArraySize)
{
	// �L�[���͎擾
	int Key = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	// �ړ��ʂ����悤�ɂ���
	Vec2 move{ 0.0f,0.0f };

	// ���L�[�������Ă�����v���C���[���ړ�������
	// �����
	if (Key && CheckHitKey(KEY_INPUT_UP) == 1)
	{
		isMove = true;
		isLookUp = true;
		isTurn = false;
		isSquat = false;
	}
	// ����
	if (Key && CheckHitKey(KEY_INPUT_DOWN) == 1)
	{
		isMove = true;
		isTurn = false;
		isLookUp = false;
		isSquat = true;
	}
	// ���ړ�
	if (Key && CheckHitKey(KEY_INPUT_LEFT) == 1)
	{
		m_pos.x -= kSpeed;
		isMove = true;
		isLookUp = false;
		isTurn = true;
		isSquat = false;
	}
	// �E�ړ�
	if (Key && CheckHitKey(KEY_INPUT_RIGHT) == 1)
	{
		m_pos.x += kSpeed;
		isMove = true;
		isLookUp = false;
		isTurn = false;
		isSquat = false;
	}

	// �W�����v�{�^���������Ă��āA�n�ʂɂ��Ă�����W�����v
	if ((Key & PAD_INPUT_A) && m_pos.y == 400)
	{
		JumpPower = 8.0f;

		isPushFlag = true;
		isMove = true;
	}

	// ��������
	m_pos.y -= JumpPower;

	// ���������x��������
	JumpPower -= 0.5f;

	//// �W�����v
	//if (Key && CheckHitKey(KEY_INPUT_A) == 1) {
	//	m_pos.y -= player.JumpPower;
	//	player.isPushFlag = true;
	//	isMove = true;
	//}
	//// ���������x��������
	//player.FallPowor += 0.5f;
	//// ��������
	//m_pos.y += player.FallPowor;

	// �����n�ʂɂ��Ă�����~�܂�
	if (m_pos.y > Ground)
	{
		m_pos.y = Ground;

		if (m_pos.y = Ground)
		{
			FallPowor = 0;

			isPushFlag = false;
		}
	}

	// �x�N�g���̐��K��
	move.normalize();
	// �x�N�g���̒�����kSpeed�ɂ���
	move *= kSpeed;
	// ���W�ƃx�N�g���̑����Z
	m_pos += move;

	// �����蔻��̍X�V
	m_colRect.SetCenter(m_pos.x + kWidth / 2, m_pos.y + kHeight / 2, kWidth, kHeight);


	// �e�̔��ˏ���
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		// �O�t���[���ŃV���b�g�{�^���������������ۑ�����Ă���ϐ���false��������e�𔭎�
		if (isPrevshotFlag == false)
		{
			// ��ʏ�ɂłĂ��Ȃ��e�����邩�A�e�̐������J��Ԃ��Ē��ׂ�
			for (int i = 0; i < shotArraySize; i++)
			{
				// �ei����ʏ�ɂłĂ��Ȃ��ꍇ�͂��̒e����ʂɏo��
				if (shotArray[i].Flag == false)
				{
					// �ei�̈ʒu���Z�b�g�A�ʒu�̓v���C���[�̒��S�ɂ���
					if (isTurn)
					{
						shotArray[i].X = m_pos.x;
						LeftDir = true;
						TopDir = false;

						/*shotArray[i].LeftDir = true;
						shotArray[i].TopDir = false;*/
					}
					else if (isLookUp)
					{
						shotArray[i].X = m_pos.x + kWidth / 2;
						LeftDir = false;
						TopDir = true;

						/*shotArray[i].LeftDir = false;
						shotArray[i].TopDir = true;*/
					}
					else
					{
						shotArray[i].X = (kWidth - shotArray[i].W) / 2 + m_pos.x;
						LeftDir = false;
						TopDir = false;

						/*shotArray[i].LeftDir = false;
						shotArray[i].TopDir = false;*/
					}

					shotArray[i].Y = (kHeight - shotArray[i].H) / 2 + m_pos.y;

					// �ei�͌����_�������đ��݂���̂ŁA���ݏ�Ԃ�ێ�����ϐ���true��������
					shotArray[i].Flag = true;

					// ��e���o�����̂Œe���o�����[�v���甲���܂�
					break;
				}
			}
		}
		// �O�t���[���ŃV���b�g�{�^����������Ă�������ۑ�����ϐ���true(������Ă���)����
		isPrevshotFlag = true;
	}
	else
	{
		// �V���b�g�{�^����������Ă��Ȃ������ꍇ��
		// �O�t���[���ŃV���b�g�{�^����������Ă�������ۑ�����ϐ���false(������Ă��Ȃ�)����
		isPrevshotFlag = false;
	}

	// x���W...�v���C���[�����E��ʊO�ɏo��ƁA���Α�����v���C���[���o�Ă���
	// y���W...�v���C���[����ʊO�ɏo�悤�Ƃ���Ǝ~�܂�
	if (m_pos.x < 0 - W)
	{
		m_pos.x = kScreenWidth - W;
	}
	if (m_pos.x > kScreenWidth)
	{
		m_pos.x = 0;
	}
	if (m_pos.y < 0)
	{
		m_pos.y = 0;
	}
	if (m_pos.y > Ground)
	{
		m_pos.y = Ground;
	}
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

#ifdef _DEBUG
	// �����蔻��̕\��
	m_colRect.Draw(GetColor(0, 0, 255), false);
#endif
}
