#include "ScenePause.h"
#include "Player.h"
#include "Game.h"
#include "Pad.h"
#include "DxLib.h"

namespace
{
	// �|�[�Y��ʂ̃T�C�Y
	constexpr int kWidth = 280;
	constexpr int kHeight = 480;

	// �|�[�Y��ʂ̈ʒu
	constexpr int kPosX = (Game::kScreenWidth - kWidth) / 2;
	constexpr int kPosY = Game::kScreenHeight / 6;

	// �I�𒆂̎l�p��Y���W�̏����ʒu
	constexpr int kInitSelectPosY = 195;
	// �l�p�̕`��̊Ԋu
	constexpr int kSelectPosY = 60;
}

ScenePause::ScenePause(Player* pPlayer):
	m_select(kBuster),
	m_pPlayer(pPlayer),
	m_isExist(false)
{
}

ScenePause::~ScenePause()
{
}

void ScenePause::Init()
{
	m_isExist = false;
	m_select = kBuster;
	m_selectPos.x = 0;
	m_selectPos.y = kInitSelectPosY;
}

void ScenePause::Update()
{
	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	/*A�L�[���������烁�j���[��\���A��\��*/
	if (Pad::IsTrigger(pad & PAD_INPUT_4))
	{
		if (!m_isExist)
		{
			m_isExist = true; // �\������
		}
		else
		{
			m_isExist = false;
		}
	}

	// �\����
	if (m_isExist)
	{
		// ���L�[����������I����Ԃ�1������
		if (Pad::IsTrigger(pad & PAD_INPUT_DOWN))
		{
			m_select = (m_select + 1) % kSelectNum;
			m_selectPos.y += kSelectPosY; // �I�𒆂̎l�p�����Ɉړ�

			// �I�𒆂̎l�p����ԉ��ɂ�������l�p����ԏ�ɖ߂�
			if (m_selectPos.y > kInitSelectPosY + kSelectPosY * 4)
			{
				m_selectPos.y = kInitSelectPosY;
			}
		}
		// ���L�[����������I����Ԃ�1�グ��
		if (Pad::IsTrigger(pad & PAD_INPUT_UP))
		{
			m_select = (m_select + (kSelectNum - 1)) % kSelectNum;
			m_selectPos.y -= kSelectPosY;	// �I�𒆂̎l�p����Ɉړ�

			if (m_selectPos.y < kInitSelectPosY)
			{
				m_selectPos.y = kInitSelectPosY + kSelectPosY * 4;
			}
		}

		// X�L�[���������猻�ݑI�𒆂̕���ɕύX����
		if (Pad::IsTrigger(pad & PAD_INPUT_2))
		{
			// �I�𒆂̕�����擾
			bool isBuster = false;
			bool isMetal = false;
			bool isFire = false;
			bool isLineMove = false;
			// �|�[�Y��ʂ���邩�ǂ���	true:����
			bool isClosePause = true; 

			switch (m_select)
			{
			case kBuster:
				// �o�X�^�[�ɐ؂�ւ���
				isBuster = true;
				break;
			case kMetal:
				// ���^���ɐ؂�ւ���
				isMetal = true;
				break;
			case kFire:
				// �t�@�C�A�ɐ؂�ւ���
				isFire = true;
				break;
			case kLine:
				// 2���ɐ؂�ւ���
				isLineMove = true;
				break;
			case kFullRecovery:
				// E�ʂ�1�ł������Ă�����HP�S��
				if (m_pPlayer->GetFullHpRecovery() > 0)
				{
					m_pPlayer->HpFullRecovery();
				}
				isClosePause = false; // �|�[�Y��ʂ���Ȃ��悤�ɂ���
				break;
			default:
				break;
			}

			// �v���C���[�̕����ύX����
			if (m_select != kFullRecovery)
			{
				m_pPlayer->ChangeShot(isBuster, isMetal, isFire, isLineMove);
			}
			// �|�[�Y��ʂ����
			if (isClosePause)
			{
				m_isExist = false;
			}
		}
	}
}

void ScenePause::Draw()
{
	if (m_isExist)
	{
		// �|�[�Y��ʂ̎l�p��\��
		SetDrawBlendMode(DX_BLENDMODE_MULA, 200);
		DrawBox(kPosX, kPosY, kPosX + kWidth, kPosY + kHeight, 0x000000, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);// �\�����[�h�����ɖ߂�
		DrawBox(kPosX, kPosY, kPosX + kWidth, kPosY + kHeight, 0xffffff, false); // �g��`��
		DrawString(kPosX ,150, "�|�[�Y���", 0xffffff);

		// �I�𒆂̕������l�p�ŕ`��
		DrawBox(505, m_selectPos.y, 770, m_selectPos.y + 30, 0x00bfff, false);
	}
}
