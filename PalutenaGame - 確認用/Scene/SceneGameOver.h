#pragma once
#include "SceneBase.h"
class SceneGameOver :
    public SceneBase
{
public:
    SceneGameOver();
    ~SceneGameOver();

    void Init();
    void Update();
    void Draw();

    void End();

    // �V�[�����I������������
    bool IsSceneEnd() const;

    void SetHandle(int handle) { Graph = handle; }

private:

    bool m_isSceneEnd;	// �V�[���I���t���O
    // true:�^�C�g�����I�����ăQ�[����


};