#include "DxLib.h"
#include "Player.h"

#include "Game.h"
#include "Pad_Key.h"

namespace
{
	// �L�����N�^�[�̃T�C�Y
	constexpr int kWidth = 32;
	constexpr int kHeight = 32;

	// �ړ����x
	constexpr float kSpeed = 3.0f;
	// �W�����v����
	constexpr float kJump = 13.0f;

	// �L�����N�^�[�̃A�j���[�V����		// ���[�V�����̃t���[�����Ƃɍ�蒼��
	constexpr int Frame[] = { 0,1,2,3,4,5,4,3,2,1 };
	// �A�j���[�V������1�R�}�̃t���[����
	constexpr int kAnimFrameNum = 8;
	// �A�j���[�V����1�T�C�N���̃t���[����
	constexpr int FrameCycle = _countof(Frame) * kAnimFrameNum;
	// �_���[�W���o�t���[����
	constexpr int kDamageFrame = 60;
}

Player::Player(SceneMain* pMain) :
	m_pMain(pMain),
	Graph(-1),
	PlayerHP(100),						// �v���C���[�̏���HP
	m_pos(kScreenWidth / 2, 100),	// �v���C���[�̏����ʒu
	m_dir(kDirFront),				// �v���C���[�̏�������
	JumpPower(0.0f),				// �v���C���[�̏����W�����v
	Gravity(0.0f),					// �v���C���[�̏����d��
	PlayerAnim(0),					// �v���C���[�A�j���[�V�����̏�����
	m_damageFrame(0),				// �v���C���[��_���A�j���[�V����
	isMove(false),					// �ړ���ԃt���O(�ے��false)
	isAttack(false)					// �U���t���O(�ے��false)
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

	// �v���C���[���ړ������ǂ���
	isMove = false;				// �ړ����Ă��Ȃ���false
	// �v���C���[���U���{�^�������������ǂ���
	isAttack = false;			// �U�����Ă��Ȃ���false
	// �v���C���[���ǂ̕����������Ă��邩
//	m_dir = kDirFront;			// ���ʂ������Ă���̐��ʂ������Ă����kDirFront

	// �p�b�h���͎擾
	int Pad = GetJoypadInputState(DX_CHECKINPUT_PAD);
	// �L�[���͎擾
	int Key = CheckHitKey(DX_CHECKINPUT_KEY);


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
	if (CheckHitKey(KEY_INPUT_UP) == 1)
	{
		isMove = false;
		m_dir = kDirUp;

		// �f�o�b�O�p
	//	m_pos.y -= kSpeed;

	}
	// ����
	if (CheckHitKey(KEY_INPUT_DOWN) == 1)
	{
		isMove = true;
		m_dir = kDirDown;

		// �f�o�b�O�p
		//m_pos.y += kSpeed;
	}
	// ���ړ�
	if (CheckHitKey(KEY_INPUT_LEFT) == 1)
	{
		m_pos.x -= kSpeed;
		isMove = true;
		m_dir = kDirLeft;
	}
	// �E�ړ�
	if (CheckHitKey(KEY_INPUT_RIGHT) == 1)
	{
		m_pos.x += kSpeed;
		isMove = true;
		m_dir = kDirRight;
	}
	// �W�����v�{�^���������Ă��āA�n�ʂɂ��Ă�����W�����v
	if (Key::IsTrigger(KEY_INPUT_Z) && m_pos.y == Ground)	//IsTrigger
	{
		// �W�����v�����x
		for (int i = 0; i < kJump; i++) {
			JumpPower += 0.5f;
		}
		isJumpFlag = true;
		isMove = true;
	}
	// �X�y�[�X�L�[�������Ă�����U��
	if (Key::IsTrigger(KEY_INPUT_SPACE))
	{
		isAttack = true;
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


	// �ҋ@&���E�ړ��A�j���[�V�����t���[��
	if (isMove == false)	//  && isJumpFlag == false
	{
		// �ҋ@��ԃA�j���[�V����
		PlayerAnim++;
		if (PlayerAnim >= FrameCycle)
		{
			PlayerAnim = 0;
		}
	}
	else if (isMove == true)
	{
		// ���E�ړ��A�j���[�V����
		PlayerAnim++;
		if (PlayerAnim >= FrameCycle)
		{
			PlayerAnim = 0;
		}
	}
	else if (isMove == true && m_dir == kDirDown)
	{
		// ���Ⴊ�݃A�j���[�V����
		PlayerAnim++;
		if (PlayerAnim >= FrameCycle)
		{
			PlayerAnim = 0;
		}
	}
	else if (isJumpFlag == true)
	{
		// �W�����v�A�j���[�V����
		PlayerAnim++;
		if (PlayerAnim >= FrameCycle)
		{
			PlayerAnim = 0;
		}
	}
	else if (isAttack == true)
	{
		// �U���A�j���[�V����
		PlayerAnim++;
		if (PlayerAnim >= FrameCycle)
		{
			PlayerAnim = 0;
		}
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

	// �v���C���[�A�j���[�V����
	int PlayerFrame = PlayerAnim / kAnimFrameNum;
	int srcX = Frame[PlayerFrame] * 16;
	int srcX2 = Frame[PlayerFrame] * 32;

	// �v���C���[�̒ʏ헧���G(�摜�̒�����؂蔲���Ċg�傷��)
	if (isMove == false && isJumpFlag == false && isAttack == false)
	{
		DrawRectExtendGraph(m_pos.x, m_pos.y,
			m_pos.x + kWidth, m_pos.y + kHeight,
			srcX + 2, 64, 13, 16,
			Graph, true);
	}
	// �v���C���[���ړ�
	else if (isMove == true && m_dir == kDirLeft && isJumpFlag == false && isAttack == false)
	{
		DrawRectExtendGraph(m_pos.x, m_pos.y,
			m_pos.x + kWidth, m_pos.y + kHeight,
			srcX + 97, 79, 13, 16,
			Graph, true);
	}
	// �v���C���[�E�ړ�
	else if (isMove == true && m_dir == kDirRight && isJumpFlag == false && isAttack == false)
	{
		DrawRectExtendGraph(m_pos.x, m_pos.y,
			m_pos.x + kWidth, m_pos.y + kHeight,
			srcX + 2, 79, 13, 16,
			Graph, true);
	}
	// �v���C���[���Ⴊ��
	else if (isMove == true && m_dir == kDirDown && isAttack == false)
	{
		DrawRectExtendGraph(m_pos.x, m_pos.y,
			m_pos.x + kWidth, m_pos.y + kHeight,
			srcX + 2, 32, 13, 16,
			Graph, true);
	}
	// �v���C���[�W�����v
	else if (isJumpFlag == true && isAttack == false)
	{
		DrawRectExtendGraph(m_pos.x, m_pos.y,
			m_pos.x + kWidth, m_pos.y + kHeight,
			srcX + 97, 64, 13, 16,
			Graph, true);
	}
	// �v���C���[�U��
	else if (isAttack == true)
	{
		DrawRectExtendGraph(m_pos.x, m_pos.y - kWidth * 1.1,
			m_pos.x + kWidth, m_pos.y + kHeight,
			srcX2 + 3, 0, 26, 32,
			Graph, true);
	}

	// �v���C���[�̌��ݍ��W�\��
	DrawFormatString(0, 0, GetColor(255, 255, 255),
		"���ݍ��W:(%.2f,%.2f)", m_pos.x, m_pos.y);
	// �v���C���[�̌��ݑ̗͕\��
	DrawFormatString(0, 19, GetColor(255, 255, 255),
		"PlayerHP:(%d)", PlayerHP);

	DrawFormatString(0, 38, GetColor(255, 255, 255),
		"isMove:(%d)", isMove);
	DrawFormatString(0, 57, GetColor(255, 255, 255),
		"isAttack:(%d)", isAttack);
	DrawFormatString(0, 76, GetColor(255, 255, 255),
		"m_dir:(%d)", m_dir);

#ifdef _DEBUG
	// �����蔻��̕\��
	m_colRect.Draw(GetColor(255, 0, 0), false);
#endif
}

void Player::OnDamage()
{
	// �_���[�W���o���͍ēx�H���Ȃ�
	if (m_damageFrame > 0)	return;
	// ���o�t���[������ݒ肷��
	m_damageFrame = kDamageFrame;
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

