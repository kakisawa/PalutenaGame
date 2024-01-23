#pragma once
#include "Vec2.h"
#include "Rect.h"

class SceneMain;
class MozueyeEnemy;
class DeathYourEnemy;
class PumpkinEnemy;
class Shot;

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
	Player(SceneMain* pMain);
	~Player();

	void Init();
	void Update();
	void Draw();
	void End();

	void OnDamage_Mozu();	// �v���C���[��_������(�G_���Y�A�C)
	void OnDamage_Death();	// �v���C���[��_������(�G_��)
	void OnDamage_Pump();	// �v���C���[��_������(�G_�p���v�L��)
	void Death();		// �v���C���[���S������

public:

	void SetHandle(int handle) { Graph = handle; }		// �����o�[�ϐ��ɃA�N�Z�X����
	Rect GetColRect() const { return m_colRect; }		// �v���C���[�̓����蔻����擾����
	Vec2 OutPos() const { return m_pos; }				// �v���C���[�̍��W���擾����
	bool PlayerDeath() const { return isDeath; }		// �v���C���[�̐�����Ԃ��擾����

	ShotDir OutShotDir() const { return m_shotDir; }				// �v���C���[���ǂ̕����������Ă��邩���擾����

	int OutHp = HP;			// �v���C���[HP
	
	// �G�̍U���͂��l�����邽��
	void SetMozu(MozueyeEnemy* pMozu) { m_mozueyeEnemy = pMozu; }
	void SetDeath(DeathYourEnemy* pDeath) { m_dethYourEnemy = pDeath; }
	void SetPump(PumpkinEnemy* pPump) { m_pumpkinEnemy = pPump; }
private:
	SceneMain* m_pMain;
	MozueyeEnemy* m_mozueyeEnemy;
	DeathYourEnemy* m_dethYourEnemy;
	PumpkinEnemy* m_pumpkinEnemy;
	Shot* m_shot;

	int HP;		// �v���C���[�̗̑�
	int Atk;	// �v���C���[�̍U����
	int Graph;	// �v���C���[�̉摜
	int W, H;	// �v���C���[�̉摜�T�C�Y
	int m_damageFrame;	// �_���[�W���󂯂Ă���̃t���[����
							// ���i��0�ŁA�����������Ƀt���[������ݒ肵��
							// �ȍ~���t���[�����炵�Ă���
	float Gravity;		// �d��
	float JumpPower;	// �W�����v�ړ���
	float PlayerAnim;	// �v���C���[�A�j���[�V����

	Vec2 m_pos;			// �\���ʒu
	Dir m_dir;			// �����Ă������
	ShotDir m_shotDir;	
	Rect m_colRect;		// �����蔻��p�̋�`

	bool isMove;		// �v���C���[���ړ������ǂ����̃t���O
	bool isJumpFlag;	// �v���C���[���W�����v�����ǂ����̃t���O
	bool isAttack;		// �v���C���[���U���������ǂ����̃t���O
	bool isDeath;		// �v���C���[�����S�������ǂ����̃t���O
};