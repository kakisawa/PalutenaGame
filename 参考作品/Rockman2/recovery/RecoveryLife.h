#pragma once
#include "RecoveryBase.h"

class RecoveryLife : public RecoveryBase
{
public:
	RecoveryLife();
	virtual ~RecoveryLife();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Draw() override;
	// アイテムをドロップする
	virtual void Start(Vec2 pos) override;

private:
	// グラフィックのハンドル
	int m_handle;
};

