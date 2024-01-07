#pragma once
#include "Vec2.h"
#include "Rect.h"
class Player
{
public:
	Player();
	~Player();

	void Init();
	void Update();
	void Draw();

public:
	// �v���C���[�̗̑�
	int PlayerHP;

private:
	// �v���C���[�̉摜
	int Graph;		// �ʏ�ҋ@
	// �v���C���[�̉摜�T�C�Y
	int W, H;

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
};

