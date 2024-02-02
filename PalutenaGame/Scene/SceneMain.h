#pragma once
#include <vector>
#include "Vec2.h"

namespace
{
	// ���Y�A�C�ő�o����
	constexpr int MozuMax = 7;
	// ���ő�o����
	constexpr int DeathMax = 5;
	// ���ڂ���ő�o����
	constexpr int PumpMax = 3;

	// ��ʓ��ɓ����ɏo����e�̐�
	constexpr int kShotMax = 30;

	// ���t���[�������ɓG���o�ꂷ�邩
	constexpr int kEnemyInterval = 60;
}

// �N���X�錾
class Player;
class Back;
class MozueyeEnemy;
class DeathYourEnemy;
class PumpkinEnemy;
class Shot;
class Time;
class SoundManager;

class SceneMain
{
public:
	SceneMain();
	virtual ~SceneMain();

	void Init();
	void Update();
	void Draw();

	void Clear();	// �N���A���̏���
	void Death();	// ���S���̏���
	void End();		


	// �V�[�����I������������
	bool IsSceneEnd() const;
	// ������̓V�[���I�����̃t���O
	// �N���A�ƃQ�[���I�[�o�[�͕ʂɂ�������������������Ȃ��B

	// ���ǂ̃X�e�[�W�ɍs����
	bool ToGameOver() const;
	bool ToGameClear() const;

	// �V���b�g��ǉ�����
	// �o�^�ł��Ȃ������ꍇ��false��Ԃ�
	// �o�^�ł��Ȃ������ꍇ�͓�����pShot�������
	bool AddShot(Shot* pShot);
	
private:
	// �G�L�����N�^�[�̐���
	void CreateEnemyMozu();
	void CreateEnemyDeath();
	void CreateEnemyPump();

	// �O���t�B�b�N�̃n���h��
	int m_gameScreenHandle;	

	int m_playerHandle;		// �v���C���[
	int m_enemyHandle;		// �G
	int m_backHandle;		// �w�i

	// �G�l�~�[
	int m_mozueyeEnemy;			// ���Y�A�C
	int m_deathYourEnemyGraph;	// ���O�����̎�
	int m_pumpkinEnemyGraph;	// �p���v�L���N

	int m_fadeAlpha;		// �t�F�[�h�C���A�A�E�g
	int m_enemyInterval;	// �G�̓o��Ԋu

	// �V�[������
	bool m_isSceneEnd;		// �V�[�����I�����鎞true�ɂ���

	bool isToGameOver;		// �Q�[���I�[�o�[��ʂɍs����
	bool isToGameClear;		// �Q�[���N���A��ʂɍs���� 

	// �v���C���[
	Player* m_pPlayer;
	// �e
	Shot* m_pShot[kShotMax];
	// �w�i
	Back* m_pBack;
	// ��������
	Time* m_pTime;
	// SE/BGM
	SoundManager* m_pSoundManager;
	// �G�l�~�[
	std::vector<MozueyeEnemy*> m_pMozueyeEnemy;
	std::vector<DeathYourEnemy*> m_pDeathYourEnemy;
	std::vector<PumpkinEnemy*> m_pPumpkinEnemy;
};