#pragma once

class SceneBase
{
public:
	SceneBase();
	virtual ~SceneBase() {}

	virtual void Init() {}
	virtual void Update() {}
	virtual void Draw() {}


	// シーンを終了させたいか
	virtual  bool IsSceneEnd() const;

protected:
	int Graph;
	int Bgm;
	int Se;

	int x;
	int y;

	bool m_isSceneEnd;	// シーン終了フラグ
	// true:タイトルを終了してゲームへ
};