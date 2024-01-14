#pragma once
#include "EnemyBase.h"

#define ENEMY_NUM 1        // �{��17

class SceneMain;
class MozueyeEnemy : public EnemyBase {
public:
    MozueyeEnemy();
    ~MozueyeEnemy() {}

    void Init();
    void Update();
    void Draw();

    void Damage(int damage) override;

    // �O���t�B�b�N�̐ݒ�
    void SetHandle(int handle) { EGraph = handle; }

    // �\���ʒu
    Vec2 enemy[ENEMY_NUM];

    // �����蔻��p�̋�`
    Rect m_colRect[ENEMY_NUM];

private:
};

