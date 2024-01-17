#pragma once
#include "Vec2.h"
#include "Rect.h"
#include <vector>

class RecoveryBase;
class ShotBase;
class SceneMain;

/// <summary>
/// �G�̊��N���X
/// </summary>
class EnemyBase
{
public:
	EnemyBase();
	virtual ~EnemyBase();

	virtual void Init();
	virtual void Update();
	virtual void Draw();

	// �G���_���[�W���󂯂����̏���
	virtual void OnDamage();
	// �G�L�����N�^�[���X�^�[�g������
	virtual void Start() = 0;

	// �����o�[�ϐ��ɃA�N�Z�X����
	void SetHandle(int handle) { m_handle = handle; }
	void SetMain(SceneMain* pMain) { m_pMain = pMain; }

	// ���݂��Ă��邩�̔���		true:���݂��Ă���
	bool IsExist() const { return m_isExist; }
	// HP�̎擾
	int GetHp() const { return m_hp; }
	// ���ݍ��W�̎擾
	Vec2 GetPos() const { return m_pos; }
	// �����蔻����擾����
	Rect GetColRect() const { return m_colRect; }

protected:
	// �����蔻���ݒ肷��
	virtual void UpdateCollision();

protected:
	// ���C���V�[���̃|�C���^
	SceneMain* m_pMain;
	// �񕜃A�C�e���̃|�C���^
	RecoveryBase* m_pRecovery;
	// �V���b�g�̃|�C���^
	std::vector<ShotBase*> m_pShot;

	// �O���t�B�b�N�̃n���h��
	int m_handle;
	// ���݂��邩�t���O true:���݂���
	bool m_isExist;	
	// �G��HP
	int m_hp;

	// �\���ʒu
	Vec2 m_pos;
	// �����蔻��̋�`
	Rect m_colRect;
	// �ړ���
	Vec2 m_vec;
};
