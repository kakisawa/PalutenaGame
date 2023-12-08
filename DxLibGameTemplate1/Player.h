#pragma once
#include "Vec2.h"
class Player
{
public:

	// �����Ă������
	enum Dir
	{
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
	int Graph;
	// �v���C���[�̉摜�T�C�Y
	int W, H;

	// �d��
	float Gravity;
	// �����ړ���
	float FallPowor;
	// �W�����v�ړ���
	float JumpPower;
	// �\���ʒu
	Vec2 m_pos;
	// �����Ă������
	Dir m_dir;

public:
	// �v���C���[���]�t���O
	bool isTurn;
	// �ړ������ǂ����̃t���O
	bool isMove;
	// �W�����v�����ǂ����̃t���O
	int isPushFlag;
};

