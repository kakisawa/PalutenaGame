#pragma once


class SceneTitle;
class SceneMain;

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
	};

private:
	// ���ݎ��s���̃V�[��
	SceneKind   m_runScene;

	// SceneManager�ŊǗ�����e�V�[��
	SceneTitle*  m_pTitle;
	SceneMain*   m_pMain;


//	SceneResult m_result;

};

