#pragma once
#include "RecoveryBase.h"

/// <summary>
/// HP��񕜃N���X
/// </summary>
class RecoveryGreatHp : public RecoveryBase
{
public:
	RecoveryGreatHp();
	virtual ~RecoveryGreatHp();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Draw() override;
	// �A�C�e�����h���b�v����
	virtual void Start(Vec2 pos) override;

private:
	// �O���t�B�b�N�̃n���h��
	int m_handle;
};

