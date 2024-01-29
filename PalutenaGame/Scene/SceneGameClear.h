#pragma once
#include "SceneBase.h"
#include "Vec2.h"

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


	// �V�[�����I������������
	bool IsSceneEnd() const;
	void SetHandle(int handle) { Graph = handle; }

    // ���O�ɗV��ł����X�e�[�W��Ԃ�
    bool AgainStage1() const { return isStage1; }
    bool AgainStage2() const { return isStage2; }

    // ���O�ɂǂ̃X�e�[�W��V��ł������̃t���O���󂯎��
    bool JustStage1(int justStage1) { isStage1 = justStage1; }
    bool JustStage2(int justStage2) { isStage2 = justStage2; }

private:
    enum Select
    {
        kScelectRestart,    // ������x�ŏ�����
        kScelectReturnHome, // �z�[����ʂɖ߂�
        kScelectEnd,        // �Q�[�����I���

        kSclectNum,         // ���ڐ�
    };

    int m_select;    // �I�𒆂̃��j���[

    int m_fadeLetter;   // �����̓_�ŗp�J�E���^
    int m_fadeAlpha;    // �t�F�[�h�C���A�A�E�g
    bool m_isSceneEnd;	// �V�[���I���t���O


    bool isStage1;  // ���O�ɗV��ł����X�e�[�W1
    bool isStage2;  // ���O�ɗV��ł����X�e�[�W2


    // �I�𒆃��j���[�l�p�\���ʒu
    Vec2 m_selectPos;
};

