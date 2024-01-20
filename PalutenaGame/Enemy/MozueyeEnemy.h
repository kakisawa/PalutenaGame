#pragma once
#include "EnemyBase.h"

//namespace
//{
//    // モズアイ出現数
//    constexpr int MozuMax = 1;	// 17
//}

class SceneMain;
class MozueyeEnemy : public EnemyBase {
public:
    MozueyeEnemy();
    ~MozueyeEnemy();

    void Init() {}
    void Update();
    void Draw(){}


private:
    // 基準規定 真右方向に移動する基準座標
    // y成分にsinの値を足して上下に動くようにする
    Vec2 m_basePos;
    // sin()に与える引数
    float m_sinRate;
};

