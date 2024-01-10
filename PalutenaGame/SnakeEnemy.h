#pragma once
#include "EnemyBase.h"

#define ENEMY_NUM 15

class SnakeEnemy :
    public EnemyBase
{
public:
    SnakeEnemy();
    ~SnakeEnemy() {}

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

