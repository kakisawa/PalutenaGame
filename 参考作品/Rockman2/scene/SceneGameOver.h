#pragma once

/// <summary>
/// �Q�[���I�[�o�[�̃N���X
/// </summary>
class SceneGameOver
{
public:
	SceneGameOver();
	~SceneGameOver();

	void Init();
	void Update();
	void Draw();
	void End();

	// �V�[�����I�������邩
	bool IsSceneSelect() const { return m_isSceneSelect; }

private:
	// �V�[���I���̃t���O true:�V�[���Ɉړ�
	bool m_isSceneSelect;
};

