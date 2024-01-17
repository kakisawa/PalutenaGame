#pragma once
#include "Vec2.h"

/// <summary>
/// �N���A�V�[���N���X
/// </summary>
class SceneClear
{
public:
	SceneClear();
	~SceneClear();
	void Init();
	void End();
	void Update();
	void Draw();

	// �V�[�����I�������邩
	bool IsSceneStageSelect() const { return m_isSceneSelectStage; }

private:
	// �I������
	enum Select
	{
		kSelectStage, // �X�e�[�W�I��
		kTitle,		  // �^�C�g��
		kSelectNum	  // ���ڐ�
	};

	// ���݂̑I�����
	int m_select;

private:
	// �V�[���I���̃t���O true:�V�[���Ɉړ�
	bool m_isSceneSelectStage;

	// �I�𒆂̎l�p�̕\���ʒu
	Vec2 m_selectPos;
};

