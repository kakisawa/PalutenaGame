#pragma once
#include "Rect.h"
#include "Vec2.h"

// �v���g�^�C�v�錾
struct Shot;

struct Player 
{
	// �v���C���[�̏����ʒu
	int X;
	int Y;

	// �v���C���[�̉摜
	int Graph;
	// �v���C���[�̉摜�T�C�Y
	int W;
	int H;

	// �����ړ���
	float FallPowor;

	// �O���t�B�b�N�̃n���h��
	int m_handle;
	// �\���ʒu
	Vec2 m_pos;
	// �����蔻��p�̋�`
	Rect m_colRect;

	// �v���C���[���]�t���O
	bool isTurn;
	// �v���C���[����������Ă��邩�̃t���O
	bool isLookUp;
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

	// �v���C���[�̌��݈ʒu���擾����
	Vec2 GetPos() const { return m_pos; }
	// �v���C���[�̓����蔻����擾����
	Rect GetColRect() const { return m_colRect; }
};

// �v���g�^�C�v�錾
void InitPlayer(Player& player);
void UpdatePlayer(Player& player, Shot shot[], int shotArraySize);
void DrawPlayer(Player& player);