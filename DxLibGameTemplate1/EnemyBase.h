#pragma once
#include "Vec2.h"
#include "Rect.h"

class EnemyBase{
public:

	EnemyBase() {}			// �R���X�g���N�^
	virtual ~EnemyBase() {}	// �f�X�g���N�^

	// �U�����󂯂鏈��(�������z�֐��ɂ��A�h���N���X�Ŏ���)
	virtual void Damage(int damage) = 0;
	// ���񂾂Ƃ��̏���
	void Death()
	{
		isDeath = true;		// ���񂾃t���O���I���ɂ���
	}
	// ����ł��邩�ǂ���
	bool GetisDeath()
	{
		return isDeath;
	}
protected:		// �h���N���X����A�N�Z�X�ł���悤��

	int EGraph;	// �G�摜
	int W,H;	// �G�摜�T�C�Y
	int HP;		// �GHP
	int Atk;	// �G�U����
	int Item;	// �h���b�v�A�C�e��
	int isTurn;	// ���E�ǂ���������Ă��邩

	// �\���ʒu
	Vec2 enemy;
	// �G�l�~�[�A�j���[�V����
	float EnemyAnim;
	// �d��
	float Gravity;

	// �����蔻��p�̋�`
	Rect m_colRect;

	bool isDeath = false; //���񂾂��ǂ����Afalse�ŏ��������Ă���
//	Player* player;	// �v���C���[
};