#pragma once

// #include "SceneMain.h"	// include�͂��Ȃ��悤��
// �N���X�̃v���g�^�C�v�錾
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

