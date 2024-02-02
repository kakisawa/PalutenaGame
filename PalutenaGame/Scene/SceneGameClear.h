#pragma once
#include "SceneBase.h"
#include "Vec2.h"

class SoundManager;

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

private:
    enum Select
    {
        kScelectBackTitle, // �z�[����ʂɖ߂�
        kScelectEnd,        // �Q�[�����I���

        kSclectNum,         // ���ڐ�
    };

    int m_select;    // �I�𒆂̃��j���[
    int Cursor;         // �J�[�\���O���t

    int m_fadeLetter;   // �����̓_�ŗp�J�E���^
    int m_fadeAlpha;    // �t�F�[�h�C���A�A�E�g
    bool m_isSceneEnd;	// �V�[���I���t���O

    // �I�𒆃��j���[�l�p�\���ʒu
    Vec2 m_selectPos;

    // SE/BGM
    SoundManager* m_pSoundManager;
};

