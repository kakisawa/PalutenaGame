#pragma once
#include "Vec2.h"
#include "Rect.h"

class EnemyBase {
public:

	EnemyBase();			// �R���X�g���N�^
	virtual ~EnemyBase(){}	// �f�X�g���N�^

	virtual void Init(){}
	virtual void Update();
	virtual void Draw();

	// �����o�[�ϐ��ɃA�N�Z�X����
	void SetHandle(int handle) { EGraph = handle; }

	// �U�����󂯂鏈��(�������z�֐��ɂ��A�h���N���X�Ŏ���)
	virtual void Damage(int damage) = 0;

	// ���񂾂Ƃ��̏���
	void Death()
	{
		isDeath = true;		// �����S�t���O���I���ɂ���
	}
	// ����ł��邩�ǂ���
	bool GetisDeath()
	{
		return isDeath;		// ���S�t���O��Ԃ�
	}

	// �ʒu�̎擾
	Vec2 GetPos() const { return m_pos; }

	// �����蔻��̋�`���擾����
	Rect GetColRect() const { return m_colRect; }


protected:		// �h���N���X����A�N�Z�X�ł���悤��

	int EGraph;	// �G�摜
	int W, H;	// �G�摜�T�C�Y
	int HP;		// �GHP
	int Atk;	// �G�U����	
	int isTurn;	// ���E�ǂ���������Ă��邩

	bool m_isExist;	// ���݂��邩�t���O(�g�p�����ǂ���)

	// �G�l�~�[�A�j���[�V����
	float EnemyAnim;
	// �d��
	float Gravity;

	// m_pos�������,m_handle�̃O���t�B�b�N�T�C�Y�𕝍����ɂ���
	// �����蔻���ݒ肷��
	virtual void UpdateCollision();

	enum Item	// �A�C�e���̎��
	{
		kHeart,		// �n�[�g
		kHalfHeart,	// �n�[�t�n�[�g
		kBigHeart,	// �r�b�O�n�[�g
		kHammer,	// �g���J�`
	};
	Item Drop;		// �h���b�v�A�C�e��

	bool isDeath; // ���S�t���O

	// �\���ʒu
	Vec2 m_pos;
	// �����蔻��̋�`
	Rect m_colRect;
	// �ړ���	1�t���[��������̈ړ��ʂ�����
	Vec2 m_vec;
};