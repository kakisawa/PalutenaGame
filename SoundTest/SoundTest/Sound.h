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

private:
	int Volume;

	int m_bgmDefo;
};