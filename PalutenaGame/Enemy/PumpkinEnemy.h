#pragma once
#include "EnemyBase.h"

//namespace
//{
//    // ���ڂ���o����
//    constexpr int PumpMax = 1;	// 10���A�o���ĂȂ�
//}

class SceneMain;
class PumpkinEnemy :
    public EnemyBase
{
public:
    PumpkinEnemy();
    ~PumpkinEnemy();

    void Init(){}
    virtual void Update() override;
    void Draw(){}
 
private:
    // ��K�� �^�E�����Ɉړ��������W
    // y������sin�̒l�𑫂��ď㉺�ɓ����悤�ɂ���
    Vec2 m_basePos;
    // sin()�ɗ^�������
    float m_sinRate;
};

