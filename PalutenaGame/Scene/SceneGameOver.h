#pragma once
#include "SceneBase.h"
#include "Vec2.h"

class SceneMain;
class SceneSecond;
class SoundManager;

class SceneGameOver :
    public SceneBase
{
public:
    SceneGameOver();
    ~SceneGameOver();

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
        kScelectBackTitle, // �z�[����ʂɖ߂�
        kScelectEnd,        // �Q�[�����I���

        kSclectNum,         // ���ڐ�
    };

    int m_select;    // �I�𒆂̃��j���[
    int Cursor;      // �J�[�\���O���t

    int m_fadeAlpha;    // �t�F�[�h�C���A�A�E�g 
    int m_fadeLetter;   // �����̓_�ŗp�J�E���^
    bool m_isSceneEnd;	// �V�[���I���t���O

    // �I�𒆃��j���[�l�p�\���ʒu
    Vec2 m_selectPos;

    // �X�e�[�W1���
    SceneMain* m_pSceneMain;
    SceneSecond* m_pSceneSecond;
    // SE/BGM
    SoundManager* m_pSoundManager;
};