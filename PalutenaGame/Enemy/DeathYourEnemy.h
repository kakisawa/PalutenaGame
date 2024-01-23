#pragma once
#include "EnemyBase.h"

class DeathYourEnemy :
    public EnemyBase
{
public:
    DeathYourEnemy();
    ~DeathYourEnemy();

    void Init();
    virtual void Update() override;

    void Start();

private:
    // Šî€‹K’è ^‰E•ûŒü‚ÉˆÚ“®‚·‚éŠî€À•W
    // y¬•ª‚Ésin‚Ì’l‚ğ‘«‚µ‚Äã‰º‚É“®‚­‚æ‚¤‚É‚·‚é
    Vec2 m_basePos;
    // sin()‚É—^‚¦‚éˆø”
    float m_sinRate;

    // “G‚ÌˆÚ“®Šp“x
    float angle;
};