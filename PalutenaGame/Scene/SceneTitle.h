#pragma once
#include "SceneBase.h"
#include "Vec2.h"

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
    enum Select
    {
        kSclectOperation,   // ������@
        kSelectGameStart,   // �Q�[���X�^�[�g
        kSclectEnd,         // �Q�[�����I���

        kSclectNum,         // ���ڐ�

        kSclectBack,        // �߂�
    };

    int m_select;    // �I�𒆂̃��j���[

private:
    int x, y;           // �^�C�g�����S���W

    int TitleGraph;     // �^�C�g�����S�O���t
    int m_fadeAlpha;    // �t�F�[�h�C���A�A�E�g
    bool m_isSceneEnd;	// �V�[���I���t���O

    // �I�𒆃��j���[�l�p�\���ʒu
    Vec2 m_selectPos;
};