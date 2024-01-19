#pragma once
#include "Vec2.h"
#include "Rect.h"

class Player;

class EnemyBase {
public:

	EnemyBase();			
	virtual ~EnemyBase(){}

	virtual void Init(){}
	virtual void Update();
	virtual void Draw();

	virtual void OnDamage();	// �G���_���[�W���󂯂����̏���
	void Death();				// ���񂾂Ƃ��̏���

	Vec2 GetPos() const { return m_pos; }			// �ʒu�̎擾
	Rect GetColRect() const { return m_colRect; }	// �����蔻��̋�`���擾����

	// �G�̍U���͂�n��
	int GetEnemyAtk() const { return Atk; }

	// �v���C���[�̍U���͂��l�����邽��
	void SetPlayer(Player* pPlayer) { m_pPlayer = pPlayer; }

protected:		// �h���N���X����A�N�Z�X�ł���悤��

	int EGraph;	// �G�摜
	int W, H;	// �G�摜�T�C�Y
	int HP;		// �GHP
	int Atk;	// �G�U����	
	int isTurn;	// ���E�ǂ���������Ă��邩

	float EnemyAnim;	// �G�l�~�[�A�j���[�V����
	float Gravity;		// �d��
	int m_damageFrame;	// �_���[�W���󂯂Ă���̃t���[����
							// ���i��0�ŁA�����������Ƀt���[������ݒ肵��
							// �ȍ~���t���[�����炵�Ă���

	bool m_isExist;		// ���݂��邩�t���O(�g�p�����ǂ���)

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

	Player* m_pPlayer;
};