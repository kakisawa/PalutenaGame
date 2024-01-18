#include "SceneBase.h"
#include "Vec2.h"

class SceneStageSelect :
    public SceneBase
{
public:
    SceneStageSelect();
    ~SceneStageSelect() {}

    void Init();
    void Update();
    void Draw();
    void End();

    // �V�[�����I������������
    bool IsSceneEnd() const;
    bool IsSceneEnd2() const;
    bool IsSceneEnd3() const;

    void SetHandle(int handle) { Graph = handle; }
private:
    enum Select
    {
        kStage1,        // �X�e�[�W1
        kStage2,        // �X�e�[�W2
        kSclectBack,    // �߂�

        kSclectNum,         // ���ڐ�
    };

    int m_select;    // �I�𒆂̃��j���[

private:
    bool m_isSceneEnd;	// �V�[���I���t���O
    bool m_isSceneEnd2; // �V�[���I���t���O2
    bool m_isSceneEnd3; // �V�[���I���t���O3

    // �I�𒆃��j���[�l�p�\���ʒu
    Vec2 m_selectPos;
};

