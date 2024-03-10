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
        kStage1,        // ステージ1
        kStage2,        // ステージ2
        kBackTitle,     // タイトル画面に戻る

        kSclectNum,     // 項目数
    };

    int m_fadeLetter;   // 文字の点滅用カウンタ
    int m_select;       // 選択中のメニュー

    // 選択中メニュー四角表示位置
    Vec2 m_selectPos;
};

