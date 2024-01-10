#pragma once
#include "EnemyBase.h"

#define ENEMY_NUM 1

class PumpkinEnemy :
    public EnemyBase
{
public:
    PumpkinEnemy();
    ~PumpkinEnemy() {}

    void Init();
    void Update();
    void Draw();

    void Damage(int damage) override;

    // �\���ʒu
    Vec2 enemy[ENEMY_NUM];

    // �����蔻��p�̋�`
    Rect m_colRect[ENEMY_NUM];

private:
};

