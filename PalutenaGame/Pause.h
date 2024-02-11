#pragma once
#include "Vec2.h"

class SoundManager;

namespace {
	// 音量の最大
	constexpr int MaxVolume = 255;

	// 初期音量
	constexpr int InitBgmVolume = MaxVolume * 0.7f;
	constexpr int InitSeVolume = MaxVolume * 0.7f;
}

class Pause
{
public:
	Pause(SoundManager* soundManager);
	~Pause();

	void Init();
	void Update();
	void Draw();

	// 音量を返す
	int SetBgmVolume() const;
	int SetSeVolume() const;

	bool GetPauseFlag() { return m_pause; }

private:
	int MiniWindowTime;
	int PauseCount;

	int BgmVolume;		// 音量
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

	SoundManager* m_pSoundManager;
};