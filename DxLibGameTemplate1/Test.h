#pragma once
#include "Vec2.h"

class Test
{
public:
	Test();
	~Test();

	void Init();
	void Update();
	void Draw();

private:
    enum Select
    {
        kStage1,        // �X�e�[�W1
        kStage2,        // �X�e�[�W2
        kBackTitle,     // �^�C�g����ʂɖ߂�

        kSclectNum,     // ���ڐ�
    };

    int m_fadeLetter;   // �����̓_�ŗp�J�E���^
    int m_select;       // �I�𒆂̃��j���[

    // �I�𒆃��j���[�l�p�\���ʒu
    Vec2 m_selectPos;
};

