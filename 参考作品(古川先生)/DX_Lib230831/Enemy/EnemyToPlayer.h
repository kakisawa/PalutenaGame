#pragma once
#include "Vec2.h"
#include "EnemyBase.h"

class Player;
// �����ʒu���甭���������̃v���C���[�̈ʒu�Ɍ������Ĉړ�����
class EnemyToPlayer : public EnemyBase
{
public:
	EnemyToPlayer();
	virtual~EnemyToPlayer();

	virtual void Update() override;

	// �����o�[�ϐ��ɃA�N�Z�X����
	void SetPlayer(Player* pPlayer) { m_pPlayer = pPlayer; }

	// �G�L�����N�^�[���X�^�[�g������
	virtual void Start()override;

private:
	Player* m_pPlayer;

/*	void Draw();
	void SetHandle(int handle) { m_handle = handle; }
	bool IsExist() const { return m_isExist; }

private:	// �����o�ϐ��͕K��private
	int m_handle;	// �O���t�B�b�N�̃n���h��
	bool m_isExist;	// ���݂��邩�t���O(�g�p�����ǂ���)

	Player* m_pPlayer;


	// �\���ʒu
	Vec2 m_pos;
	// �ړ���	1�t���[��������̈ړ��ʂ�����
	Vec2 m_vec;
	*/
};

