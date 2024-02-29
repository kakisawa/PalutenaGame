#pragma once
#include "EnemyBase.h"

class DeathYourEnemy :
    public EnemyBase
{
public:
    DeathYourEnemy();
    ~DeathYourEnemy();

    virtual void Init(Player* pPlayer) override;
    virtual void Update() override;
    virtual void Draw() override;

    void Start(float x, float y);

private:
    float m_sinRate;    // sin()に与える引数
    float m_angle;      // 敵の移動角度

    Vec2 m_basePos;    
};