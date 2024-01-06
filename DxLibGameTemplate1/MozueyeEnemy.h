#pragma once
#include "EnemyBase.h"
class MozueyeEnemy : public EnemyBase{
public:
    MozueyeEnemy();
    ~MozueyeEnemy(){}

    void Init();
    void Update();
    void Draw();

    void Damage(int damage) override; 

private:
};

