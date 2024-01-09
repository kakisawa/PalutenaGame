#pragma once
class SceneResult
{
public:
	SceneResult();
	~SceneResult();

	void Init();
	void Update();
	void Draw();
	void End();

	// �V�[�����I������������
	bool IsSceneEnd() const { return m_isSceneEnd; }

private:
	// �摜�̃n���h��
	int m_gameoverHandle;

	bool m_isSceneEnd;	// �V�[���I���t���O
};

