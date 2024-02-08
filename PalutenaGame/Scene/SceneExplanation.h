#pragma once
#include "SceneBase.h"
#include "Vec2.h"
#include <vector>

class SoundManager;
class ColorManager;

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

    void BackDraw();

    // シーンを終了させたいか
    bool IsSceneEnd() const;
    void SetHandle(int handle) { Graph = handle; }

private:
    int BgGraph;
    float m_scrollX;    // スクロール移動量

    int m_fadeAlpha;    // フェードイン、アウト
    bool m_isSceneEnd;	// シーン終了フラグ

    struct Size         // 背景のサイズ
    {
        int width;
        int height;
    };

    // SE/BGM
    SoundManager* m_pSoundManager;
    // 色
    ColorManager* m_pColorManager;
};

