#pragma once
#include "Vec2.h"
#include "Rect.h"

class Player;

class EnemyBase {
public:

	EnemyBase();			
	virtual ~EnemyBase(){}

	virtual void Init(Player* pPlayer);
	virtual void Update();
	virtual void Draw(){}

	virtual void OnDamage();	// �G���_���[�W���󂯂����̏���
	void Death();				// ���񂾂Ƃ��̏���

	Vec2 GetPos() const { return m_pos; }			// �ʒu�̎擾
	Rect GetColRect() const { return m_colRect; }	// �����蔻��̋�`���擾����

	// �G�̍U����,HP,�X�R�A��n��
	int GetEnemyAtk() const { return m_atk; }
	int GetEnemyHP() const { return m_hp; }

	bool isExist() const { return m_isExist; }

	// �G�L�����N�^�[���X�^�[�g������
	virtual void Start(float x, float y) = 0;
	
protected:		// �h���N���X����A�N�Z�X�ł���悤��
	int EGraph;	// �G�摜
	int m_w, m_h;	// �G�摜�T�C�Y
	int m_hp;		// �GHP
	int m_atk;	// �G�U����	
	int Score;	// �G��|�����ۂɓ�����X�R�A
	int isTurn;	// ���E�ǂ���������Ă��邩

	float EnemyAnim;	// �G�l�~�[�A�j���[�V����
	float m_gravity;		// �d��
	int m_damageFrame;	// �_���[�W���󂯂Ă���̃t���[����
							// ���i��0�ŁA�����������Ƀt���[������ݒ肵��
							// �ȍ~���t���[�����炵�Ă���

	bool isScore;		// �X�R�A���Z�t���O

	bool m_isExist;		// ���݂��邩�t���O(�g�p�����ǂ���)
	bool isDeath;		// ���S�t���O


	// �\���ʒu
	Vec2 m_pos;
	// �����蔻��̋�`
	Rect m_colRect;
	// �ړ���	1�t���[��������̈ړ��ʂ�����
	Vec2 m_vec;

	Player* m_pPlayer;
};