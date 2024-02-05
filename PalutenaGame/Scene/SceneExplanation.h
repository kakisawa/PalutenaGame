#pragma once
#include "SceneBase.h"
#include "Vec2.h"
#include <vector>

class SoundManager;
class Player;
class Shot;
class DeathYourEnemy;

namespace {
    // 死最大出現数
    constexpr int DeathMax = 1;
    // 画面内に同時に出せる弾の数
    constexpr int kShotMax = 30;
}

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

    // グラフィックのハンドル
    int m_gameScreenHandle;
    int m_playerHandle;		// プレイヤー
    int m_enemyHandle;		// 敵





    int m_fadeAlpha;    // フェードイン、アウト
    bool m_isSceneEnd;	// シーン終了フラグ

    struct Size         // 背景のサイズ
    {
        int width;
        int height;
    };

    // プレイヤー
    Player* m_pPlayer;
    // 弾
    Shot* m_pShot[kShotMax];
    // エネミー
    std::vector<DeathYourEnemy*> m_pDeathYourEnemy;
    SoundManager* m_pSoundManager;
};

