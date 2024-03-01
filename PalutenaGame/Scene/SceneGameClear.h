#pragma once
#include "SceneBase.h"
#include "Vec2.h"

class SoundManager;
class FontManager;
class Player;
class ColorManager;

class SceneGameClear :
    public SceneBase
{
public:

	SceneGameClear();
	~SceneGameClear();

	void Init();
	void Update();
	void Draw();
    void End();

    void StringDraw();  // 文字系の描画
    void BackDraw();    // 背景の描画
    void UIDraw();      // UI等の描画

	// シーンを終了させたいか
	bool IsSceneEnd() const;
	void SetHandle(int handle) { m_graph = handle; }
   
private:
    int m_titleGraph;       // タイトルグラフ
    int m_scoreGraph;       // スコアグラフ
    int m_select;           // 選択中のメニュー
    int m_cursorGraph;      // カーソルグラフ
    int m_selectUIGraph;    // UI
    int m_selectUIGraph2;   // UI
    int m_pushAGraph;       // Aボタンを押すグラフ
    int m_fadeLetter;       // 文字の点滅用カウンタ
    int m_fadeAlpha;        // フェードイン、アウト
    int m_resultScore;      // 獲得スコア

    float m_scrollX;    // スクロール移動量
     
    bool m_isSceneEnd;	// シーン終了フラグ

    enum Select
    {
        kScelectBackTitle, // ホーム画面に戻る
        kScelectEnd,        // ゲームを終わる

        kSclectNum,         // 項目数
    };
    struct Size         // 背景のサイズ
    {
        int m_width;
        int m_height;
    };

    // 選択中メニュー四角表示位置
    Vec2 m_selectPos;
    // SE/BGM
    SoundManager* m_pSoundManager;
    // フォント
    FontManager* m_pFontManager;
    // 色
    ColorManager* m_pColorManager;
};

