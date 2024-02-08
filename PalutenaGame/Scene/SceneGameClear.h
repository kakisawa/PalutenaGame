#pragma once
#include "SceneBase.h"
#include "Vec2.h"

class SoundManager;
class FontManager;

class SceneGameClear :
    public SceneBase
{
public:

	SceneGameClear();
	~SceneGameClear();

	void Init();
	void Update();
	void Draw();
    void End();

    void StringDraw();  // �����n�̕`��
    void BackDraw();    // �w�i�̕`��
    void UIDraw();      // UI���̕`��

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

    int TitleGraph;     // �^�C�g���O���t
    int ScoreGraph;     // �X�R�A�O���t
    int m_select;       // �I�𒆂̃��j���[
    int Cursor;         // �J�[�\���O���t
    int SelectUI;       // UI
    int SelectUI2;      // UI

    float m_scrollX;    // �X�N���[���ړ���

    struct Size         // �w�i�̃T�C�Y
    {
        int width;
        int height;
    };

    int m_fadeLetter;   // �����̓_�ŗp�J�E���^
    int m_fadeAlpha;    // �t�F�[�h�C���A�A�E�g
    bool m_isSceneEnd;	// �V�[���I���t���O

    // �I�𒆃��j���[�l�p�\���ʒu
    Vec2 m_selectPos;

    // SE/BGM
    SoundManager* m_pSoundManager;
    // �t�H���g
    FontManager* m_pFontManager;
};

