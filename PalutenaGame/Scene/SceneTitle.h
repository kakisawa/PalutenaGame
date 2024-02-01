#pragma once
#include "SceneBase.h"
#include "Vec2.h"

class Font;
class SoundManager;

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

    // ���̃V�[���֍s�����̒l��Ԃ�
    // �Q�[���Z���N�g�V�[���֌�������
    bool IsSceneEnd() const;

    // ���ǂ̃X�e�[�W�ɍs����
    bool ToStage() const;
    bool ToExplanation() const;

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


    int x, y;           // �^�C�g�����S���W
    int TitleGraph;     // �^�C�g�����S�O���t
    int Cursor;         // �J�[�\���O���t
    float m_scrollX;    // �X�N���[���ړ���

    struct Size         // �w�i�̃T�C�Y
    {
        int width;
        int height;
    };

    int m_select;       // �I�𒆂̃��j���[
    int m_fadeLetter;   // �����̓_�ŗp�J�E���^
    int m_fadeAlpha;    // �t�F�[�h�C���A�A�E�g
    bool m_isSceneEnd;	// �V�[���I���t���O

    bool isToSelect;        // �X�e�[�W�Z���N�g��ʂɍs����
    bool isToExplanation;   // �����V�[���ɍs���� 

    // �I�𒆃��j���[�l�p�\���ʒu
    Vec2 m_selectPos;
    // �w�i�̕\���ʒu
    Vec2 m_bgPos;

    // �t�H���g�̃|�C���^
    Font* m_pFont;
    // SE/BGM
    SoundManager* m_pSoundManager;
};