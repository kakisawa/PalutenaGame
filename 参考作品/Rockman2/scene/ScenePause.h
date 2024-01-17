#pragma once
#include "Vec2.h"

class Player;

/// <summary>
/// �|�[�Y�V�[���N���X
/// </summary>
class ScenePause
{
public:
	ScenePause(Player* pPlayer);
	~ScenePause();
	void Init();
	void Update();
	void Draw();
	// �|�[�Y��ʂ��\������Ă��邩�擾����
	bool IsExist() const { return m_isExist; }

private:
	// �I������
	enum Select
	{
		kBuster,// �o�X�^�[
		kMetal, // ���^��
		kFire,	// �t�@�C�A�[
		kLine,	// 2��
		kFullRecovery,	// E��
		kSelectNum // ���ڐ�
	};

	// ���݂̑I�����
	int m_select;

private:
	// �v���C���[�̃|�C���^
	Player* m_pPlayer;

	// �|�[�Y��ʂ̕\���ʒu
	Vec2 m_pos;
	// �I�𒆂̎l�p�̕\���ʒu
	Vec2 m_selectPos;
	// �|�[�Y��ʂ��\������Ă��邩 true:�\������Ă���
	bool m_isExist;
};

