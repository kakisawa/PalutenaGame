#pragma once
#include "SceneBase.h"
class SceneTitle :
    public SceneBase
{
public:
    SceneTitle();
    ~SceneTitle() {}

    void Init();
    void Update();
    void Draw();

    void End();

    // �V�[�����I������������
    bool IsSceneEnd() const;

    void SetHandle(int handle) { Graph = handle; }

private:
    int TitleGraph;     // �^�C�g�����S�O���t

    bool m_isSceneEnd;	// �V�[���I���t���O
    // true:�^�C�g�����I�����ăQ�[����
};