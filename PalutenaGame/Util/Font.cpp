#include "Font.h"
#include "DxLib.h"

void Font::init()
{
	// ********** フォントのロード **********
	LPCSTR font_path = "data/Font/mogihaPen.ttf"; // 読み込むフォントファイルのパス
	if (AddFontResourceEx(font_path, FR_PRIVATE, NULL) > 0) {
	}
	else {
		// フォント読込エラー処理
		MessageBox(NULL, "フォント読込失敗", "", MB_OK);
	}
	// タイトル画面表示用フォント

	m_TitleFont = CreateFontToHandle("モギハ・ペン字Font", 64, -1);
}

void Font::Update()
{
}

void Font::Draw()
{
}
