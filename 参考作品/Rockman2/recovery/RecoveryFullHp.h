#pragma once
#include "RecoveryBase.h"

/// <summary>
/// HP�S�񕜃A�C�e���N���X
/// </summary>
class RecoveryFullHp : public RecoveryBase
{
public:
	RecoveryFullHp();
	~RecoveryFullHp();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Draw() override;
	// �A�C�e�����h���b�v����
	virtual void Start(Vec2 pos) override;

private:
	// �O���t�B�b�N�̃n���h��
	int m_handle;
};

