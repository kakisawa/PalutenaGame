#pragma once

class Time
{
public:
	Time();
	~Time();

	void Init();
	void Update();
	void Draw();

	bool TimeUp() const { return isTimeUp; }

private:
	float Second;		// 残りのゲーム秒数(制限時間)*60
	float Count;		// カウント秒数*60

	bool isTimeUp;		// 制限時間が終了したか
};

