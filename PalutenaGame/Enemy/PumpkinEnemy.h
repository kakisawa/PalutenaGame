#pragma once
#include "EnemyBase.h"

#define ENEMY_NUM 1

class SceneMain;
class PumpkinEnemy :
    public EnemyBase
{
public:
    PumpkinEnemy();
    ~PumpkinEnemy() {}

    void Init();
    void Update();
    void Draw();

    // �O���t�B�b�N�̐ݒ�
    void SetHandle(int handle) { EGraph = handle; }

    void Damage(int damage) override;

    // �\���ʒu
    Vec2 enemy[ENEMY_NUM];

    // �����蔻��p�̋�`
    Rect m_colRect[ENEMY_NUM];

private:
};

