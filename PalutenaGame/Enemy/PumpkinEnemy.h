#pragma once
#include "EnemyBase.h"

class SceneMain;
class Player;
class PumpkinEnemy :
    public EnemyBase
{
public:
    PumpkinEnemy();
    ~PumpkinEnemy();

    void Init(){}
    virtual void Update() override;
    void Draw(){}

    void Start();

    // �����o�[�ϐ��ɃA�N�Z�X����
    void SetPlayer(Player* pPlayer) { m_pPlayer = pPlayer; }
 
private:
    // ��K�� �^�E�����Ɉړ��������W
    // y������sin�̒l�𑫂��ď㉺�ɓ����悤�ɂ���
    Vec2 m_basePos;
    // sin()�ɗ^�������
    float m_sinRate;

    Player* m_pPlayer;
};