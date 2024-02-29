#pragma once
#include "EnemyBase.h"

class SceneMain;
class PumpkinEnemy :
    public EnemyBase
{
public:
    PumpkinEnemy();
    ~PumpkinEnemy();

    virtual void Update() override;
    void Draw() override;

    void Start(float x, float y);

private:
    float m_sinRate;// sin()�ɗ^�������

    Vec2 m_basePos;
};