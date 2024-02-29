#pragma once
#include "SceneBase.h"
#include "Vec2.h"
#include <vector>

class SoundManager;
class ColorManager;
class FontManager;

class SceneOption:
	public SceneBase
{
public:
	SceneOption();
	~SceneOption();

	void Init();
	void Update();
	void Draw();
	void End();

	void BackDraw();

	// シーンを終了させたいか
	bool IsSceneEnd() const;
	void SetHandle(int handle) { m_graph = handle; }

private:
	int m_bgGraph;
	int m_pushAGraph;          // 「Aボタンで決定」グラフ
	float m_scrollX;    // スクロール移動量

	int m_fadeAlpha;    // フェードイン、アウト
	int m_fadeLetter;   // 文字の点滅用カウンタ
	bool m_isSceneEnd;	// シーン終了フラグ

	struct Size         // 背景のサイズ
	{
		int m_width;
		int m_height;
	};

	// SE/BGM
	SoundManager* m_pSoundManager;
	// 色
	ColorManager* m_pColorManager;
	// フォント
	FontManager* m_pFontManager;
};