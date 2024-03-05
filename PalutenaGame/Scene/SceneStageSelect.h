#include "SceneBase.h"
#include "Vec2.h"

class SoundManager;
class FontManager;
class ColorManager;

class SceneStageSelect :
    public SceneBase
{
public:
    SceneStageSelect();
    ~SceneStageSelect();

    void Init();
    void Update();
    void Draw();
    void End();

    void StringDraw();          // 文字の描画
    void BackDraw();            // 背景のスクロール描画
    bool IsSceneEnd() const;    // シーンを終了させたいか

    // 次どのステージに行くか
    bool ToStage1() const { return m_isStage1; }
    bool ToStage2() const { return m_isStage2; }
    bool ToBackTitke() const { return m_isBackTitle; }

private:
    int m_explanationGraph;   // 操作説明画像
    int m_cursorGraph;        // カーソル画像
    int m_pushAGraph;         // 「Aボタンで決定」
    int m_selectUIGraph;      // UI
    int m_selectUIGraph2;     // UI
    int m_select;             // 選択中のメニュー
    int m_fadeAlpha;          // フェードイン、アウト
    int m_fadeLetter;         // 文字の点滅用カウンタ
    
    float m_scrollX;           // スクロール移動量グラフ
   
    // ステージ1へ行くか、ステージ２へ行くか、タイトル画面に戻るか
    bool m_isStage1;
    bool m_isStage2;
    bool m_isBackTitle;
   
    enum Select         // セレクト選択肢
    {
        kStage1,        // ステージ1
        kStage2,        // ステージ2
        kBackTitle,     // タイトル画面に戻る

        kSclectNum,     // 項目数
    };
    struct Size         // 背景のサイズ
    {
        int m_width;
        int m_height;
    };

    // 選択中メニュー四角表示位置
    Vec2 m_selectPos;
    // 背景の表示位置
    Vec2 m_bgPos;
    // SE/BGM
    SoundManager* m_pSoundManager;
    // フォント
    FontManager* m_pFontManager;
    // 色
    ColorManager* m_pColorManager;
};

