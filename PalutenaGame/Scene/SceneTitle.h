#pragma once
#include "SceneBase.h"
#include "Vec2.h"

class SoundManager;
class FontManager;
class ColorManager;
class SceneTitle :
    public SceneBase
{
public:
    SceneTitle();
    ~SceneTitle();

    void Init();
    void Update();
    void Draw();
    void End();

    void StringDraw();      // �����̕`��
    void BackDraw();        // �w�i�̃X�N���[���`��
    void SetHandle(int handle) { m_graph = handle; }    // �摜�̓ǂݍ���

    bool IsSceneEnd() const;     // �Q�[���Z���N�g�V�[���֌�������
    // ���ǂ̃X�e�[�W�ɍs����
    bool ToStage() const;
    bool ToExplanation() const;

private:
    int m_titleGraph;       // �^�C�g�����S�摜
    int m_cursorGraph;      // �J�[�\���摜
    int m_pushAGraph;       // �uA�{�^���Ō���v�摜
    int m_selectUIGraph;    // UI�摜
    int m_selectUIGraph2;   // UI�摜
    int m_select;           // �I�𒆂̃��j���[
    int m_fadeLetter;       // �����̓_�ŗp�J�E���^
    int m_fadeAlpha;        // �t�F�[�h�C���A�A�E�g

    float m_scrollX;        // �X�N���[���ړ���

    bool m_isSceneEnd;	    // �V�[���I���t���O
    bool m_isToSelect;      // �X�e�[�W�Z���N�g��ʂɍs����
    bool m_isToExplanation; // �����V�[���ɍs���� 

    struct Size         // �w�i�̃T�C�Y
    {
        int m_width;
        int m_height;
    };

    enum Select
    {
        kSelectGameStart,   // �Q�[���X�^�[�g
        kSclectOperation,   // ������@
        kSclectEnd,         // �Q�[�����I���

        kSclectNum,         // ���ڐ�
        kSclectBack,        // �߂�
    };

    // �I�𒆃��j���[�l�p�\���ʒu
    Vec2 m_selectPos;
    // �w�i�̕\���ʒu
    Vec2 m_bgPos;
    // �t�H���g�̃|�C���^
    FontManager* m_pFontManager;
    // SE�EBGM
    SoundManager* m_pSoundManager;
    // �F
    ColorManager* m_pColorManager;
};