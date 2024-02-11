#pragma once
#include "Vec2.h"

class Pause
{
public:
	Pause();
	~Pause();

	void Init();
	void Update();
	void Draw();

	void PushPause();

private:

	int MiniWindowTime;
	int PauseCount;

	int BgmVolume;		// 仮数字
	int SeVolume;

	bool m_pause;
	int m_select;       // 選択中のメニュー

	enum Select
	{
		kBgmVolume,   // BGM
		kSeVolume,    // SE
		kBack,		  // 戻る

		kSclectNum,   // 項目数
	};

	// 選択中メニュー四角表示位置
	Vec2 m_selectPos;
};