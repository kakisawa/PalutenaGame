#pragma once
class SceneTitle;
class SceneStageSelect;
class SceneMain;
class SceneGameOver;

enum Stage
{
	kStage1,
	kStage2,

	kBack
};

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void Init();
	void Update();
	void Draw();
	void End();

public:
	// �X�e�[�W�̎��
	Stage PlayedStage() const { return m_runStage; }
	// �v���C��/�Q�[���I�[�o�[���X�e�[�W
	Stage m_runStage;


private:

	// �V�[���̎��
	enum SceneKind
	{
		kSceneKindTitle,	// �^�C�g���V�[��
		kSceneStageSelect,	// �X�e�[�W�Z���N�g
		kSceneKindMain,		// �Q�[���P�V�[��
		kSceneKindGameOver,	// �Q�[���I�[�o�[�V�[��
	};

	// ���ݎ��s���̃V�[��
	SceneKind   m_runScene;

	// SceneManager�ŊǗ�����e�V�[��
	SceneTitle*  m_pTitle;
	SceneStageSelect* m_pStageSelect;
	SceneMain*   m_pMain;
	SceneGameOver* m_pGameOver;
};

