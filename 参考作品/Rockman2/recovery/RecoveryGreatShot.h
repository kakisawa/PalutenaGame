#pragma once
#include "RecoveryBase.h"

/// <summary>
/// 弾大回復クラス
/// </summary>
class RecoveryGreatShot : public RecoveryBase
{
public:
	RecoveryGreatShot();
	virtual ~RecoveryGreatShot();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Draw() override;
	// アイテムをドロップする
	virtual void Start(Vec2 pos) override;

private:
	// グラフィックのハンドル
	int m_handle;
}; 
