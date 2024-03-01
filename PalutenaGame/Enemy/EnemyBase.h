#pragma once
#include "Vec2.h"
#include "Rect.h"

class Player;
class EnemyBase
{
public:

	EnemyBase();			
	virtual ~EnemyBase(){}

	virtual void Init(Player* pPlayer);
	virtual void Update();
	virtual void Draw(){}

	// �G���_���[�W���󂯂����̏���
	virtual void OnDamage();	
	// ���񂾂Ƃ��̏���
	void Death();
	// �ʒu�̎擾
	Vec2 GetPos() const { return m_pos; }
	// �����蔻��̋�`���擾����
	Rect GetColRect() const { return m_colRect; }	
	// �G�̍U����,HP,�X�R�A��n��
	int GetEnemyAtk() const { return m_atk; }
	int GetEnemyHP() const { return m_hp; }
	// �G�����݂��邩�ǂ����̃t���O��n��
	bool isExist() const { return m_isExist; }

	// �G�L�����N�^�[���X�^�[�g������
	virtual void Start(float x, float y) = 0;
	
protected:	// �h���N���X����A�N�Z�X�ł���悤��
	int m_graph;		// �G�摜
	int m_expGraph;		// �G���S�����j�摜
	int m_w, m_h;		// �G�摜�T�C�Y
	int m_hp;			// �GHP
	int m_atk;			// �G�U����	
	int m_score;		// �G�����X�R�A
	int m_damageFrame;	// �_���[�W���󂯂Ă���̃t���[����

	float m_enemyAnim;		// �G�A�j���[�V����
	float m_enemyDeathAnim;	// �G���S�A�j���[�V����
	float m_gravity;		// �d��
	
	bool m_isExist;		// ���݂��邩�t���O(�g�p�����ǂ���)
	bool m_isTurn;		// ���E�ǂ���������Ă��邩
	bool m_isDeathAnim;	// �G���S�A�j���[�V�����t���O
	bool m_isDeath;		// ���S�t���O
	bool m_isScore;		// �X�R�A���Z�t���O
	
	// �\���ʒu
	Vec2 m_pos;
	// �����蔻��̋�`
	Rect m_colRect;
	// �ړ���	1�t���[��������̈ړ��ʂ�����
	Vec2 m_vec;

	Player* m_pPlayer;
};