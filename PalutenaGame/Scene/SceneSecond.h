#pragma once
#include <vector>
#include "Vec2.h"

namespace
{
	// ���Y�A�C�o����
	constexpr int MozuSecondMax = 5;	// 17
	// ���o����
	constexpr int DeathSecondMax = 2;	// 3
	// ���ڂ���o����
	constexpr int PumpSecondMax = 3;	// 10���A�o���ĂȂ�

	// ��ʓ��ɓ����ɏo����e�̐�
	constexpr int kShotSecondMax = 30;

	// ���t���[�������ɓG���o�ꂷ�邩
	constexpr int kEnemySecondInterval = 60;
}

// �N���X�錾
class Player;
class Back;
class SceneMain;
class MozueyeEnemy;
class DeathYourEnemy;
class PumpkinEnemy;
class Shot;
class Time;
class SoundManager;

class SceneSecond
{
public:
	SceneSecond();
	virtual ~SceneSecond();

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

	// ���O�ɂ��̃X�e�[�W��V��ł������ǂ����̃t���O
	bool JustFinishStage2() const { return isFinishStage2; }

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

	bool isFinishStage2;	// ���O�Ƀv���C�����X�e�[�W�𔻒肷�邽�߂̃t���O
	// �Q�[���I������true�ɂ���

	bool isToGameOver;		// �X�e�[�W�Z���N�g��ʂɍs����
	bool isToGameClear;		// �����V�[���ɍs���� 

	// �������邵���Ȃ�������...
	// ���ԕs��
	SceneMain* m_pSceneMain;

	// �v���C���[
	Player* m_pPlayer;
	// �e
	Shot* m_pShot[kShotSecondMax];
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

