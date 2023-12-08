#pragma once
#include "ShotBase.h"
#include "Vec2.h"
#include <vector>

class ShotMagicWand :
    public ShotBase
{
public:
    ShotMagicWand();
    virtual ~ShotMagicWand();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Draw() override;

	// �e���X�^�[�g������
	virtual void Start(Vec2 pos) override;

private:
	// �c����\�����邽�߂ɉߋ��̈ʒu���o���Ă���
	std::vector<Vec2> m_posLog;
};

