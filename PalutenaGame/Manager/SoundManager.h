#pragma once
#include <Vec2.h>

namespace {
	// ���ʂ̍ő�
	constexpr int MaxVolume = 255;

	// ��������
	constexpr int InitBgmVolume = MaxVolume * 0.6f;
	constexpr int InitSeVolume = MaxVolume * 0.6f;
}

class Pause;
class FontManager;
class ColorManager;

class SoundManager
{
public:
	SoundManager();
	~SoundManager();

	void Init();
	void Update(){}
	void Draw();
	void End();

public:
	void SoundSelect();
	void SoundButton();
	void SoundDamage();
	void SoundJump();
	void SoudndAttack();

public:
	void BGMDefo();
	void BGMButtle();
	void BGMGameClear();
	void BGMGameOver();
	void BGMExplanation();

public:
	void ChangeSound();

public:
	int m_soundJump;
	int m_soundAttack;
	int m_soundDamage;
	int m_soundSelect;
	int m_soundButton;

	int m_bgmDefo;
	int m_bgmButtle;
	int m_bgmGameClear;
	int m_bgmGameOver;
	int m_bgmExplanation;

public:
	// BGM�̉��ʂ𒲐����郁�\�b�h
	void ChangeBGMVolume(int volume);
	// SE�̉��ʂ𒲐����郁�\�b�h
	void ChangeSEVolume(int volume);

	// �����������ʂɕϊ�����
	void SetBgmVolume();
	void SetSeVolume();

private:
	int SeVolume;
	int BgmVolume;

	enum Select
	{
		kBgmVolume,   // BGM
		kSeVolume,    // SE
		kBack,		  // �߂�

		kSclectNum,   // ���ڐ�
	};
	int m_select;       // �I�𒆂̃��j���[


	// �I�𒆃��j���[�l�p�\���ʒu
	Vec2 m_selectPos;

	Pause* m_pPause;
	// �t�H���g�̃|�C���^
	FontManager* m_pFontManager;
	// �F
	ColorManager* m_pColorManager;
};

