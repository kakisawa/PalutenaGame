#pragma once
#include "EnemyBase.h"

// class �쐬����N���X�� : public �p�����N���X
// public�ȊO�ɂ�private,protected���g�p�ł��邪���public
class EnemyLeft : public EnemyBase
{
public:
	EnemyLeft();
	virtual ~EnemyLeft();

	// ���̂Ƃ���p���������̂܂܎g���̂ŕs�v
	// void Init();
	// void Update();
	// void Draw();

	virtual void Update() override;

	virtual void Start() override;

private:
	// ��K�� �^�E�����Ɉړ��������W
	// y������sin�̒l�𑫂��ď㉺�ɓ����悤�ɂ���
	Vec2 m_basePos;
	// sin()�ɗ^�������
	float m_sinRate;
};

