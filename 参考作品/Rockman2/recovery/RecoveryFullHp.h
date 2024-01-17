#pragma once
#include "RecoveryBase.h"

/// <summary>
/// HP全回復アイテムクラス
/// </summary>
class RecoveryFullHp : public RecoveryBase
{
public:
	RecoveryFullHp();
	~RecoveryFullHp();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Draw() override;
	// アイテムをドロップする
	virtual void Start(Vec2 pos) override;

private:
	// グラフィックのハンドル
	int m_handle;
};

