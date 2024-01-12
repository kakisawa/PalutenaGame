#pragma once


class SceneTitle;
class SceneMain;
class SceneGameOver;

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void Init();
	void Update();
	void Draw();
	void End();

private:

	enum SceneKind
	{
		kSceneKindTitle,
		kSceneKindMain,
		kSceneKindGameOver,
	};

private:
	// ���ݎ��s���̃V�[��
	SceneKind   m_runScene;

	// SceneManager�ŊǗ�����e�V�[��
	SceneTitle*  m_pTitle;
	SceneMain*   m_pMain;
	SceneGameOver* m_pGameOver;


//	SceneResult m_result;

};

