#pragma once
#include "Rect.h"
#include "Vec2.h"
#include "Game.h"

// �v���g�^�C�v�錾
struct Shot;

class Player 
{
public:
	Player();
	~Player();

	void Init();
	void Update(Shot shotArray[], int shotArraySize);
	void Draw();

	// �����蔻��p�̋�`
	Rect m_colRect;
	// �v���C���[�̌��݈ʒu���擾����
	Vec2 GetPos() const { return m_pos; }
	// �v���C���[�̓����蔻����擾����
	Rect GetColRect() const { return m_colRect; }

private:
	// �v���C���[�̉摜
	int Graph;
	// �v���C���[�̉摜�T�C�Y
	int W;
	int H;

	// �����ړ���
	float FallPowor;
	// �W�����v�ړ���
	float JumpPower;

	// �O���t�B�b�N�̃n���h��
	int m_handle;
	// �\���ʒu
	Vec2 m_pos;

public:

	// �v���C���[���]�t���O
	bool isTurn;
	// �v���C���[����������Ă��邩�̃t���O
	bool isLookUp;
	// �v���C���[�����Ⴊ��ł��邩�̃t���O
	bool isSquat;
	// �ړ������ǂ����̃t���O
	bool isMove;
	// �W�����v�����ǂ����̃t���O
	int isPushFlag;
	// �V���b�g�{�^�����O�t���[���ŉ����ꂽ���ǂ����̃t���O
	bool isPrevshotFlag;

	// �e�̍������t���O
	bool LeftDir;
	// �e�̏�����t���O
	bool TopDir;
};