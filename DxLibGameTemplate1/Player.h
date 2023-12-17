#pragma once
#include "Vec2.h"
#include "Rect.h"
class Player
{
public:

	// �����Ă������
	enum Dir
	{
		kDirFront,	// ����
		kDirDown,	// ��
		kDirLeft,	// ��
		kDirRight,	// �E
		kDirUp,		// ��
	};


	Player();
	~Player();

	void Init();
	void Update();
	void Draw();

private:
	// �v���C���[�̉摜
	int Graph;		// �ʏ�ҋ@
	// �v���C���[�̉摜�T�C�Y
	int W, H;
	// �v���C���[�̗̑�
	int HP;

	// �\���ʒu
	Vec2 m_pos;
	// �����Ă������
	Dir m_dir;
	// �ҋ@��ԃA�j���[�V����
	float IdleAnimation;
	// ���E�ړ��A�j���[�V����
	float RunAnimation;
	// ���Ⴊ�݃A�j���[�V����
	float SquatAnimation;

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

