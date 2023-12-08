#pragma once

// #include "SceneMain.h"	// includeはしないように
// クラスのプロトタイプ宣言
class SceneMain;
class SceneMapEdit;
class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void Init();
	void End();

	void Update();
	void Draw();

private:
	SceneMain* m_pMain;
	SceneMapEdit* m_pMapEdit;

};

