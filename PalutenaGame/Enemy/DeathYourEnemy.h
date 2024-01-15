#pragma once
#include "EnemyBase.h"

class DeathYourEnemy :
    public EnemyBase
{
public:
    DeathYourEnemy();
    ~DeathYourEnemy();

    void Init(){}
    virtual void Update() override;

    void Damage(int damage) override;

private:
    // ��K�� �^�E�����Ɉړ��������W
    // y������sin�̒l�𑫂��ď㉺�ɓ����悤�ɂ���
    Vec2 m_basePos;
    // sin()�ɗ^�������
    float m_sinRate;
};