#pragma once

class SceneBase
{
public:
	SceneBase();
	virtual ~SceneBase() {}

	virtual void Init() {}
	virtual void Update() {}
	virtual void Draw() {}

protected:
	int m_graph;	// �w�i�O���t
	bool m_isSceneEnd;	// �V�[���I���t���O
};