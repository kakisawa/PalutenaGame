#pragma once
#include "SceneBase.h"
#include "Vec2.h"

class SceneTitle :
    public SceneBase
{
public:
    SceneTitle();
    ~SceneTitle() {}

    void Init();
    void Update();
    void Draw();
    void End();

    // シーンを終了させたいか
    bool IsSceneEnd() const;

    void SetHandle(int handle) { Graph = handle; }

private:
    enum Select
    {
        kSclectOperation,   // 操作方法
        kSelectGameStart,   // ゲームスタート
        kSclectEnd,         // ゲームを終わる

        kSclectNum,         // 項目数

        kSclectBack,        // 戻る
    };

    int m_select;    // 選択中のメニュー

private:
    int x, y;           // タイトルロゴ座標

    int TitleGraph;     // タイトルロゴグラフ
    int m_fadeAlpha;    // フェードイン、アウト
    bool m_isSceneEnd;	// シーン終了フラグ

    // 選択中メニュー四角表示位置
    Vec2 m_selectPos;
};