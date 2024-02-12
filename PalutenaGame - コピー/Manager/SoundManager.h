#pragma once
#include <Vec2.h>

namespace {
	// 音量の最大
	constexpr int MaxVolume = 255;

	// 初期音量
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

	enum Select
	{
		kBgmVolume,   // BGM
		kSeVolume,    // SE
		kBack,		  // 戻る

		kSclectNum,   // 項目数
	};
	int m_select;       // 選択中のメニュー


	// 選択中メニュー四角表示位置
	Vec2 m_selectPos;

	Pause* m_pPause;
	// フォントのポインタ
	FontManager* m_pFontManager;
	// 色
	ColorManager* m_pColorManager;
};

