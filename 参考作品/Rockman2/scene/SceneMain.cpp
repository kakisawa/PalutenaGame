#include "SceneMain.h"
#include "DxLib.h"
#include "Pad.h"
#include "Rect.h"
#include "Game.h"
#include "Bg.h"
#include "ScenePause.h"

#include "RecoverySmallHp.h"
#include "RecoveryGreatHp.h"
#include "RecoverySmallShot.h"
#include "RecoveryGreatShot.h"
#include "RecoveryLife.h"
#include "RecoveryFullHp.h"

#include "Player.h"

#include "ShotBase.h"

#include "Matasaburo.h"
#include <cassert>

namespace
{
	// ��ʓ���1�x�ɏo����e��
	constexpr int kShotMax = 3;
	// 1�x�ɓo��ł���G��
	constexpr int kEnemyMax = 20;
	// ��ʓ���1�x�ɏo����񕜃A�C�e����
	constexpr int kRecoveryMax = 50;

	// �v���C���[�̉摜�T�C�Y
	constexpr int kPlayerWidth = 32;
	constexpr int kPlayerHeight = 64;

	// �}�b�v�`�b�v�̃T�C�Y
	constexpr int kMapChipWidth = 32;
	constexpr int kMapChipHeight = 32;

	// �|�[�Y��ʂ̕����\���ʒu
	constexpr int kTextPosX = 510;
	// �o�[�̕\���ʒu
	constexpr int kBarPosX = 540;
	// �o�[�̕\���Ԋu
	constexpr int kBarInterval = 8;

	// �o�[�̎l�p�̃T�C�Y
	constexpr int kBarWidth = 5;
	constexpr int kBarHeight = 20;

	// Y���W�̕\���ʒu�̊Ԋu
	constexpr int kInterval = 60;
	// �����A�o�[�̕\���ʒu
	constexpr int kDisPosY = 200;
}

SceneMain::SceneMain():
	m_drawValue(0),
	m_isGetFullHpRecovery(false),
	m_isExistLineMove(false),
	m_isSceneGameOver(false),
	m_isSceneClear(false)
{
	// �v���C���[�̃O���t�B�b�N���[�h
	m_playerHandle = LoadGraph("data/image/player.png");
	assert(m_playerHandle != -1);
	m_bgHandle = LoadGraph("data/image/backGround.png");
	assert(m_bgHandle != -1);
	m_mapHandle = LoadGraph("data/image/map.png");
	assert(m_mapHandle != -1);
	m_enemyHandle = LoadGraph("data/image/Enemy/matasaburo.png");
	assert(m_bgHandle != -1);

	// �v���C���[�̃������m��
	m_pPlayer = new Player{ this };
	m_pPlayer->SetHandle(m_playerHandle);	// Player�ɃO���t�B�b�N�̃n���h����n��

	// �w�i�̃������m��
	m_pBg = new Bg;
	m_pBg->SetHandle(m_bgHandle);
	m_pBg->SetMapHandle(m_mapHandle);
	m_pBg->SetPlayer(m_pPlayer);
	m_pPlayer->SetBg(m_pBg);

	// �|�[�Y��ʂ̃������m��
	m_pPause = new ScenePause{ m_pPlayer };

	// �V���b�g�̏�����
	m_pShot.resize(kShotMax);
	for (int i = 0; i < m_pShot.size(); i++)
	{
		m_pShot[i] = nullptr; // ���g�p��Ԃɂ���
	}

	// �G�̏�����
	m_pEnemy.resize(kEnemyMax);
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		m_pEnemy[i] = nullptr; // ���g�p��Ԃɂ���
	}

	// �񕜃A�C�e���̏�����
	m_pRecovery.resize(kRecoveryMax);
	for (int i = 0; i < m_pRecovery.size(); i++)
	{
		m_pRecovery[i] = nullptr; // ���g�p��Ԃɂ���
	}
}

SceneMain::~SceneMain()
{
	// ����������O���t�B�b�N���폜
	DeleteGraph(m_playerHandle);
	DeleteGraph(m_bgHandle);
	DeleteGraph(m_enemyHandle);

	// �w�i�̃��������
	delete m_pBg;
	m_pBg = nullptr;

	// �|�[�Y��ʂ̃������m��
	delete m_pPause;
	m_pPause = nullptr;

	// �v���C���[�̃��������
	delete m_pPlayer;
	m_pPlayer = nullptr;

	// �V���b�g�̃��������
	for (int i = 0; i < m_pShot.size(); i++)
	{
		if (m_pShot[i])
		{
			// nullptr�łȂ��ꍇ�Anullptr������
			delete m_pShot[i];
			m_pShot[i] = nullptr;
		}
	}

	// �G�̃��������
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		if (m_pEnemy[i])
		{
			// nullptr�łȂ��ꍇ�Anullptr������
			delete m_pEnemy[i];
			m_pEnemy[i] = nullptr;
		}
	}

	// �񕜃A�C�e���̃��������
	for (int i = 0; i < m_pRecovery.size(); i++)
	{
		if (m_pRecovery[i])
		{
			// nullptr�łȂ��ꍇ�Anullptr������
			delete m_pRecovery[i];
			m_pRecovery[i] = nullptr;
		}
	}
}

void SceneMain::Init()
{
	// ��ʑJ�ڂ̏�����
	m_isSceneGameOver = false;
	m_isSceneClear = false;
	m_isExistLineMove = false;

	// �|�[�Y��ʂ̏�����
	m_pPause->Init();

	// �v���C���[�̏�����
	assert(m_pPlayer);	// m_pPlayer == nullptr�̏ꍇ�~�܂�
	m_pPlayer->Init();

	// �w�i�̏�����
	m_pBg->Init();
	

	// �G�̏�����
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		if (m_pEnemy[i])
		{
			m_pEnemy[i]->Init();
		}
	}

	// �񕜃A�C�e���̏�����
	for (int i = 0; i < m_pRecovery.size(); i++)
	{
		if (m_pRecovery[i])
		{
			m_pRecovery[i]->Init();
		}
	}
}

void SceneMain::End()
{
}

void SceneMain::Update()
{
	// �v���C���[�̎c�@��0�����̏ꍇ
	if (m_pPlayer->GetLife() < 0)
	{
		m_isSceneGameOver = true; // �Q�[���I�[�o�[��ʂɑJ��
	}

	// TODO:�{�X��|������N���A��ʂɑJ�ڂ���
	// C�L�[�ŃN���A��ʂɈړ�����悤�ɂ���
	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if (Pad::IsTrigger(pad & PAD_INPUT_3))
	{
		m_isSceneClear = true; // �N���A��ʂɑJ��
	}

	// �|�[�Y��ʂ̍X�V
	m_pPause->Update();

	// �|�[�Y��ʂ��\������Ă���ꍇ��ʂ��~�߂�
	if (m_pPause->IsExist())
	{
		return;
	}

	// �w�i�̍X�V
	m_pBg->Update();

	// �v���C���[�̍X�V
	m_pPlayer->Update();

	m_playerPos = m_pPlayer->GetPos();		// �v���C���[�̌��ݒn���擾
	Rect playerRect = m_pPlayer->GetColRect();	// �v���C���[�̓����蔻��

	// �v���C���[�������W�ɓ��B������G��o�ꂳ����
	if (m_pPlayer->GetPos().x > 100 && m_pPlayer->GetPos().x < 103)
	{
		CreateMatasaburo();
	}

	// �v���C���[����ʓ��Ɉړ�������E�ʂ�\������
	if (m_playerPos.x >= 100 && !m_isGetFullHpRecovery)
	{
		DropFullHpRecovery();
	}

	// �e�̍X�V
	for (int i = 0; i < m_pShot.size(); i++)
	{
		// nullptr�Ȃ珈���͍s��Ȃ�
		if (!m_pShot[i]) continue;

		m_pShot[i]->Update();

		// �A�C�e��2���̏ꍇ
		if (m_pShot[i]->GetShotType() == ShotType::kShotLineMove)
		{
			// ��ʏ�ɑ��݂��邩
			if (m_pShot[i]->IsExist())
			{
				m_isExistLineMove = true;
			}
			else
			{
				m_isExistLineMove = false;
			}

			// �e�̓����蔻��
			Rect shotRect = m_pShot[i]->GetColRect();
			if (playerRect.IsCollision(shotRect))
			{
				m_pPlayer->RideLineMove(shotRect);
			}
		}

		// ��ʊO�ɏo���烁�������������
		if (!m_pShot[i]->IsExist())
		{
			delete m_pShot[i];
			m_pShot[i] = nullptr;
		}
	}

	// �G�̍X�V
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		// nullptr�Ȃ珈���͍s��Ȃ�
		if (!m_pEnemy[i]) continue;
		m_pEnemy[i]->Update();

		// �g�p�ς݂̓G�L�����N�^�[���폜
		if (!m_pEnemy[i]->IsExist())
		{
			// �m���ŃA�C�e�����h���b�v
			int getRandDrop = GetRand(100);

			if (getRandDrop <= 10)
			{
				DropHpSmallRecovery(i); // HP��(��)
			}
			else if (getRandDrop <= 15)
			{
				DropHpGreatRecovery(i);	// HP��(��)
			}
			else if (getRandDrop <= 25)
			{
				DropShotSmallRecovery(i); // �e�G�l���M�[(��)
			}
			else if (getRandDrop <= 30)
			{
				DropShotGreatRecovery(i); // �e�G�l���M�[(��)
			}
			else if (getRandDrop <= 32)
			{
				DropLifeRecovery(i);	// �c�@
			}
			
			// ���������������
			delete m_pEnemy[i];
			m_pEnemy[i] = nullptr;	// nullptr������
		}
		else
		{
			// �G�ƃv���C���[�̓����蔻��
			Rect enemyRect = m_pEnemy[i]->GetColRect();
			if (playerRect.IsCollision(enemyRect))
			{
				m_pPlayer->OnDamage();
			}

			for (int j = 0; j < m_pShot.size(); j++)
			{
				// nullptr�Ȃ珈���͍s��Ȃ�
				if (!m_pShot[j]) continue;

				// �G�ƒe�̓����蔻��
				// �A�C�e���Q���̏ꍇ�͓G�Ƃ̓����蔻��𖳎�����
				if (m_pShot[j]->GetShotType() != ShotType::kShotLineMove)
				{
					Rect shotRect = m_pShot[j]->GetColRect(); // �e�̓����蔻��
					if (shotRect.IsCollision(enemyRect))
					{
						m_pEnemy[i]->OnDamage();
					}
					if (enemyRect.IsCollision(shotRect))
					{
						// �e���폜
						delete m_pShot[j];
						m_pShot[j] = nullptr;
					}
				}
			}
		}
	}

	// �񕜃A�C�e���̍X�V
	for (int i = 0; i < m_pRecovery.size(); i++)
	{
		// nullptr�Ȃ珈���͍s��Ȃ�
		if (!m_pRecovery[i]) continue;

		m_pRecovery[i]->Update();

		Rect recoveryRect = m_pRecovery[i]->GetColRect();	// �񕜃A�C�e���̓����蔻��
		// �v���C���[�Ɖ񕜃A�C�e���̓����蔻��
		if (playerRect.IsCollision(recoveryRect))
		{
			if (dynamic_cast<RecoverySmallHp*>(m_pRecovery[i])) // HP����
			{
				m_pPlayer->HpSmallRecovery();
			}
			else if (dynamic_cast<RecoveryGreatHp*>(m_pRecovery[i])) // HP���
			{
				m_pPlayer->HpGreatRecovery();
			}
			else if (dynamic_cast<RecoverySmallShot*>(m_pRecovery[i])) // �e����
			{
				m_pPlayer->ShotSmallRecovery();
			}
			else if (dynamic_cast<RecoveryGreatShot*>(m_pRecovery[i])) // �e���
			{
				m_pPlayer->ShotGreatRecovery();
			}
			else if (dynamic_cast<RecoveryLife*>(m_pRecovery[i])) // �c�@��
			{
				m_pPlayer->LifeRecovery();
			}
			else if (dynamic_cast<RecoveryFullHp*>(m_pRecovery[i])) // HP�S��
			{
				if (!m_isGetFullHpRecovery)  // E�ʂ��擾���ĂȂ��ꍇ
				{
					m_pPlayer->GetHpFullRecovery();
					m_isGetFullHpRecovery = true;
				}
			}

			// �擾������A�C�e��������
			delete m_pRecovery[i];
			m_pRecovery[i] = nullptr;
		}
	}
}

void SceneMain::Draw()
{
	// �`���X�N���[�����N���A����
	ClearDrawScreen();

	// �w�i�̕`��
	m_pBg->Draw();

	// �v���C���[�̕`��
	m_pPlayer->Draw();

	// �e�̕`��
	for (int i = 0; i < m_pShot.size(); i++)
	{
		// nullptr�Ȃ珈���͍s��Ȃ�
		if (!m_pShot[i])continue;
		m_pShot[i]->Draw();
	}

	// �G�̕`��
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		// nullptr�Ȃ珈���͍s��Ȃ�
		if (!m_pEnemy[i])continue;
		m_pEnemy[i]->Draw();
	}

	// �񕜃A�C�e���̕`��
	for (int i = 0; i < m_pRecovery.size(); i++)
	{
		// nullptr�Ȃ珈���͍s��Ȃ�
		if (!m_pRecovery[i])continue;
		m_pRecovery[i]->Draw();
	}

	// ���݂�HP�������l�p��`�悷��
	for (int i = 0; i < m_pPlayer->GetHp(); i++)
	{
		DrawBox(10, 10 + 10 * i, 40, (10 + 10 * i) + 5, 0xeee8aa, true);
	}

	// ���ݑI�𒆂̕���̒e��������ɕ\��
	if (m_pPlayer->IsMetal()) // ���^��
	{
		for (int i = 0; i < m_pPlayer->GetMetalEnergy(); i++)
		{
			DrawBox(50, 10 + 10 * i, 80, (10 + 10 * i) + 5, 0xc0c0c0, true);
		}
	}
	if (m_pPlayer->IsFire()) // �t�@�C�A
	{
		for (int i = 0; i < m_pPlayer->GetFireEnergy(); i++)
		{
			DrawBox(50, 10 + 10 * i, 80, (10 + 10 * i) + 5, 0xff4500, true);
		}
	}
	if (m_pPlayer->IsLineMove()) // 2��
	{
		for (int i = 0; i < m_pPlayer->GetLineEnergy(); i++)
		{
			DrawBox(50, 10 + 10 * i, 80, (10 + 10 * i) + 5, 0xb22222, true);
		}
	}

	// �|�[�Y��ʂ̕\��
	m_pPause->Draw();

	/*�|�[�Y��ʕ\����*/
	if (m_pPause->IsExist())
	{
		// ���݂�HP��\��
		DrawFormatString(kTextPosX, kDisPosY, 0xffffff, "P :");
		for (int i = 0; i < m_pPlayer->GetHp(); i++) // ���݂�HP�������l�p��`�悷��
		{
			DrawBox(kBarPosX + kBarInterval * i, kDisPosY, (kBarPosX + kBarInterval * i) + kBarWidth, kDisPosY + kBarHeight, 0xeee8aa, true);
		}

		// ���݂̒e�G�l���M�[����\��
		// ���^��
		DrawFormatString(kTextPosX, kDisPosY + kInterval, 0xffffff, "M :");
		for (int i = 0; i < m_pPlayer->GetMetalEnergy(); i++) // ���݂̃G�l���M�[�������l�p��`�悷��
		{
			DrawBox(kBarPosX + kBarInterval * i, kDisPosY + kInterval, (kBarPosX + kBarInterval * i) + kBarWidth, kDisPosY + kInterval + kBarHeight, 0xeee8aa, true);
		}

		// �t�@�C�A�[
		DrawFormatString(kTextPosX, kDisPosY + kInterval * 2, 0xffffff, "F :");
		for (int i = 0; i < m_pPlayer->GetFireEnergy(); i++) // ���݂̃G�l���M�[�������l�p��`�悷��
		{
			DrawBox(kBarPosX + kBarInterval * i, kDisPosY + kInterval * 2, (kBarPosX + kBarInterval * i) + kBarWidth, kDisPosY + kInterval * 2 + kBarHeight, 0xeee8aa, true);
		}

		// �A�C�e��2��
		DrawFormatString(kTextPosX, kDisPosY + kInterval * 3, 0xffffff, "2 :");
		for (int i = 0; i < m_pPlayer->GetLineEnergy(); i++) // ���݂̃G�l���M�[�������l�p��`�悷��
		{
			DrawBox(kBarPosX + kBarInterval * i, kDisPosY + kInterval * 3, (kBarPosX + kBarInterval * i) + kBarWidth, kDisPosY + kInterval * 3 + kBarHeight, 0xeee8aa, true);
		}

		// ���݂�E�ʐ���\��
		DrawFormatString(kTextPosX, kDisPosY + kInterval * 4, 0xffffff, "E : %d", m_pPlayer->GetFullHpRecovery());

		// ���݂̎c�@����\��
		DrawFormatString(kTextPosX, kDisPosY + kInterval * 5, 0xffffff, "�c�@��:%d", m_pPlayer->GetLife());
	}
}

/*�e�̐���*/
bool SceneMain::AddShot(ShotBase* pShot)
{
	// nullptr��n���ꂽ��~�܂�
	assert(pShot);

	for (int i = 0; i < m_pShot.size(); i++)
	{
		// �g�p���Ȃ玟�̃`�F�b�N���s��
		if (m_pShot[i])continue;

		// m_pShot[i] == nullptr�Ȃ̂ŐV�����o�^����
		m_pShot[i] = pShot;

		// �o�^������I��
		return true;
	}

	// m_pShot�Ƀ|�C���^��o�^�ł��Ȃ�����
	delete pShot;
	return false;
}

/*�A�C�e���h���b�v*/
void SceneMain::DropHpSmallRecovery(int enemyIndex) // HP����
{
	for (int i = 0; i < m_pRecovery.size(); i++)
	{
		if (!m_pRecovery[i])
		{
			m_pRecovery[i] = new RecoverySmallHp;
			m_pRecovery[i]->Start(m_pEnemy[enemyIndex]->GetPos());
			m_pRecovery[i]->Init();
			return;
		}
	}
}

void SceneMain::DropHpGreatRecovery(int enemyIndex) // HP���
{
	for (int i = 0; i < m_pRecovery.size(); i++)
	{
		if (!m_pRecovery[i])
		{
			m_pRecovery[i] = new RecoveryGreatHp;
			m_pRecovery[i]->Start(m_pEnemy[enemyIndex]->GetPos());
			m_pRecovery[i]->Init();
			return;
		}
	}
}

void SceneMain::DropShotSmallRecovery(int enemyIndex) // �e����
{
	for (int i = 0; i < m_pRecovery.size(); i++)
	{
		if (!m_pRecovery[i])
		{
			m_pRecovery[i] = new RecoverySmallShot;
			m_pRecovery[i]->Start(m_pEnemy[enemyIndex]->GetPos());
			m_pRecovery[i]->Init();
			return;
		}
	}
}

void SceneMain::DropShotGreatRecovery(int enemyIndex) // �e���
{
	for (int i = 0; i < m_pRecovery.size(); i++)
	{
		if (!m_pRecovery[i])
		{
			m_pRecovery[i] = new RecoveryLife;
			m_pRecovery[i]->Start(m_pEnemy[enemyIndex]->GetPos());
			m_pRecovery[i]->Init();
			return;
		}
	}
}

void SceneMain::DropLifeRecovery(int enemyIndex) // �c�@��
{
	for (int i = 0; i < m_pRecovery.size(); i++)
	{
		if (!m_pRecovery[i])
		{
			m_pRecovery[i] = new RecoveryGreatShot;
			m_pRecovery[i]->Start(m_pEnemy[enemyIndex]->GetPos());
			m_pRecovery[i]->Init();
			return;
		}
	}
}

void SceneMain::DropFullHpRecovery() // HP�S��
{
	for (int i = 0; i < m_pRecovery.size(); i++)
	{
		if (!m_pRecovery[i])
		{
			m_pRecovery[i] = new RecoveryFullHp;
			m_pRecovery[i]->Start({ 500, 500 }); // �A�C�e���̈ʒu��ݒ�
			m_pRecovery[i]->Init();
			return;
		}
	}
}

/*�G�̐���*/
void SceneMain::CreateMatasaburo()
{
	//�g���Ă��Ȃ��ꏊ�ɃA�h���X��ۑ�����
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		if (!m_pEnemy[i])	// nullptr�ł��邱�Ƃ��`�F�b�N����
		{
			m_pEnemy[i] = new Matasaburo;
			m_pEnemy[i]->SetHandle(m_enemyHandle);
			m_pEnemy[i]->Start();
			m_pEnemy[i]->Init();
			return;	// 1�̕����������m�ۂł����炻�̎��_�ŏI��
		}
	}
}
