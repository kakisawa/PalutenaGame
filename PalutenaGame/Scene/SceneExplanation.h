#pragma once
#include "SceneBase.h"

class SoundManager;

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

    void BackDraw();

    // �V�[�����I������������
    bool IsSceneEnd() const;
    void SetHandle(int handle) { Graph = handle; }

private:
    int BgGraph;
    float m_scrollX;    // �X�N���[���ړ���

    int m_fadeAlpha;    // �t�F�[�h�C���A�A�E�g
    bool m_isSceneEnd;	// �V�[���I���t���O

    struct Size         // �w�i�̃T�C�Y
    {
        int width;
        int height;
    };

    SoundManager* m_pSoundManager;
};

