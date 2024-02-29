#pragma once
#include "EnemyBase.h"

class SceneMain;
class MozueyeEnemy : public EnemyBase {
public:
    MozueyeEnemy();
    ~MozueyeEnemy();

    void Init(Player* pPlayer) override;
    void Update() override;
    void Draw() override;

    void Start(float x,float y);

private:
    float m_sinRate; // sin()‚É—^‚¦‚éˆø”
    
    Vec2 m_basePos;    
};

