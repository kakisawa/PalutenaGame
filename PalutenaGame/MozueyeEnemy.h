#pragma once
#include "EnemyBase.h"

#define ENEMY_NUM 3        // 本来17

class MozueyeEnemy : public EnemyBase {
public:
    MozueyeEnemy();
    ~MozueyeEnemy() {}

    void Init();
    void Update();
    void Draw();

    void Damage(int damage) override;

    // 表示位置
    Vec2 enemy[ENEMY_NUM];

    // 当たり判定用の矩形
    Rect m_colRect[ENEMY_NUM];


private:
};

