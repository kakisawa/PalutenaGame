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

    void Start(float x,float y);     // 敵出現位置設定
 };

