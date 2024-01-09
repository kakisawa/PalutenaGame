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

	// �萔�̒�`
	enum SceneKind
	{
		kSceneKindTitle,
		kSceneKindMain,
		kSceneKindResult,
	};

private:
	// ���ݎ��s���̃V�[��
	SceneKind   m_runScene;

	// SceneManager�ŊǗ�����e�V�[��
	SceneTitle  m_title;
	SceneMain   m_main;
	SceneResult m_result;
};

