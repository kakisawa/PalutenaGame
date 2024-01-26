#pragma once
#include "SceneBase.h"
class SceneExplanation :
    public SceneBase
{
public:
    SceneExplanation();
    ~SceneExplanation();

    void Init();
    void Update();
    void Draw();
    void End();


    // シーンを終了させたいか
    bool IsSceneEnd() const;
    void SetHandle(int handle) { Graph = handle; }

private:
    int m_fadeAlpha;    // フェードイン、アウト
    bool m_isSceneEnd;	// シーン終了フラグ
};

