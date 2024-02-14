#pragma once
#include "Vec2.h"

class SoundManager;
class ColorManager;

class Pause
{
public:
	Pause(SoundManager* soundManager);
	~Pause();

	void Init();
	void Update();
	void Draw();

	bool GetPauseFlag() { return m_pause; }

private:
	int MiniWindowTime;
	int PauseCount;

	bool m_pause;

	// BGMESE
	SoundManager* m_pSoundManager;
	// F
	ColorManager* m_pColorManager;
};