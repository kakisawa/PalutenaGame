#pragma once
#include "Vec2.h"
#include "EnemyBase.h"

// �E����o�ꂷ��G�̃N���X
class EnemyRight : public EnemyBase
{
public:
	EnemyRight();
	virtual ~EnemyRight();

	virtual void Update() override;

	// �G�L�����N�^�[���X�^�[�g������
	virtual void Start() override;

	/*
	void Init();

	
	void Draw();

	 �����o�[�ϐ��ɃA�N�Z�X����
	void SetHandle(int handle) { m_handle = handle; }

	bool IsExist() const { return m_isExist; }



private:	// �����o�ϐ��͕K��private
	int m_handle;	// �O���t�B�b�N�̃n���h��

	bool m_isExist;	// ���݂��邩�t���O(�g�p�����ǂ���)

	// �\���ʒu
	Vec2 m_pos;
	// �ړ���	1�t���[��������̈ړ��ʂ�����
	Vec2 m_vec;
*/
};

