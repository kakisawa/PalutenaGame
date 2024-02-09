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
	int m_select;       // �I�𒆂̃��j���[

	int m_bgmDefo;
	int m_seDefo;

	enum Select
	{
		kBgmVolume,   // BGM
		kSeVolume,    // SE
		kBack,		  // �߂�

		kSclectNum,   // ���ڐ�
	};

	// �I�𒆃��j���[�l�p�\���ʒu
	Vec2 m_selectPos;
};