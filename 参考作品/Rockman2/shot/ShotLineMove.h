#pragma once
#include "ShotBase.h"
class ShotLineMove : public ShotBase
{
public:
	ShotLineMove();
	virtual ~ShotLineMove();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Draw() override;

	// 弾をスタートさせる
	virtual void Start(Vec2 pos) override;

	// 現在のエネルギー数を取得する
	float GetLineMoveEnergy() const { return m_energy; }
	// 現在の位置を取得する
	Vec2 GetPos() const { return m_pos; }

	// 弾の種類を取得する
	virtual ShotType GetShotType() const { return ShotType::kShotLineMove; }

private:
	// グラフィックのハンドル
	int m_handle;
	// 静止する時間
	int m_stopFrame;
	// 現在の弾エネルギー数
	float m_energy;
};

