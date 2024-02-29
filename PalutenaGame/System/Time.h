#pragma once

class FontManager;
class ColorManager;

class Time
{
public:
	Time();
	~Time();

	void Init();
	void Update();
	void Draw();

	// 制限時間のフラグを返す
	bool TimeUp() const { return m_isTimeUp; }

private:
	float m_second;		// 残りのゲーム秒数(制限時間)*60
	float m_count;		// カウント秒数*60

	bool m_isTimeUp;		// 制限時間が終了したか

	// フォント
	FontManager* m_pFontManager;
	// 色
	ColorManager* m_pColorManager;
};

