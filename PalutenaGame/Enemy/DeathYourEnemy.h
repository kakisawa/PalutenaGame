#pragma once
#include "EnemyBase.h"

//namespace
//{
//    // ���o����
//    constexpr int DeathMax = 2;	// 3
//}

class DeathYourEnemy :
    public EnemyBase
{
public:
    DeathYourEnemy();
    ~DeathYourEnemy();

    void Init(){}
    virtual void Update() override;

private:
    // ��K�� �^�E�����Ɉړ��������W
    // y������sin�̒l�𑫂��ď㉺�ɓ����悤�ɂ���
    Vec2 m_basePos;
    // sin()�ɗ^�������
    float m_sinRate;

    // �G�̈ړ��p�x
    float angle;
};