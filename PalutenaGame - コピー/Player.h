#pragma once
#include "Vec2.h"
#include "Rect.h"

class SceneExplanation;
class SceneMain;
class SceneSecond;
class MozueyeEnemy;
class DeathYourEnemy;
class PumpkinEnemy;
class Shot;
class SoundManager;

// �����Ă������
enum Dir
{
	kDirFront,	// ����
	kDirDown,	// ��
	kDirLeft,	// ��
	kDirRight,	// �E
	kDirUp,		// ��
};

// �e��������
enum ShotDir
{
	kShotDirLeft,	// ��
	kShotDirRight,	// �E
	kShotDirUp,		// ��
};

class Player
{
public:
	Player();
	Player(SceneMain* pMain);
	Player(SceneSecond* pSceneSecond);

	~Player();

	void Init();
	void Update();
	void Draw();
	void End();

	void OnDamage_Mozu();	// �v���C���[��_������(�G_���Y�A�C)
	void OnDamage_Death();	// �v���C���[��_������(�G_��)
	void OnDamage_Pump();	// �v���C���[��_������(�G_�p���v�L��)
	void Death();			// �v���C���[���S������

public:
	void SetHandle(int handle) { Graph = handle; }		// �����o�[�ϐ��ɃA�N�Z�X����
	Rect GetColRect() const { return m_colRect; }		// �v���C���[�̓����蔻����擾����
	Vec2 OutPos() const { return m_pos; }				// �v���C���[�̍��W���擾����
	bool PlayerDeath() const { return isDeath; }		// �v���C���[�̐�����Ԃ��擾����
 	int GetAtk() const { return Atk; }					// �v���C���[�̍U���͂��擾����
	ShotDir OutShotDir() const { return m_shotDir; }	// �v���C���[���ǂ̕����������Ă��邩���擾����
	void AddScore(int Score) { m_Score += Score; }		// �X�R�A
	
	int GetScore() const { return m_Score; }

	// �G�̍U���͂��l�����邽��
	void SetMozu(MozueyeEnemy* pMozu) { m_pMozueyeEnemy = pMozu; }
	void SetDeath(DeathYourEnemy* pDeath) { m_pDeathYourEnemy = pDeath; }
	void SetPump(PumpkinEnemy* pPump) { m_pPumpkinEnemy = pPump; }
private:
	SceneExplanation* m_pExplanation;
	SceneMain* m_pMain;
	SceneSecond* m_pSecond;
	MozueyeEnemy* m_pMozueyeEnemy;
	DeathYourEnemy* m_pDeathYourEnemy;
	PumpkinEnemy* m_pPumpkinEnemy;
	Shot* m_pShot;
	SoundManager* m_pSoundManager;

	int HP;		// �v���C���[�̗̑�
	int Atk;	// �v���C���[�̍U����
	int m_Score;	// �v���C���[�̊l���X�R�A
	int Graph;	// �v���C���[�̉摜
	int W, H;	// �v���C���[�̉摜�T�C�Y
	int m_damageFrame;	// �_���[�W���󂯂Ă���̃t���[����
							// ���i��0�ŁA�����������Ƀt���[������ݒ肵��
							// �ȍ~���t���[�����炵�Ă���

	float Gravity;		// �d��
	float JumpPower;	// �W�����v�ړ���
	float PlayerAnim;	// �v���C���[�A�j���[�V����

	int SoundJump;		// �W�����v�T�E���h
	int SoundAttack;	// �U���T�E���h

	Vec2 m_pos;			// �\���ʒu
	Dir m_dir;			// �����Ă������
	ShotDir m_shotDir;	
	Rect m_colRect;		// �����蔻��p�̋�`

	bool isMove;		// �v���C���[���ړ������ǂ����̃t���O
	bool isTurn;		// �v���C���[�̍��E���]�󋵂ɂ��Ẵt���O
	bool isJumpFlag;	// �v���C���[���W�����v�����ǂ����̃t���O
	bool isAttack;		// �v���C���[���U���������ǂ����̃t���O
	bool isDeath;		// �v���C���[�����S�������ǂ����̃t���O
};