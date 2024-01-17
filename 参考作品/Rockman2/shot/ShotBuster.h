#pragma once
#include "ShotBase.h"
#include <vector>

class ShotBuster : public ShotBase
{
public:
	ShotBuster();
	virtual ~ShotBuster();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Draw() override;

	// �e���X�^�[�g������
	virtual void Start(Vec2 pos) override;

private:
	// �O���t�B�b�N�̃n���h��
	int m_handle;
};

