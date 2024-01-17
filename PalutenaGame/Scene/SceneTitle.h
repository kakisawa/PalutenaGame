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
        kSelectGameState,   // ゲームスタート
        kSclectOperation,   // 操作方法
        kSclectBack,        // 戻る
        kSclectEnd,         // ゲームを終わる
        kSclectNum,         // 項目数
    };

    int m_select;    // 選択中のメニュー


private:
    int TitleGraph;     // タイトルロゴグラフ
    bool m_isSceneEnd;	// シーン終了フラグ
    
    // 選択中メニュー四角表示位置
    Vec2 m_selectPos;
};