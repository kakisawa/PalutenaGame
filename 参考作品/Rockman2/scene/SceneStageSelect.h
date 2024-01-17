#pragma once
#include "Vec2.h"

/// <summary>
/// �X�e�[�W�I���N���X
/// </summary>
class SceneStageSelect
{
public:
	SceneStageSelect();
	~SceneStageSelect();

	void Init();
	void Update();
	void Draw();
	void End();

	// �V�[�����I�������邩
	bool IsSceneEnd() const { return m_isSceneEnd; }

private:
	// �I������
	enum Select
	{
		kStage1,	// �X�e�[�W1
		kStage2,	// �X�e�[�W2
		kStage3,	// �X�e�[�W3
		kBackTitle,	// �^�C�g���ɖ߂�
		kSelectNum	// ���ڐ�
	};

	// ���݂̑I�����
	int m_select;

private:
	// �V�[���I���̃t���O true:�V�[���Ɉړ�
	bool m_isSceneEnd;

	// �^�C�g�����S
	int m_logoHandle;
	// �I�𒆂̎l�p�̕\���ʒu
	Vec2 m_selectPos;
};

