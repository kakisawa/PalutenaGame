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
    // 基準規定 真右方向に移動する基準座標
    // y成分にsinの値を足して上下に動くようにする
    Vec2 m_basePos;
    // sin()に与える引数
    float m_sinRate;

    // 敵の移動角度
    float angle;
};