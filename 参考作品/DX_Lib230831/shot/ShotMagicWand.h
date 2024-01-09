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

	// 弾をスタートさせる
	virtual void Start(Vec2 pos) override;

private:
	// 残像を表示するために過去の位置を覚えておく
	std::vector<Vec2> m_posLog;
};

