#pragma once
class SceneTitle
{
public:
	SceneTitle();
	~SceneTitle();

	void Init();
	void Update();
	void Draw();

	void End();

	// �V�[�����I������������
	bool IsSceneEnd() const;

private:

	bool m_isSceneEnd;	// �V�[���I���t���O
					// true:�^�C�g�����I�����ăQ�[����

	// BGM�̃n���h��
	int m_bgmHandle;

	// ���ʉ��̃n���h��
	int m_decideSe;

		// �t�F�[�h�C���A�A�E�g
	int m_fadeAlpha;
};

