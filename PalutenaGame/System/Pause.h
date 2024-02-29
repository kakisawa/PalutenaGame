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

	bool GetPauseFlag() { return m_ispause; }

private:
	float m_miniWindowTime;
	float m_pauseCount;

	bool m_ispause;

	// BGMESE
	SoundManager* m_pSoundManager;
	// F
	ColorManager* m_pColorManager;
};