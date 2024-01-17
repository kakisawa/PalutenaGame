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
	// �A�C�e�����h���b�v����
	virtual void Start(Vec2 pos) override;

private:
	// �O���t�B�b�N�̃n���h��
	int m_handle;
};

