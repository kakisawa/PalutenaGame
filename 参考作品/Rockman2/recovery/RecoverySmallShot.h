#pragma once
#include "RecoveryBase.h"

/// <summary>
/// 弾小回復クラス
/// </summary>
class RecoverySmallShot : public RecoveryBase
{
public:
	RecoverySmallShot();
	virtual ~RecoverySmallShot();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Draw() override;
	// アイテムをドロップする
	virtual void Start(Vec2 pos) override;

private:

	// グラフィックのハンドル
	int m_handle;
};

