#pragma once
#include "SceneBase.h"
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

    // シーンを終了させたいか
    bool IsSceneEnd() const;

    void SetHandle(int handle) { Graph = handle; }

private:

    bool m_isSceneEnd;	// シーン終了フラグ
    // true:タイトルを終了してゲームへ


};