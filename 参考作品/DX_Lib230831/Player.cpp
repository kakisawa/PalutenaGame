#include "Player.h"
#include "Game.h"
#include "DxLib.h"
#include "Pad.h"
#include "SceneMain.h"

#include "ShotMagicWand.h"
#include "ShotBible.h"

#include <cmath>

// Player�Ŏg�p����
namespace
{
	// �ړ����x
	constexpr float kSpeed = 3.0f;

	// �L�����N�^�[�̃T�C�Y
	constexpr int kWidth = 32;
	constexpr int kHeight = 32;

	// �L�����N�^�[�̃A�j���[�V����
	constexpr int kUseFrame[] = { 0,1,2,1 };
	// �A�j���[�V������1�R�}�̃t���[����
	constexpr int kAnimFrameNum = 8;
	// �A�j���[�V����1�T�C�N���̃t���[����
	constexpr int kAnimFrameCycle = _countof(kUseFrame) * kAnimFrameNum;
	// �_���[�W���o�t���[����
	constexpr int kDamageFrame = 60;
	// ���@�̏�̔��ˊԊu
	constexpr int kMagicWandFrame = 30;
}

Player::Player(SceneMain* pMain) :
	m_pMain(pMain),
	m_handle(-1),
	m_pos(Game::kScreenWidth / 2, Game::kScreenHeight / 2),
	m_dir(kDirDown),
	m_walkAnimFrame(0),
	m_magicWandFrame(0),
	m_damageFrame(0)
{
}

Player::~Player()
{
}

void Player::Init()
{
}

void Player::Update()
{
	// �_���[�W���o�̐i�s
	m_damageFrame--;
	if (m_damageFrame < 0)	m_damageFrame = 0;

	// �p�b�h�̏\���L�[���g�p���ăv���C���[���ړ�������
	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	bool isMove = false;	// �ړ������ǂ���
	// �ړ��ʂ����悤�ɂ���
	Vec2 move{ 0.0f,0.0f };

	if (pad & PAD_INPUT_UP)
	{
		// m_pos.y -= kSpeed;
		move.y -= kSpeed;
		m_dir = kDirUp;
		isMove = true;
	}
	if (pad & PAD_INPUT_DOWN)
	{
		//m_pos.y += kSpeed;
		move.y += kSpeed;
		m_dir = kDirDown;
		isMove = true;
	}
	if (pad & PAD_INPUT_LEFT)
	{
		// m_pos.x -= kSpeed;
		move.x -= kSpeed;
		m_dir = kDirLeft;
		isMove = true;
	}
	if (pad & PAD_INPUT_RIGHT)
	{
		// m_pos.x += kSpeed;
		move.x += kSpeed;
		m_dir = kDirRight;
		isMove = true;
	}

	// �΂߈ړ��̏ꍇ�����������ňړ�����悤�ɂ���
		/*
	// �x�N�g���̐��K�����s���ׂɃx�N�g���̒��������߂�
	float moveLength = move.length();
	sqrt(1.0);		// double�^�̕����������߂����ꍇ�͂�����
	sqrtf(1.0f);	// float�^�̏ꍇ�͂�����
	moveLength = sqrtf(moveLength);	// �����������߂Ē�����
	*/

	// �x�N�g���̐��K��
	move.normalize();
	/*
	// moveLength(�x�N�g���̒���)��0.0�̉\��������
	if (moveLength > 0.0f)
	
		
	// �x�N�g���̒����Ńx�N�g��������
		move.x /= moveLength;
		move.y /= moveLength;

	*/

	// �x�N�g���̒�����kSpeed�ɂ���
	move *= kSpeed;
	/*
	move.x *= kSpeed;
	move.y *= kSpeed;	
	move = move.mul(kSpeed);
*/

	// ���W�ƃx�N�g���̑����Z
	m_pos += move;
	/*
	m_pos.x += move.x;
	m_pos.y += move.y;
	m_pos = m_pos.puls(move);
	m_pos += move;*/

	// �����蔻��̍X�V
	m_colRect.SetCenter(m_pos.x, m_pos.y, kWidth, kHeight);
	
	if (isMove)
	{
		// �����A�j���[�V����
		m_walkAnimFrame++;
		if (m_walkAnimFrame >= kAnimFrameCycle)
		{
			m_walkAnimFrame = 0;
		}
	}

	// �V���b�g
	m_magicWandFrame++;
	if (m_magicWandFrame >= kMagicWandFrame)
	{
		m_magicWandFrame = 0;

		// ���@�̏񐶐�
		ShotMagicWand* pShot = new ShotMagicWand;

		pShot->Init();
		pShot->SetMain(m_pMain);
		pShot->SetPlayer(this);
		pShot->Start(GetPos());
		// �ȍ~�X�V�⃁�����̊J����SceneMain�ɔC����
		m_pMain->AddShot(pShot);
	}

	// �����e�X�g����
	// �{�^�����������甭������悤�ɂ���
	if (Pad::IsTrigger(PAD_INPUT_1))
	{
		// �����������̊m��
		ShotBible* pShot = new ShotBible;

		pShot->Init();
		pShot->SetMain(m_pMain);
		pShot->SetPlayer(this);
		pShot->Start(GetPos());
		// �ȍ~�X�V�⃁�����̊J����SceneMain�ɔC����
		m_pMain->AddShot(pShot);
	}
}


void Player::Draw()
{
	// �_���[�W���o 2�t���[���Ԋu�ŕ\����\���؂�ւ�
	// 0: �\�������
	// 1:�\�������
	// 2:��\��
	// 3:��\��
	// 4:�\�������	...
	// %4���邱�Ƃ�012301230123...�ɕϊ�����
	if (m_damageFrame % 4 >= 2) return;

	// DrawGraph(static_cast<int>(m_posX), static_cast<int>(m_posY), m_handle, true);	// C++�̃L���X�g�͏������G

	int animFrame = m_walkAnimFrame / kAnimFrameNum;

	int srcX = kUseFrame[animFrame] * kWidth;
	int srcY = kHeight * m_dir;

#if false
	switch (m_dir)
	{
	case kDirDown:
		srcY = 32 * 0;
		break;
	case kDirLeft:
		srcY = 32 * 1;
		break;
	case kDirRight:
		srcY = 32 * 2;
		break;
	case kDirUp:
		srcY = 32 * 3;
		break;
	}
#endif

//	DrawRectGraph(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y),
//		srcX, srcY, kWidth, kHeight, m_handle, true);
	
	// Dx���C�u�����ɂ̓��t�@�����X�y�[�W�ɏ�����Ă��Ȃ��֐����������݂���
	// DxLib.h���m�F���Ă�����ۂ��֐���T�����茟�����Ă݂悤
	DrawRectRotaGraph(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y),
		srcX, srcY, kWidth, kHeight,
		1.0, 0.0,
		m_handle, true, false);

#ifdef _DEBUG
	// �����蔻��̕\��
	m_colRect.Draw(GetColor(0, 0, 255), false);
#endif
}

void Player::OnDamage()
{
	// �_���[�W���o���͍ēx�H���Ȃ�
	if (m_damageFrame > 0)	return;
	// ���o�t���[������ݒ肷��
	m_damageFrame = kDamageFrame;
}
