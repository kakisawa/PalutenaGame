#pragma once

class Pause;

class SoundManager
{
public:
	SoundManager();
	~SoundManager();

	void Init();
	void Update(){}
	void Draw(){}
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
	// BGMの音量を調整するメソッド
	void ChangeBGMVolume(int volume);
	// SEの音量を調整するメソッド
	void ChangeSEVolume(int volume);

	// 調整した音量に変換する
	void SetBgmVolume();
	void SetSeVolume();

private:
	int SeVolume;
	int BgmVolume;

	Pause* m_pPause;
};

