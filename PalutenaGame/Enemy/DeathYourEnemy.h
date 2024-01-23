#pragma once
#include "EnemyBase.h"

//namespace
//{
//    // 死出現数
//    constexpr int DeathMax = 2;	// 3
//}

class DeathYourEnemy :
    public EnemyBase
{
public:
    DeathYourEnemy();
    ~DeathYourEnemy();

    void Init(){}
    virtual void Update() override;

private:
    // 基準規定 真右方向に移動する基準座標
    // y成分にsinの値を足して上下に動くようにする
    Vec2 m_basePos;
    // sin()に与える引数
    float m_sinRate;

    // 敵の移動角度
    float angle;
};