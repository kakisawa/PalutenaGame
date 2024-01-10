#pragma once
#include "EnemyBase.h"

#define ENEMY_NUM 1        // �{�� 3

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

    // �\���ʒu
    Vec2 enemy[ENEMY_NUM];

    // �����蔻��p�̋�`
    Rect m_colRect[ENEMY_NUM];
};