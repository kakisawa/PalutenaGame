#pragma once
class SceneTitle;
class SceneOption;
class SceneStageSelect;
class SceneMain;
class SceneSecond;
class SceneGameOver;
class SceneGameClear;

class SoundManager;
class Player;

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void Init();
	void Update();
	void Draw();
	void End();

	static int s_ResultScore;

private:
	// �V�[���̎��
	enum SceneKind
	{
		kSceneKindTitle,		// �^�C�g���V�[��
		kSceneKindOption,		// �ݒ�V�[��
		kSceneKindStageSelect,	// �X�e�[�W�Z���N�g
		kSceneKindMain,			// �Q�[��1�V�[��
		kSceneKindSecond,		// �Q�[��2�V�[��
		kSceneKindGameOver,		// �Q�[���I�[�o�[�V�[��
		kSceneKindGameClear,	// �Q�[���N���A�V�[��
	};

	// ���ݎ��s���̃V�[��
	SceneKind   m_runScene;

	// SceneManager�ŊǗ�����e�V�[��
	SceneTitle*  m_pTitle;
	SceneStageSelect* m_pStageSelect;
	SceneMain*   m_pMain;
	SceneSecond* m_pSecond;
	SceneGameOver* m_pGameOver;
	SceneGameClear* m_pGameClear;
	SceneOption* m_pOption;

	SoundManager* m_pSoundManager;
	Player* m_pPlayer;
};