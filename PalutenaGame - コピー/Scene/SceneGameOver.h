#pragma once
#include "SceneBase.h"
#include "Vec2.h"

class SoundManager;
class FontManager;

class SceneGameOver :
    public SceneBase
{
public:
    SceneGameOver();
    ~SceneGameOver();

    void Init();
    void Update();
    void Draw();
    void End();

    void StringDraw();
    void BackDraw();

    // シーンを終了させたいか
    bool IsSceneEnd() const;

    void SetHandle(int handle) { Graph = handle; }

private:
    enum Select
    {
        kScelectBackTitle, // ホーム画面に戻る
        kScelectEnd,        // ゲームを終わる

        kSclectNum,         // 項目数
    };

    int m_select;    // 選択中のメニュー
    int Cursor;      // カーソルグラフ
    int SelectUI;       // UI
    int SelectUI2;       // UI

    float m_scrollX;    // スクロール移動量

    struct Size         // 背景のサイズ
    {
        int width;
        int height;
    };

    int m_fadeAlpha;    // フェードイン、アウト 
    int m_fadeLetter;   // 文字の点滅用カウンタ
    bool m_isSceneEnd;	// シーン終了フラグ

    // 選択中メニュー四角表示位置
    Vec2 m_selectPos;

    // SE・BGM
    SoundManager* m_pSoundManager;
    // フォント
    FontManager* m_pFontManager;
};