#pragma once
#include "ShotBase.h"
class ShotBible :
    public ShotBase
{
public:
    ShotBible();
    virtual ~ShotBible();

	virtual void Init() override;

	virtual void Update() override;
	virtual void Draw() override;

	// 弾をスタートさせる
	virtual void Start(Vec2 pos) override;

private:

	// 一定時間経過したら消す為に生成してからのフレームを数える
	int m_frameCount;	// インストラクタで初期化する
	
	// プレイヤーから見てどの方向にあるか
	// 弧度法で指定

	float m_angle;
};

