#include "Font.h"
#include "DxLib.h"

void Font::init()
{
	// ********** �t�H���g�̃��[�h **********
	LPCSTR font_path = "data/Font/mogihaPen.ttf"; // �ǂݍ��ރt�H���g�t�@�C���̃p�X
	if (AddFontResourceEx(font_path, FR_PRIVATE, NULL) > 0) {
	}
	else {
		// �t�H���g�Ǎ��G���[����
		MessageBox(NULL, "�t�H���g�Ǎ����s", "", MB_OK);
	}
	// �^�C�g����ʕ\���p�t�H���g

	m_TitleFont = CreateFontToHandle("���M�n�E�y����Font", 64, -1);
}

void Font::Update()
{
}

void Font::Draw()
{
}
