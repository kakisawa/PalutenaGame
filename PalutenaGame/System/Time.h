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
	bool TimeUp() const { return isTimeUp; }

private:
	float Second;		// 残りのゲーム秒数(制限時間)*60
	float Count;		// カウント秒数*60

	bool isTimeUp;		// 制限時間が終了したか

	// フォント
	FontManager* m_pFontManager;
	// 色
	ColorManager* m_pColorManager;
};

