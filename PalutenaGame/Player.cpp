#include "DxLib.h"
#include "Player.h"

#include "SceneMain.h"
#include "MozueyeEnemy.h"
#include "DeathYourEnemy.h"
#include "PumpkinEnemy.h"
#include "Shot/Shot.h"
#include "Game.h"
#include "Pad.h"

namespace
{
	// �L�����N�^�[�̃T�C�Y
	constexpr int kWidth = 32;
	constexpr int kHeight = 32;

	// �ړ����x
	constexpr float kSpeed = 3.0f;
	// �W�����v����
	constexpr float kJump = 13.0f;

	// ��{�L�����A�j���[�V����		// ���[�V�����̃t���[�����Ƃɍ�蒼��
	constexpr int DefFrame[] = { 0,1,2,3,4,5};
	// ��{�L�����A�j���[�V������1�R�}�̃t���[����
	constexpr int DefAnimFrameNum = 8;
	// ��{�L�����A�j���[�V����1�T�C�N���̃t���[����
	constexpr int DefFrameCycle = _countof(DefFrame) * DefAnimFrameNum;

	// ���S���L�����A�j���[�V������R�}�̃t���[����
	constexpr int DeathAnimFrameNum = 50;
	// ��{�L�����A�j���[�V����1�T�C�N���̃t���[����
	constexpr int DeathFrameCycle = _countof(DefFrame) * DeathAnimFrameNum;


	// �_���[�W���o�t���[����
	constexpr int kDamageFrame = 60;
}

Player::Player(SceneMain* pMain) :
	m_pMain(pMain),
	Graph(-1)
{
}

Player::~Player()
{
}

void Player::Init()
{
	HP = 100;						// �v���C���[�̏���HP
	m_pos.x = kScreenWidth / 2;	// �v���C���[�̏����ʒux
	m_pos.y = 100;				// �v���C���[�̏����ʒuy
	m_dir = kDirFront;			// �v���C���[�̏�������(���ʂ�flont)
	m_shotDir = kShotDirRight;
	JumpPower = 0.0f;			// �v���C���[�̏����W�����v
	Gravity = 0.0f;				// �v���C���[�̏����d��
	Atk = 1;					// �v���C���[�̏����U����
	PlayerAnim = 0;				// �v���C���[�A�j���[�V�����̏�����
	m_damageFrame = 0;			// �v���C���[��_���A�j���[�V����  
	isMove = false;				// �ړ���ԃt���O(�ے��false)
	isAttack = false;			// �U���t���O(�ے��false)
	isDeath = false;			// ���S�t���O(�ے��false)
	m_damageFrame = 0;
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

	// �v���C���[�����S���Ă��Ȃ��Ƃ��͍s���ł���
	if (!PlayerDeath()) {

		// ���L�[�������Ă�����v���C���[���ړ�������
		// �����
		if (CheckHitKey(KEY_INPUT_UP) == 1)
		{
			isMove = false;
			m_dir = kDirUp;
			m_shotDir = kShotDirUp;
		}
		// ����
		if (CheckHitKey(KEY_INPUT_DOWN) == 1)
		{
			isMove = true;
			m_dir = kDirDown;
		}
		// ���ړ�
		if (CheckHitKey(KEY_INPUT_LEFT) == 1)
		{
			m_pos.x -= kSpeed;
			isMove = true;
			m_dir = kDirLeft;

			m_shotDir = kShotDirLeft;
		}
		// �E�ړ�
		if (CheckHitKey(KEY_INPUT_RIGHT) == 1)
		{
			m_pos.x += kSpeed;
			isMove = true;
			m_dir = kDirRight;
			m_shotDir = kShotDirRight;
		}
		// �W�����v�{�^���������Ă��āA�n�ʂɂ��Ă�����W�����v
		if (Pad::IsTrigger(PAD_INPUT_1) && m_pos.y == Ground)
		{
			// �W�����v�����x
			for (int i = 0; i < kJump; i++) {
				JumpPower += 0.5f;
			}
			isJumpFlag = true;
			isMove = true;
		}
		// �X�y�[�X�L�[�������Ă�����U��
		if (Pad::IsTrigger(PAD_INPUT_10))
		{
			// �V���b�g�������̊m��
			Shot* pShot = new Shot();

			pShot->SetMain(m_pMain);
			pShot->SetPlayer(this);
			pShot->init();
			pShot->Start(m_pos);
			isAttack = true;
			// �ȍ~�X�V�⃁�����̊J����SceneMain�ɔC����
			m_pMain->AddShot(pShot);
		}
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
		if (PlayerAnim >= DefFrameCycle)
		{
			PlayerAnim = 0;
		}
	}
	else if (isMove == true)
	{
		// ���E�ړ��A�j���[�V����
		PlayerAnim++;
		if (PlayerAnim >= DefFrameCycle)
		{
			PlayerAnim = 0;
		}
	}
	else if (isMove == true && m_dir == kDirDown)
	{
		// ���Ⴊ�݃A�j���[�V����
		PlayerAnim++;
		if (PlayerAnim >= DefFrameCycle)
		{
			PlayerAnim = 0;
		}
	}
	else if (isJumpFlag == true)
	{
		// �W�����v�A�j���[�V����
		PlayerAnim++;
		if (PlayerAnim >= DefFrameCycle)
		{
			PlayerAnim = 0;
		}
	}
	else if (isAttack == true)
	{
		// �U���A�j���[�V����
		PlayerAnim++;
		if (PlayerAnim >= DefFrameCycle)
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
	int PlayerFrame = PlayerAnim / DefAnimFrameNum;
	int srcX = DefFrame[PlayerFrame] * 16;
	int srcX2 = DefFrame[PlayerFrame] * 32;

	// �v���C���[�̒ʏ헧���G(�摜�̒�����؂蔲���Ċg�傷��)
	if (isMove == false && isJumpFlag == false && isAttack == false && isDeath == false)
	{
		DrawRectExtendGraph(m_pos.x, m_pos.y,
			m_pos.x + kWidth, m_pos.y + kHeight,
			srcX + 2, 64, 13, 16,
			Graph, true);
	}
	// �v���C���[���ړ�
	else if (isMove == true && m_dir == kDirLeft && isJumpFlag == false && isAttack == false && isDeath == false)
	{
		DrawRectExtendGraph(m_pos.x, m_pos.y,
			m_pos.x + kWidth, m_pos.y + kHeight,
			srcX + 97, 79, 13, 16,
			Graph, true);
	}
	// �v���C���[�E�ړ�
	else if (isMove == true && m_dir == kDirRight && isJumpFlag == false && isAttack == false && isDeath == false)
	{
		DrawRectExtendGraph(m_pos.x, m_pos.y,
			m_pos.x + kWidth, m_pos.y + kHeight,
			srcX + 2, 79, 13, 16,
			Graph, true);
	}
	// �v���C���[���Ⴊ��
	else if (isMove == true && m_dir == kDirDown && isAttack == false && isDeath == false)
	{
		DrawRectExtendGraph(m_pos.x, m_pos.y,
			m_pos.x + kWidth, m_pos.y + kHeight,
			srcX + 2, 32, 13, 16,
			Graph, true);
	}
	// �v���C���[�W�����v
	else if (isJumpFlag == true && isAttack == false && isDeath == false)
	{
		DrawRectExtendGraph(m_pos.x, m_pos.y,
			m_pos.x + kWidth, m_pos.y + kHeight,
			srcX + 97, 64, 13, 16,
			Graph, true);
	}
	// �v���C���[�U��
	else if (isAttack == true && isDeath == false)
	{
		DrawRectExtendGraph(m_pos.x, m_pos.y - kWidth * 1.1,
			m_pos.x + kWidth, m_pos.y + kHeight,
			srcX2 + 3, 0, 26, 32,
			Graph, true);
	}
	// �U���{�^����IsTrigger�ɂ��Ă���ׁAisAttack����u�����������Ă��Ȃ��B
	// �@�Ȃ̂ŋ��炭�A��u�`�悵����Ƀf�t�H���g�̕`��ɖ߂��Ă���͗l�B
	// �@�ŏI�I�ɂ́A1���[�v���̃A�j���[�V�����͓����Ăق���

	SetFontSize(16);
	// �v���C���[�̌��ݍ��W�\��
	DrawFormatString(80, 0, GetColor(255, 255, 255),
		"���ݍ��W:(%.2f,%.2f)", m_pos.x, m_pos.y);
	// �v���C���[�̌��ݑ̗͕\��
	DrawFormatString(80, 19, GetColor(255, 255, 255),
		"PlayerHP:(%d)", HP);

#ifdef _DEBUG
	DrawFormatString(80, 38, GetColor(255, 255, 255),
		"isMove:(%d)", isMove);
	DrawFormatString(80, 57, GetColor(255, 255, 255),
		"isAttack:(%d)", isAttack);
	DrawFormatString(80, 76, GetColor(255, 255, 255),
		"m_dir:(%d)", m_dir);

	// �����蔻��̕\��
	m_colRect.Draw(GetColor(255, 0, 0), false);
#endif
}

void Player::Death()
{
	if (isDeath == true)
	{
		// ���S���A�j���[�V����
		PlayerAnim++;
		if (PlayerAnim >= DeathFrameCycle)
		{
			PlayerAnim = 0;
		}

		// �v���C���[�A�j���[�V����
		int DeathPlayerFrame = PlayerAnim / DefAnimFrameNum;
		int srcX2 = DefFrame[DeathPlayerFrame] * 16;

		// ���l�܂鏊�A��x�ŏI�t���[��(6)�܂ŗ����炻��ȍ~�͌v�Z���Ȃ��悤�ɂ�����
		// �@����������A���Ƀ��[�V�����̍Ō�̃R�}�Ŏ~�܂葱����B
		// bool�ň��������~�܂�悤�ɂ���̂�����

		DrawRectExtendGraph(m_pos.x, m_pos.y,
			m_pos.x + kWidth, m_pos.y + kHeight,
			srcX2, 48, 15, 17,
			Graph, true);
	}
}

void Player::End()
{
	// �w�i������������폜
	DeleteGraph(Graph);
}

void Player::OnDamage_Mozu()
{
	// �_���[�W���o���͍ēx�H���Ȃ�
	if (m_damageFrame > 0)	return;

	// �v���C���[��HP���A�G�̍U���͕����炷
	HP -= m_mozueyeEnemy->GetEnemyAtk();

	// HP��0�ȉ��ɂȂ����ꍇ�A�v���C���[�̎��S�t���O��true�ɂ���
	if (HP <= 0)
	{
		isDeath = true;
	}

	// ���o�t���[������ݒ肷��
	m_damageFrame = kDamageFrame;

#ifdef _DEBUG
	// �G�ƃv���C���[�̓����蔻�肪����������
	printfDx("��������\n");
#endif
}

void Player::OnDamage_Death()
{
	// �_���[�W���o���͍ēx�H���Ȃ�
	if (m_damageFrame > 0) return;

	// �v���C���[��HP���A�G�̍U���͕����炷
	HP -= m_dethYourEnemy->GetEnemyAtk();

	// HP��0�ȉ��ɂȂ����ꍇ�A�v���C���[�̎��S�t���O��true�ɂ���
	if (HP <= 0)
	{
		isDeath = true;
	}

	// ���o�t���[������ݒ肷��
	m_damageFrame = kDamageFrame;

#ifdef _DEBUG
	// �G�ƃv���C���[�̓����蔻�肪����������
	printfDx("��������\n");
#endif
}

void Player::OnDamage_Pump()
{
	// �_���[�W���o���͍ēx�H���Ȃ�
	if (m_damageFrame > 0)	return;

	// �v���C���[��HP���A�G�̍U���͕����炷
	HP -= m_pumpkinEnemy->GetEnemyAtk();

	// HP��0�ȉ��ɂȂ����ꍇ�A�v���C���[�̎��S�t���O��true�ɂ���
	if (HP <= 0)
	{
		isDeath = true;
	}

	// ���o�t���[������ݒ肷��
	m_damageFrame = kDamageFrame;

#ifdef _DEBUG
	// �G�ƃv���C���[�̓����蔻�肪����������
	printfDx("��������\n");
#endif
}
