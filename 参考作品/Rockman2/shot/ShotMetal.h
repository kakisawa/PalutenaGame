#pragma once
#include "ShotBase.h"

class ShotMetal : public ShotBase
{
public:
	ShotMetal();
	virtual ~ShotMetal();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Draw() override;

	// �e���X�^�[�g������
	virtual void Start(Vec2 pos) override;

private:
	// �O���t�B�b�N�̃n���h��
	int m_handle;

	// ���݂̒e�G�l���M�[��
	float m_energy;
};

