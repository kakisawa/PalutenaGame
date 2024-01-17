#pragma once
#include "Vec2.h"
#include "Rect.h"

class Player;
class SceneMain;

/// <summary>
/// �񕜃A�C�e�����N���X
/// </summary>
class RecoveryBase
{
public:
	RecoveryBase();
	virtual ~RecoveryBase();

	virtual void Init();
	virtual void Update();
	virtual void Draw();

	// �A�C�e���̏����ʒu
	virtual void Start(Vec2 pos) = 0;

	// �����o�ϐ��ɃA�N�Z�X
	void SetMain(SceneMain* pMain) { m_pMain = pMain; }

	// �A�C�e�������݂��Ă��邩
	bool IsExist() const { return m_isExist; }
	// ���ݍ��W�̎擾
	Vec2 GetPos() const { return m_pos; }
	// �񕜃A�C�e���̓����蔻����擾����
	Rect GetColRect() const { return m_colRect; }

protected:
	// ���C���V�[���̃|�C���^
	SceneMain* m_pMain;
	// �O���t�B�b�N�̃n���h��
	int m_handle;
	// �\�����Ԃ̃t���[��
	int m_frame;
	// ��ʓ��ɑ��݂��Ă��邩
	bool m_isExist;

	// �\���ʒu
	Vec2 m_pos;
	// �����蔻��p�̋�`
	Rect m_colRect;
	// �ړ���
	Vec2 m_vec;
};

