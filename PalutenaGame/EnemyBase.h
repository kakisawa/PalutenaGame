#pragma once
#include "Vec2.h"
#include "Rect.h"

class EnemyBase {
public:

	EnemyBase() {}			// �R���X�g���N�^
	virtual ~EnemyBase() {}	// �f�X�g���N�^

	virtual void Init();
	virtual void Update();
	virtual void Draw();

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
	int W, H;	// �G�摜�T�C�Y
	int HP;		// �GHP
	int Atk;	// �G�U����	
	int isTurn;	// ���E�ǂ���������Ă��邩

	enum Item	// �A�C�e���̎��
	{
		kHeart,		// �n�[�g
		kHalfHeart,	// �n�[�t�n�[�g
		kBigHeart,	// �r�b�O�n�[�g
		kHammer,	// �g���J�`
	};

	Item Drop;		// �h���b�v�A�C�e��

	// �G�l�~�[�A�j���[�V����
	float EnemyAnim;
	// �d��
	float Gravity;


	bool isDeath = false; //���񂾂��ǂ����Afalse�ŏ��������Ă���
	//	Player* player;	// �v���C���[
};