#pragma once
#include "SceneMain.h"
#include "SceneTitle.h"
#include "SceneResult.h"

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

	// 定数の定義
	enum SceneKind
	{
		kSceneKindTitle,
		kSceneKindMain,
		kSceneKindResult,
	};

private:
	// 現在実行中のシーン
	SceneKind   m_runScene;

	// SceneManagerで管理する各シーン
	SceneTitle  m_title;
	SceneMain   m_main;
	SceneResult m_result;
};

