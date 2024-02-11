#pragma once
#include "Vec2.h"

class SoundManager;

namespace {
	// ���ʂ̍ő�
	constexpr int MaxVolume = 255;

	// ��������
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

	// ���ʂ�Ԃ�
	int SetBgmVolume() const;
	int SetSeVolume() const;

	bool GetPauseFlag() { return m_pause; }

private:
	int MiniWindowTime;
	int PauseCount;

	int BgmVolume;		// ����
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

	SoundManager* m_pSoundManager;
};