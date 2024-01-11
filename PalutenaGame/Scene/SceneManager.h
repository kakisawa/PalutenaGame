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
	// 現在実行中のシーン
	SceneKind   m_runScene;

	// SceneManagerで管理する各シーン
	SceneTitle*  m_pTitle;
	SceneMain*   m_pMain;


//	SceneResult m_result;

};

