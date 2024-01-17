#include "Player.h"
#include "DxLib.h"
#include "Game.h"
#include "Pad.h"
#include "Bg.h"
#include "SceneMain.h"
#include "ShotBuster.h"
#include "ShotMetal.h"
#include "ShotFire.h"
#include "ShotLineMove.h"
#include "RecoveryBase.h"
#include <cassert>

// Player�Ŏg�p����萔
namespace
{
	// �ړ����x
	constexpr float kSpeed = 4.0f;
	// �d��
	constexpr float kGravity = 0.5f;
	// �����x
	constexpr float kVelocity = -12.0f;

	// �v���C���[�̃T�C�Y
	constexpr int kPlayerWidth = 32;
	constexpr int kPlayerHeight = 64;

	// �}�b�v�`�b�v�̃T�C�Y
	constexpr int kMapWidth = 32;
	constexpr int kMapHeight = 32;

	// �_���[�W���o�̃t���[����
	constexpr int kDamageFrame = 60;

	// �v���C���[�̏����ʒu
	constexpr float kPosX = 30.0f;
	constexpr float kPosY = 500.0f;

	// �v���C���[�̍ő�HP
	constexpr float kMaxHp = 28;
	// �ő�e�G�l���M�[
	constexpr float kMaxShot = 28;
	// �c�@
	constexpr int kLife = 10;

	// �A�C�e���̉񕜗�
	constexpr float kSmallRecovery = 2;		// ���A�C�e��
	constexpr float kGreatRecovery = 10;	// ��A�C�e��

	// �A�C�e��2���̃T�C�Y
	constexpr int kShotWidth = 32;
}


Player::Player(SceneMain* pMain) :
	m_pMain(pMain),
	m_pBg(nullptr),
	m_pos(kPosX, kPosY),
	m_move(0.0f, 0.0f),
	m_colRect(),
	m_handle(-1),
	m_isRight(true),
	m_isGround(false),
	m_jumpFrame(0),
	m_hp(kMaxHp),
	m_life(kLife),
	m_fullHpRecovery(0),
	m_damageFrame(0),
	m_metalEnergy(28),
	m_fireEnergy(28),
	m_lineEnergy(28),
	m_isBuster(false),
	m_isMetal(false),
	m_isFire(false),
	m_isLineMove(false),
	m_keyState(0),
	m_pressTime(0),
	m_nowPressTime(0)
{
}

Player::~Player()
{
}

/*����������*/
void Player::Init()
{
	// ���݈ʒu
	m_pos.x = kPosX;
	m_pos.y = kPosY;
	// ����
	m_isRight = true;
	// �W�����v�t���O
	m_isGround = false;
	// �����x
	m_move.y = 0.0f;
	// HP
	m_hp = kMaxHp;
	// �c�@��
	m_life = kLife;
	// �_���[�W�̃t���[����
	m_damageFrame = 0;
	// �J�n���̓o�X�^�[��łĂ�悤�ɂ���
	m_isBuster = true;
	m_isMetal = false;
	m_isFire = false;
	m_isLineMove = false;
}

/*�v���C���[�̍X�V*/
void Player::Update()
{
	// �p�b�h���g�p����
	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	/*������������E�Ɉړ�*/
	if (pad & PAD_INPUT_RIGHT)
	{
		m_isRight = true;
		m_move.x = kSpeed;
	}
	/*�����������獶�Ɉړ�*/
	else if (pad & PAD_INPUT_LEFT)
	{
		m_isRight = false;
		m_move.x = -kSpeed;
	}
	else
	{
		m_move.x = 0;
	}

	/*��ʊO�ɏo�����ʓ��ɖ߂�*/
	if (m_pos.x < 0.0f + kPlayerWidth * 0.5)
	{
		m_pos.x = 0.0f + kPlayerWidth * 0.5;
	}
	if (m_pos.y < 0.0f)
	{
		m_pos.y = 0.0f;
	}

	/*�v���C���[�����ɗ��������ꍇ*/
	if ((m_pos.y - kPlayerHeight * 0.5f) > Game::kScreenHeight)
	{
		// �c�@��1���炷
		m_life--;
		if (m_life >= 0)
		{
			// �c�@��0�ȏゾ������v���C���[�������ʒu�ɖ߂�
			m_pos.x = kPosX;
			m_pos.y = kPosY;
		}
	}

	/*�_���[�W���o*/
	m_damageFrame--;
	if (m_damageFrame < 0)
	{
		m_damageFrame = 0;
	}

	/*�n�ʂɐڂ��Ă���*/
	if (m_isGround)
	{
		m_jumpFrame = 0;
		m_move.y = 0.0f;

		/*Space�ŃW�����v*/
		if (Pad::IsTrigger(PAD_INPUT_10))
		{
			m_isGround = false;
			m_move.y = kVelocity;
		}

		CheckHitMap();
	}
	/*�W�����v��*/
	else
	{
		m_jumpFrame++;	// �W�����v�t���[���̍X�V

		//�{�^���𗣂����u�ԂɃW�����v����
		if (Pad::IsRelease(PAD_INPUT_10))
		{
			// �W�����v�̍��������߂�
			float jumpHeight;

			if (m_jumpFrame < 10) // ����������10�t���[���ȉ�
			{
				jumpHeight = 0.5f;
			}
			else if (m_jumpFrame < 30) // 30�t���[���ȉ�
			{
				jumpHeight = 0.8f;
			}
			else	// 30�t���[���ȏ�
			{
				jumpHeight = 1.0f;
			}
			m_move.y *= jumpHeight;
		}
		m_move.y += kGravity; // �����x�ɏd�͂𑫂�

		CheckHitMap();
	}

	/*�o�X�^�[����*/
	if (m_isBuster)
	{
		if (Pad::IsTrigger(PAD_INPUT_1))
		{
			ShotBuster* pShot = new ShotBuster;

			// �V�����e�𐶐�����
			pShot->Init();
			pShot->SetMain(m_pMain);
			pShot->SetPlayer(this);
			pShot->Start(m_pos);
			// �ȍ~�X�V�⃁�����̉����SceneMain�ɔC����
			m_pMain->AddShot(pShot);
		}

	}

	/*���^������*/
	if (m_isMetal)
	{
		if (Pad::IsTrigger(PAD_INPUT_1))
		{
			if (m_metalEnergy > 0)
			{
				ShotMetal* pShot = new ShotMetal;
				// �V�����e�𐶐�����
				pShot->Init();
				pShot->SetMain(m_pMain);
				pShot->SetPlayer(this);
				pShot->Start(m_pos);
				// �ȍ~�X�V�⃁�����̉����SceneMain�ɔC����
				m_pMain->AddShot(pShot);

				if (pShot->IsExist())
				{
					// �e�G�l���M�[��0.25���炷
					m_metalEnergy -= 0.25f;
				}
			}
			else
			{
				m_metalEnergy = 0;
			}
		}
	}

	/*�t�@�C���[����*/
	if (m_isFire)
	{
	// �L�[�������ꂽ�u�Ԃ��擾
		if (Pad::IsTrigger(PAD_INPUT_1))
		{
			m_pressTime = GetNowCount();
		}
		// �L�[��������Ă��邩����
		if (Pad::IsPress(PAD_INPUT_1))
		{
			m_nowPressTime = GetNowCount() - m_pressTime; // �{�^���������ė����܂ł̎���
		}
		// �L�[�������ꂽ�u�Ԃ𔻒�
		if (Pad::IsRelease(PAD_INPUT_1))
		{
			if (m_fireEnergy > 0) // �e�G�l���M�[��0�ȏ�
			{
				if (m_nowPressTime < 2000) // ���������Ԃ�2�b�ȉ�
				{
					m_fireEnergy--; // �e�G�l���M�[��1���炷
				}
				else if (m_nowPressTime < 5000) // ���������Ԃ�5�b�ȉ�
				{
					if (m_fireEnergy - 6 < 0) // �e�G�l���M�[������Ȃ��ꍇ
					{
						m_fireEnergy--; // �e�G�l���M�[��1���炷
					}
					else
					{
						m_fireEnergy -= 6; // �e�G�l���M�[��6���炷
					}
				}
				else // ���������Ԃ�5�b�ȏ�
				{
					if (m_fireEnergy - 10 < 0) // �e�G�l���M�[������Ȃ��ꍇ
					{
						m_fireEnergy--; // �e�G�l���M�[��1���炷
					}
					else
					{
						m_fireEnergy -= 10; // �e�G�l���M�[��10���炷
					}
				}

				// �V�����e�𐶐�����
				ShotFire* pShot = new ShotFire;
				pShot->Init();
				pShot->SetMain(m_pMain);
				pShot->SetPlayer(this);
				pShot->Start(m_pos);
				// �ȍ~�X�V�⃁�����̉����SceneMain�ɔC����
				m_pMain->AddShot(pShot);
			}
			else // �e�G�l���M�[��0�ȉ�
			{
				m_fireEnergy = 0; // ���݂̒e�G�l���M�[��0�ɂ���
			}
		}
	}
	
	/*�A�C�e��2������*/
	if (m_isLineMove)
	{
		// �{�^�����������甭��
		if (Pad::IsTrigger(PAD_INPUT_1))
		{
			if (!m_pMain->GetIsExistLineMove() && m_lineEnergy > 0)
			{
				ShotLineMove* pShot = new ShotLineMove;
				// �V�����e�𐶐�����
				pShot->Init();
				pShot->SetMain(m_pMain);
				pShot->SetPlayer(this);
				pShot->Start(m_pos);
				// �ȍ~�X�V�⃁�����̉����SceneMain�ɔC����
				m_pMain->AddShot(pShot);
			}
		}

		// ��ʓ��ɂ���ꍇ
		if (m_pMain->GetIsExistLineMove())
		{
			m_lineEnergy -= 0.03f; // �G�l���M�[�����炷
		}
	}

	// �����蔻��X�V
	m_colRect.SetCenter(m_pos.x, m_pos.y, kPlayerWidth, kPlayerHeight);

	/*if (m_pos.y > 500)
	{
		m_pos.y = 500;
	}*/
}

void Player::Draw()
{
	// �������W��������W�ɕϊ�
	int x = m_pos.x - kPlayerWidth * 0.5f;
	int y = m_pos.y - kPlayerHeight * 0.5f;

	// �X�N���[���ʂ𔽉f����
	x -= m_pBg->GetScrollX();
	y -= m_pBg->GetScrollY();

	if (m_isRight) // �E�������Ă���ꍇ
	{
		DrawGraph(x, y, m_handle, false);
	}
	else // ���������Ă���ꍇ
	{
		DrawTurnGraph(x, y, m_handle, false);
	}

	// �_���[�W���o
	// 2�t���[���Ԋu�ŕ\����\����؂�ւ���
	if (m_damageFrame % 4 >= 2) return;

#ifdef _DEBUG
	// MEMO:�X�N���[�������f����Ȃ����߃R�����g�A�E�g
	// �����蔻��̕\��
	//m_colRect.Draw(0x0000ff, false);
#endif
}

void Player::CheckHitMap()
{
	Rect chipRect; // ���������}�b�v�`�b�v�̋�`

	// �����瓖���������`�F�b�N����
	m_pos.x += m_move.x;
	//if (m_pBg->IsCollision(GetColRect(), chipRect)) // �ǂɓ�������
	//{
	//	if (m_move.x > 0.0f && m_pos.x + m_move.x >= chipRect.GetLeft() - (kPlayerHeight * 0.5f))
	//	{
	//		m_move.x = chipRect.GetLeft() - m_pos.y - (kPlayerWidth * 0.5);
	//		m_pos.x += m_move.x;
	//	}
	//	else if (m_move.x < 0.0f) // �������Ɉړ�
	//	{
	//		m_pos.x = chipRect.GetRight() + kPlayerWidth * 0.5 + 1;
	//	}
	//}

	// �c���瓖���������`�F�b�N����
	m_pos.y += m_move.y;
	if (m_pBg->IsCollision(GetColRect(), chipRect))
	{
		if (m_move.y > 0.0f && m_pos.y + m_move.y >= chipRect.GetTop() - (kPlayerHeight * 0.5f)) // �n�ʂɐڒn
		{
			m_move.y = static_cast<float>(chipRect.GetTop() - (m_pos.y + (kPlayerHeight * 0.5f)));
			m_pos.y += m_move.y;
			m_isGround = true;
		}
		//else if (m_pos.y + m_move.y <= chipRect.GetBottom() - (kPlayerHeight * 0.5f)) // ������Ɉړ�
		//{
		//	m_move.y = chipRect.GetBottom() - (m_pos.y + (kPlayerHeight * 0.5f));
		//	m_pos.y -= m_move.y;
		//	m_move.y *= -1.0f;
		//}
	}
	else // �n�ʂɂ���Ԃ����Ă��Ȃ�
	{
		m_isGround = false;
	}
}

/*�e�̑I����Ԃ��X�V*/
void Player::ChangeShot(bool isBuster, bool isMetal, bool isFire, bool isLineMove)
{
	// �o�X�^�[�̑I����Ԃ��X�V
	m_isBuster = isBuster;

	// ���^���̑I����Ԃ��X�V
	m_isMetal = isMetal;

	// �t�@�C�A�̑I����Ԃ��X�V
	m_isFire = isFire;

	// 2���̑I����Ԃ��X�V
	m_isLineMove = isLineMove;
}

/*�v���C���[�̃_���[�W���o*/
void Player::OnDamage()
{
	// �_���[�W���o���͖��G��ԂɂȂ�
	if (m_damageFrame > 0) return;

	// ���o�t���[������ݒ肷��
	m_damageFrame = kDamageFrame;

	// HP�����炷
	m_hp--;

	if (m_hp <= 0)
	{
		m_life--;		// �c�@��1���炷
		m_hp = kMaxHp;	// HP�S��
	}
}

/*E�ʎ擾*/
void Player::GetHpFullRecovery()
{
	m_fullHpRecovery += 1;
}

/*��*/
void Player::HpSmallRecovery() // HP����
{
	m_hp += kSmallRecovery;
	if (m_hp > kMaxHp) // �ő�HP�𒴂����ꍇ
	{
		m_hp = kMaxHp;
	}
}

void Player::HpGreatRecovery() // HP���
{
	m_hp += kGreatRecovery;
	if (m_hp > kMaxHp) // �ő�HP�𒴂����ꍇ
	{
		m_hp = kMaxHp;
	}
}

void Player::ShotSmallRecovery() // �e����
{
	if (m_isMetal) // ���^��
	{
		m_metalEnergy += kSmallRecovery;
		if (m_metalEnergy > kMaxShot)
		{
			m_metalEnergy = kMaxShot;
		}
	}
	else if (m_isFire) // �t�@�C�A
	{
		m_fireEnergy += kSmallRecovery;
		if (m_fireEnergy > kMaxShot)
		{
			m_fireEnergy = kMaxShot;
		}
	}
	else if (m_isLineMove) // 2��
	{
		m_isLineMove += kSmallRecovery;
		if (m_isLineMove > kMaxShot)
		{
			m_isLineMove = kMaxShot;
		}
	}
}

void Player::ShotGreatRecovery() // �e���
{
	if (m_isMetal) // ���^��
	{
		m_metalEnergy += kGreatRecovery;
		if (m_metalEnergy > kMaxShot)
		{
			m_metalEnergy = kMaxShot;
		}
	}
	else if (m_isFire) // �t�@�C�A
	{
		m_fireEnergy += kGreatRecovery;
		if (m_fireEnergy > kMaxShot)
		{
			m_fireEnergy = kMaxShot;
		}
	}
	else if (m_isLineMove) // 2��
	{
		m_isLineMove += kSmallRecovery;
		if (m_isLineMove > kMaxShot)
		{
			m_isLineMove = kMaxShot;
		}
	}
}

void Player::LifeRecovery() // �c�@��
{
	m_life += 1;	// �c�@��1���₷
	if (m_life > 99)
	{
		m_life = 99;
	}
}

void Player::HpFullRecovery() // HP�S��
{
	if (m_fullHpRecovery > 0)
	{
		if (m_hp < kMaxHp) // ���݂�HP���ő�HP����
		{
			m_hp += kMaxHp;	// HP���ő�܂ŉ�
			if (m_hp > kMaxHp) // �ő�HP�𒴂����ꍇ
			{
				m_hp = kMaxHp;
			}
			m_fullHpRecovery--; // ��������1���炷
		}
	}
	else
	{
		m_fullHpRecovery = 0;
	}
}

/*�A�C�e��2���ɏ�����ۂ̏���*/
void Player::RideLineMove(Rect shotRect)
{
 	Rect lineMoveRect = shotRect; // �A�C�e��2���̓����蔻��

	// ��ɏ�����ꍇ
	if (m_colRect.GetBottom() >= lineMoveRect.GetTop()) 
	{
		m_pos.y = lineMoveRect.GetTop() - kPlayerHeight;
		m_isGround = true;

		// �v���C���[�����Ɉړ�
		m_pos.x += lineMoveRect.GetCenter().x - m_colRect.GetCenter().x;

		// �W�����v
		if (Pad::IsTrigger(PAD_INPUT_10))
		{
			m_isGround = false;
			m_move.y = kVelocity;
		}

		// �����蔻��̍X�V
		m_colRect.SetCenter(m_pos.x + static_cast<float>(kPlayerWidth) / 2, m_pos.y + static_cast<float>(kPlayerHeight) / 2, kPlayerWidth, kPlayerHeight);
	}
}
