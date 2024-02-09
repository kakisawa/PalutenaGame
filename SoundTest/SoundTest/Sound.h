#pragma once
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
	int MiniWindowTime;
	int PauseCount;

	bool m_pause;

	int m_bgmDefo;
};