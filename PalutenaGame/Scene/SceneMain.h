#pragma once
#include <vector>
#include "Vec2.h"

namespace
{
	// ���Y�A�C�ő�o����
	constexpr int MozuMax = 4;
	// ���ő�o����
	constexpr int DeathMax = 10;
	// ���ڂ���ő�o����
	constexpr int PumpMax = 3;

	// ��ʓ��ɓ����ɏo����e�̐�
	constexpr int kShotMax = 30;

	// ���t���[�������ɓG���o�ꂷ�邩
	constexpr int kEnemyInterval = 50;
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
class ColorManager;
class Pause;

class SceneMain
{
public:
	SceneMain();
	virtual ~SceneMain();

	void Init();
	void Update();
	void Draw();
	void End();

	// �L�����N�^�[�n�̕`��
	void CharactorDraw();
	void StartDraw();
	void CoundownDraw();

	void DrawDoor();

	void Clear();	// �N���A���̏���
	void Death();	// ���S���̏���

	// �V���b�g��ǉ�����
		// �o�^�ł��Ȃ������ꍇ��false��Ԃ�
		// �o�^�ł��Ȃ������ꍇ�͓�����pShot�������
	bool AddShot(Shot* pShot);

	// �V�[�����I������������
	bool IsSceneEnd() const;
	
	// ���ǂ̃X�e�[�W�ɍs����
	bool ToGameOver() const;
	bool ToGameClear() const;

private:
	// �G�L�����N�^�[�̐���
	void CreateEnemyMozu();
	void CreateEnemyDeath();
	void CreateEnemyPump();

	void AppEnemyAnim();

	// �O���t�B�b�N�̃n���h��
	int m_gameScreenHandle;	

	int m_playerHandle;		// �v���C���[
	int m_enemyHandle;		// �G
	int m_backHandle;		// �w�i
	int m_backHandle2;		// �w�i(��)
	int m_door;				// �G�o����

	int m_explanation;		// ����
	int m_key_A;
	int m_count1;			// �J�E���g1
	int m_count2;			// �J�E���g2
	int m_count3;			// �J�E���g3

	// �G�l�~�[
	int m_mozueyeEnemy;			// ���Y�A�C
	int m_deathYourEnemyGraph;	// ���O�����̎�
	int m_pumpkinEnemyGraph;	// �p���v�L���N

	int m_fadeAlpha;		// �t�F�[�h�C���A�A�E�g
	int m_enemyInterval;	// �G�̓o��Ԋu
	int m_startCount;		// �Q�[���X�^�[�g�J�E���g

	int m_doorCount;		// �G�o�����̕`��J�E���g

	// �V�[������
	bool m_isStartFlag;		// �Q�[�����n�܂�O�̐���
	bool m_isStartCountFlag;
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
	// �F
	ColorManager* m_pColorManager;
	// �|�[�Y
	Pause* m_pPause;
	// �G�l�~�[
	std::vector<MozueyeEnemy*> m_pMozueyeEnemy;
	std::vector<DeathYourEnemy*> m_pDeathYourEnemy;
	std::vector<PumpkinEnemy*> m_pPumpkinEnemy;
};