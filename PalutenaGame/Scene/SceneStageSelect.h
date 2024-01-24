#include "SceneBase.h"
#include "Vec2.h"

class SceneMain;

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

    void SetHandle(int handle) { Graph = handle; }

    // �V�[�����I������������
    bool IsSceneEnd() const;

    // ���ǂ̃X�e�[�W�ɍs����
    bool ToStage1() const { return isStage1; }
    bool ToStage2() const { return isStage2; }
    bool ToBackTitke() const { return isBackTitle; }

private:
    enum Select
    {
        kStage1,        // �X�e�[�W1
        kStage2,        // �X�e�[�W2
        kBackTitle,     // �^�C�g����ʂɖ߂�

        kSclectNum,         // ���ڐ�
    };

    int m_select;    // �I�𒆂̃��j���[

private:

    // �X�e�[�W1�֍s�����A�X�e�[�W�Q�֍s�����A�^�C�g����ʂɖ߂邩
    bool isStage1;
    bool isStage2;
    bool isBackTitle;

    // �I�𒆃��j���[�l�p�\���ʒu
    Vec2 m_selectPos;
};

