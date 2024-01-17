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
        kSelectGameState,   // �Q�[���X�^�[�g
        kSclectOperation,   // ������@
        kSclectBack,        // �߂�
        kSclectEnd,         // �Q�[�����I���
        kSclectNum,         // ���ڐ�
    };

    int m_select;    // �I�𒆂̃��j���[


private:
    int TitleGraph;     // �^�C�g�����S�O���t
    bool m_isSceneEnd;	// �V�[���I���t���O
    
    // �I�𒆃��j���[�l�p�\���ʒu
    Vec2 m_selectPos;
};