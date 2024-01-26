#pragma once
#include "SceneBase.h"
class SceneExplanation :
    public SceneBase
{
public:
    SceneExplanation();
    ~SceneExplanation();

    void Init();
    void Update();
    void Draw();
    void End();


    // �V�[�����I������������
    bool IsSceneEnd() const;
    void SetHandle(int handle) { Graph = handle; }

private:
    int m_fadeAlpha;    // �t�F�[�h�C���A�A�E�g
    bool m_isSceneEnd;	// �V�[���I���t���O
};

