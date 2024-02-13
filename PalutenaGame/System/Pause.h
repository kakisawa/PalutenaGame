#pragma once
#include "Vec2.h"

class SoundManager;

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

	SoundManager* m_pSoundManager;
};