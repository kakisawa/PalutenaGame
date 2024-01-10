#pragma once
#include "EnemyBase.h"

#define ENEMY_NUM 1        // 本来 3

class DeathYourEnemy :
    public EnemyBase
{
public:
    DeathYourEnemy();
    ~DeathYourEnemy();

    void Init();
    void Update();
    void Draw();

    void Damage(int damage) override;

    // 表示位置
    Vec2 enemy[ENEMY_NUM];

    // 当たり判定用の矩形
    Rect m_colRect[ENEMY_NUM];
};