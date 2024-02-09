#include "FontManager.h"
#include "DxLib.h"

FontManager::FontManager()
{
    //�t�H���g/
    // �t�@�C���̃��[�h
   // �ǂݍ��ރt�H���g�t�@�C���̃p�X
    LPCSTR font_path = "data/Font/KaiseiHarunoUmi-Bold.ttf";

    if (AddFontResourceEx(font_path, FR_PRIVATE, NULL) > 0)
    {
    }
    else
    {
        // �t�H���g�Ǎ��G���[����
        MessageBox(NULL, "�t�H���g�Ǎ����s", "", MB_OK);
    }

    m_fontHandle = CreateFontToHandle("Kaisei HarunoUmi", 58, -1);
    m_fontHandle2 = CreateFontToHandle("Kaisei HarunoUmi", 32, -1);
    m_fontHandle3 = CreateFontToHandle("Kaisei HarunoUmi", 105, -1);
    m_fontStaging = CreateFontToHandle("���z�� �l�N�X�g UP B", 85, -1);

}

FontManager::~FontManager()
{
    DeleteFontToHandle(m_fontHandle);
    DeleteFontToHandle(m_fontHandle2);
    DeleteFontToHandle(m_fontHandle3);
    DeleteFontToHandle(m_fontStaging);
}
