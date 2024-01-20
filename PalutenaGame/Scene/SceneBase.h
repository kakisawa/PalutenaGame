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
	virtual  bool IsSceneEnd() const;

protected:
	int Graph;
	int Bgm;
	int Se;

	int x;
	int y;

	bool m_isSceneEnd;	// �V�[���I���t���O
	// true:�^�C�g�����I�����ăQ�[����
};