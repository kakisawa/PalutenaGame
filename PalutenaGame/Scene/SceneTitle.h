#pragma once
#include "SceneBase.h"
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
    int TitleGraph;     // タイトルロゴグラフ

    bool m_isSceneEnd;	// シーン終了フラグ
    // true:タイトルを終了してゲームへ
};