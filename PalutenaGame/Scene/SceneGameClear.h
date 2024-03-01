#pragma once
#include "SceneBase.h"
#include "Vec2.h"

class SoundManager;
class FontManager;
class Player;
class ColorManager;

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
	void SetHandle(int handle) { m_graph = handle; }
   
private:
    int m_titleGraph;       // �^�C�g���O���t
    int m_scoreGraph;       // �X�R�A�O���t
    int m_select;           // �I�𒆂̃��j���[
    int m_cursorGraph;      // �J�[�\���O���t
    int m_selectUIGraph;    // UI
    int m_selectUIGraph2;   // UI
    int m_pushAGraph;       // A�{�^���������O���t
    int m_fadeLetter;       // �����̓_�ŗp�J�E���^
    int m_fadeAlpha;        // �t�F�[�h�C���A�A�E�g
    int m_resultScore;      // �l���X�R�A

    float m_scrollX;    // �X�N���[���ړ���
     
    bool m_isSceneEnd;	// �V�[���I���t���O

    enum Select
    {
        kScelectBackTitle, // �z�[����ʂɖ߂�
        kScelectEnd,        // �Q�[�����I���

        kSclectNum,         // ���ڐ�
    };
    struct Size         // �w�i�̃T�C�Y
    {
        int m_width;
        int m_height;
    };

    // �I�𒆃��j���[�l�p�\���ʒu
    Vec2 m_selectPos;
    // SE/BGM
    SoundManager* m_pSoundManager;
    // �t�H���g
    FontManager* m_pFontManager;
    // �F
    ColorManager* m_pColorManager;
};

