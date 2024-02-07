#include "SceneBase.h"
#include "Vec2.h"

class SoundManager;
class FontManager;

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

    void StringDraw();      // 文字の描画
    void BackDraw();        // 背景のスクロール描画

    void SetHandle(int handle) { Graph = handle; }

    // シーンを終了させたいか
    bool IsSceneEnd() const;

    // 次どのステージに行くか
    bool ToStage1() const { return isStage1; }
    bool ToStage2() const { return isStage2; }
    bool ToBackTitke() const { return isBackTitle; }

private:
    int ExplanationGraph;   // 操作説明グラフ
    int Cursor;             // カーソルグラフ
    int PushA;              // 「Aボタンで決定」
    int SelectUI;        // UI
    int SelectUI2;       // UI

    enum Select
    {
        kStage1,        // ステージ1
        kStage2,        // ステージ2
        kBackTitle,     // タイトル画面に戻る

        kSclectNum,     // 項目数
    };

    int m_select;       // 選択中のメニュー
    int m_fadeAlpha;    // フェードイン、アウト
    int m_fadeLetter;   // 文字の点滅用カウンタ
    float m_scrollX;    // スクロール移動量グラフ

    struct Size         // 背景のサイズ
    {
        int width;
        int height;
    };

    // ステージ1へ行くか、ステージ２へ行くか、タイトル画面に戻るか
    bool isStage1;
    bool isStage2;
    bool isBackTitle;

    // 選択中メニュー四角表示位置
    Vec2 m_selectPos;
    // 背景の表示位置
    Vec2 m_bgPos;

    // SE/BGM
    SoundManager* m_pSoundManager;
    // フォント
    FontManager* m_pFontManager;
};

