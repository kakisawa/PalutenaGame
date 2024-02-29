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

	// BGMの音量を調整するメソッド
	void ChangeBGMVolume(float volume);
	// SEの音量を調整するメソッド
	void ChangeSEVolume(float volume);

	// 調整した音量に変換する
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
	int m_select;       // 選択中のメニュー

	float m_seVolume;
	float m_bgmVolume;

	bool m_isSceneEnd;

	enum Select
	{
		kBgmVolume,   // BGM
		kSeVolume,    // SE
		kBack,		  // 戻る

		kSclectNum,   // 項目数
	};
	
	// 選択中メニュー四角表示位置
	Vec2 m_selectPos;

	Pause* m_pPause;
	// フォントのポインタ
	FontManager* m_pFontManager;
	// 色
	ColorManager* m_pColorManager;
};