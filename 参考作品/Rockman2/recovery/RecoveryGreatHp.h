#pragma once
#include "RecoveryBase.h"

/// <summary>
/// HP大回復クラス
/// </summary>
class RecoveryGreatHp : public RecoveryBase
{
public:
	RecoveryGreatHp();
	virtual ~RecoveryGreatHp();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Draw() override;
	// アイテムをドロップする
	virtual void Start(Vec2 pos) override;

private:
	// グラフィックのハンドル
	int m_handle;
};

