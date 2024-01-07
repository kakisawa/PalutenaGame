#pragma once
#include "EnemyBase.h"

#define ENEMY_NUM 2        // �{��17

class MozueyeEnemy : public EnemyBase {
public:
    MozueyeEnemy();
    ~MozueyeEnemy() {}

    void Init();
    void Update();
    void Draw();

    void Damage(int damage) override;

    // �\���ʒu
    Vec2 enemy[ENEMY_NUM];

    // �����蔻��p�̋�`
    Rect m_colRect;


private:
};

