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

	int BgmVolume;		// ������
	int SeVolume;

	bool m_pause;
	int m_select;       // �I�𒆂̃��j���[

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