#pragma once
#include "RecoveryBase.h"

/// <summary>
/// HP小回復クラス
/// </summary>
class RecoverySmallHp : public RecoveryBase
{
public:
	RecoverySmallHp();
	virtual ~RecoverySmallHp();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Draw() override;
	// アイテムをドロップする
	virtual void Start(Vec2 pos) override;

private:
	// グラフィックのハンドル
	int m_handle;
};

