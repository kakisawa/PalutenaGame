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
	int m_graph;	// 背景グラフ
	bool m_isSceneEnd;	// シーン終了フラグ
};