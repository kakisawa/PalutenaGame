#pragma once
#include "EnemyBase.h"

//namespace
//{
//    // ���Y�A�C�o����
//    constexpr int MozuMax = 1;	// 17
//}

class SceneMain;
class MozueyeEnemy : public EnemyBase {
public:
    MozueyeEnemy();
    ~MozueyeEnemy();

    void Init() {}
    void Update();
    void Draw(){}


private:
    // ��K�� �^�E�����Ɉړ��������W
    // y������sin�̒l�𑫂��ď㉺�ɓ����悤�ɂ���
    Vec2 m_basePos;
    // sin()�ɗ^�������
    float m_sinRate;
};

