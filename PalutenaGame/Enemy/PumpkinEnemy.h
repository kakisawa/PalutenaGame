#pragma once
#include "EnemyBase.h"

#define ENEMY_NUM 1

class SceneMain;
class PumpkinEnemy :
    public EnemyBase
{
public:
    PumpkinEnemy();
    ~PumpkinEnemy() {}

    void Init();
    void Update();
    void Draw();

    // グラフィックの設定
    void SetHandle(int handle) { EGraph = handle; }

    void Damage(int damage) override;

    // 表示位置
    Vec2 enemy[ENEMY_NUM];

    // 当たり判定用の矩形
    Rect m_colRect[ENEMY_NUM];

private:
};

