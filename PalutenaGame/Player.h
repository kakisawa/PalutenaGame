#pragma once
#include "Vec2.h"
#include "Rect.h"

class SceneMain;
class Player
{
public:
	Player(SceneMain* pMain);
	~Player();

	void Init();
	void Update();
	void Draw();

	void End();

public:

	// �����o�[�ϐ��ɃA�N�Z�X����
	void SetHandle(int handle) { Graph = handle; }
	// �v���C���[�̓����蔻����擾����
	Rect GetColRect() const { return m_colRect; }
	// �v���C���[�̗̑�
	int PlayerHP;

	// �v���C���[���_���[�W���󂯂�
	void OnDamage();

private:

	SceneMain* m_pMain;

	// �v���C���[�̉摜
	int Graph;		
	// �v���C���[�̉摜�T�C�Y
	int W, H;

	int m_damageFrame;		// �_���[�W���󂯂Ă���̃t���[����
							// ���i��0�ŁA�����������Ƀt���[������ݒ肵��
							// �ȍ~���t���[�����炵�Ă���

	// �����Ă������
	enum Dir
	{
		kDirFront,	// ����
		kDirDown,	// ��
		kDirLeft,	// ��
		kDirRight,	// �E
		kDirUp,		// ��
	};

	// �\���ʒu
	Vec2 m_pos;
	// �����Ă������
	Dir m_dir;
	// �v���C���[�A�j���[�V����
	float PlayerAnim;
	// enum��bool��ς���
	// �d��
	float Gravity;
	// �W�����v�ړ���
	float JumpPower;

	// �����蔻��p�̋�`
	Rect m_colRect;

	// �v���C���[���ړ������ǂ����̃t���O
	bool isMove;
	// �W�����v�����ǂ����̃t���O
	bool isJumpFlag;
	// �v���C���[���U���������ǂ����̃t���O
	bool isAttack;
};