#pragma once
#include <Vec2.h>

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

	void SoundSelect();
	void SoundButton();
	void SoundDamage();
	void SoundJump();
	void SoudndAttack();

	void BGMDefo();
	void BGMButtle();
	void BGMGameClear();
	void BGMGameOver();
	void BGMExplanation();

	void ChangeSound();

	// BGM�̉��ʂ𒲐����郁�\�b�h
	void ChangeBGMVolume(float volume);
	// SE�̉��ʂ𒲐����郁�\�b�h
	void ChangeSEVolume(float volume);

	// �����������ʂɕϊ�����
	void SetBgmVolume();
	void SetSeVolume();

	bool GetSceneEnd() { return m_isSceneEnd; }

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

private:
	int m_graph;
	int m_select;       // �I�𒆂̃��j���[

	float m_seVolume;
	float m_bgmVolume;

	bool m_isSceneEnd;

	enum Select
	{
		kBgmVolume,   // BGM
		kSeVolume,    // SE
		kBack,		  // �߂�

		kSclectNum,   // ���ڐ�
	};
	
	// �I�𒆃��j���[�l�p�\���ʒu
	Vec2 m_selectPos;

	Pause* m_pPause;
	// �t�H���g�̃|�C���^
	FontManager* m_pFontManager;
	// �F
	ColorManager* m_pColorManager;
};