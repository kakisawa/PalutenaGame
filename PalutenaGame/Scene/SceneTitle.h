#pragma once
#include "SceneBase.h"
#include "Vec2.h"

class SoundManager;
class FontManager;
class ColorManager;
class SceneTitle :
    public SceneBase
{
public:
    SceneTitle();
    ~SceneTitle();

    void Init();
    void Update();
    void Draw();
    void End();

    void StringDraw();      // 文字の描画
    void BackDraw();        // 背景のスクロール描画
    void SetHandle(int handle) { m_graph = handle; }    // 画像の読み込み

    bool IsSceneEnd() const;     // ゲームセレクトシーンへ向かうか
    // 次どのステージに行くか
    bool ToStage() const;
    bool ToExplanation() const;

private:
    int m_titleGraph;       // タイトルロゴ画像
    int m_cursorGraph;      // カーソル画像
    int m_pushAGraph;       // 「Aボタンで決定」画像
    int m_selectUIGraph;    // UI画像
    int m_selectUIGraph2;   // UI画像
    int m_select;           // 選択中のメニュー
    int m_fadeLetter;       // 文字の点滅用カウンタ
    int m_fadeAlpha;        // フェードイン、アウト

    float m_scrollX;        // スクロール移動量

    bool m_isSceneEnd;	    // シーン終了フラグ
    bool m_isToSelect;      // ステージセレクト画面に行くか
    bool m_isToExplanation; // 説明シーンに行くか 

    struct Size         // 背景のサイズ
    {
        int m_width;
        int m_height;
    };

    enum Select
    {
        kSelectGameStart,   // ゲームスタート
        kSclectOperation,   // 操作方法
        kSclectEnd,         // ゲームを終わる

        kSclectNum,         // 項目数
        kSclectBack,        // 戻る
    };

    // 選択中メニュー四角表示位置
    Vec2 m_selectPos;
    // 背景の表示位置
    Vec2 m_bgPos;
    // フォントのポインタ
    FontManager* m_pFontManager;
    // SE・BGM
    SoundManager* m_pSoundManager;
    // 色
    ColorManager* m_pColorManager;
};