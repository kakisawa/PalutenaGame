#pragma once
#include "Vec2.h"

/// <summary>
///  �^�C�g���V�[���̃N���X
/// </summary>
class SceneTitle
{
public:
	SceneTitle();
	~SceneTitle();

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
		kStart,	 // �X�^�[�g
		kOption, // �I�v�V����
		kExit,	 // �Q�[���I��
		kSelectNum // ���ڐ�
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

