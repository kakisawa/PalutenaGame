#include "SceneBase.h"
#include "Vec2.h"

class SoundManager;
class FontManager;
class ColorManager;

class SceneStageSelect :
    public SceneBase
{
public:
    SceneStageSelect();
    ~SceneStageSelect();

    void Init();
    void Update();
    void Draw();
    void End();

    void StringDraw();          // �����̕`��
    void BackDraw();            // �w�i�̃X�N���[���`��
    bool IsSceneEnd() const;    // �V�[�����I������������

    // ���ǂ̃X�e�[�W�ɍs����
    bool ToStage1() const { return m_isStage1; }
    bool ToStage2() const { return m_isStage2; }
    bool ToBackTitke() const { return m_isBackTitle; }

private:
    int m_explanationGraph;   // ��������摜
    int m_cursorGraph;        // �J�[�\���摜
    int m_pushAGraph;         // �uA�{�^���Ō���v
    int m_selectUIGraph;      // UI
    int m_selectUIGraph2;     // UI
    int m_select;             // �I�𒆂̃��j���[
    int m_fadeAlpha;          // �t�F�[�h�C���A�A�E�g
    int m_fadeLetter;         // �����̓_�ŗp�J�E���^
    
    float m_scrollX;           // �X�N���[���ړ��ʃO���t
   
    // �X�e�[�W1�֍s�����A�X�e�[�W�Q�֍s�����A�^�C�g����ʂɖ߂邩
    bool m_isStage1;
    bool m_isStage2;
    bool m_isBackTitle;
   
    enum Select         // �Z���N�g�I����
    {
        kStage1,        // �X�e�[�W1
        kStage2,        // �X�e�[�W2
        kBackTitle,     // �^�C�g����ʂɖ߂�

        kSclectNum,     // ���ڐ�
    };
    struct Size         // �w�i�̃T�C�Y
    {
        int m_width;
        int m_height;
    };

    // �I�𒆃��j���[�l�p�\���ʒu
    Vec2 m_selectPos;
    // �w�i�̕\���ʒu
    Vec2 m_bgPos;
    // SE/BGM
    SoundManager* m_pSoundManager;
    // �t�H���g
    FontManager* m_pFontManager;
    // �F
    ColorManager* m_pColorManager;
};

