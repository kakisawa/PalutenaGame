#pragma once

class SceneBase
{
public:
	SceneBase();
	virtual ~SceneBase() {}

	virtual void Init() {}
	virtual void Update() {}
	virtual void Draw() {}

	// �V�[�����I������������
	virtual  bool IsSceneEnd() const { return false; }

protected:
	int m_graph;	// �w�i�O���t
	bool m_isSceneEnd;	// �V�[���I���t���O
};