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
    // Šî€‹K’è ^‰E•ûŒü‚ÉˆÚ“®‚·‚éŠî€À•W
    // y¬•ª‚Ésin‚Ì’l‚ğ‘«‚µ‚Äã‰º‚É“®‚­‚æ‚¤‚É‚·‚é
    Vec2 m_basePos;
    // sin()‚É—^‚¦‚éˆø”
    float m_sinRate;

    // “G‚ÌˆÚ“®Šp“x
    float angle;
};