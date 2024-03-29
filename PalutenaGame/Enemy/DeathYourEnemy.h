#pragma once
#include "EnemyBase.h"

class DeathYourEnemy :public EnemyBase
{
public:
    DeathYourEnemy();
    ~DeathYourEnemy();

    virtual void Init(Player* pPlayer) override;
    virtual void Update() override;
    virtual void Draw() override;

    void Start(float x, float y);   // 敵出現位置設定

private:
    float m_angle;      // 敵の移動角度  
};