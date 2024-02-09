#pragma once
#include "Vec2.h"
class Sound
{
public:
	Sound();
	~Sound();

	void Init();
	void Update();
	void Draw();

	void BGMDefo();

	void Pause();

private:
	int Volume;
	int SeVolume;
	int MiniWindowTime;
	int PauseCount;

	bool m_pause;
	int m_select;       // 選択中のメニュー

	int m_bgmDefo;
	int m_seDefo;

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