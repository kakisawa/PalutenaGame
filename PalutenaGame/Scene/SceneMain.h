#pragma once
#include <vector>
#include "Vec2.h"

namespace
{
	constexpr int MozuMax = 4;			// ���Y�A�C�ő�o����
	constexpr int DeathMax = 10;		// ���ő�o����
	constexpr int PumpMax = 3;			// ���ڂ���ő�o����
	constexpr int kShotMax = 30;		// ��ʓ��ɓ����ɏo����e�̐�
	constexpr int kEnemyInterval = 50;	// ���t���[�������ɓG���o�ꂷ�邩
}

// �N���X�錾
class Player;
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

	void BgDraw();			// �w�i�̕`��
	void DrawDoor();		// �G�̏o���ʒu���`��
	void CharactorDraw();	// �L�����N�^�[�n�̕`��
	void StartDraw();		// �Q�[���J�n�O�̐����`��
	void CoundownDraw();	// ������Q�[���J�n�J�E���g�_�E���`��

	void Clear();	// �N���A���̏���
	void Death();	// ���S���̏���

	bool AddShot(Shot* pShot);	// �V���b�g��ǉ�����

	bool IsSceneEnd() const;	// �V�[�����I�������邩
	bool IsToGameOver() const;	// �Q�[���I�����Q�[���I�[�o�[�V�[���Ɍ�����
	bool IsToGameClear() const;	// �Q�[���N���A���Q�[���N���A�V�[���Ɍ�����

private:
	// �G�L�����N�^�[�̐���
	void CreateEnemyMozu();	// ���Y�A�C
	void CreateEnemyDeath();// ��
	void CreateEnemyPump();	// �p���v�L��

	int m_gameScreenHandle;	// �Q�[����ʃT�C�Y�̃O���t�B�b�N�f�[�^
	int m_enemyHandle;		// �G
	int m_backHandle;		// �w�i
	int m_backGroundHandle;	// �w�i(��)
	int m_door;				// �G�o����

	int m_explanation;		// ����
	int m_key_A;			//�uA�{�^���Ō���v�O���t
	int m_count1;			// �J�E���g1
	int m_count2;			// �J�E���g2
	int m_count3;			// �J�E���g3

	int m_mozueyeEnemy;			// ���Y�A�C
	int m_deathYourEnemyGraph;	// ��
	int m_pumpkinEnemyGraph;	// �p���v�L��

	int m_fadeAlpha;		// �t�F�[�h�C���A�A�E�g
	int m_enemyInterval;	// �G�̓o��Ԋu
	int m_startCount;		// �Q�[���X�^�[�g�J�E���g
	int m_doorCount;		// �G�o�����̕`��J�E���g

	bool m_isStartFlag;		// �Q�[�����n�܂�O�̐����t���O
	bool m_isStartCountFlag;// ������Q�[���J�n�J�E���g�t���O
	bool m_isSceneEnd;		// �V�[���t���O

	bool m_isToGameOver;		// �Q�[���I�[�o�[��ʂɍs�����̃t���O
	bool m_isToGameClear;		// �Q�[���N���A��ʂɍs�����̃t���O

	// �v���C���[
	Player* m_pPlayer;
	// �e
	Shot* m_pShot[kShotMax];
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