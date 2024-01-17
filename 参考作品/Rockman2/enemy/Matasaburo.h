#pragma once
#include "EnemyBase.h"
#include "Vec2.h"

/// <summary>
/// ‚Ü‚½‚³‚Ô‚ë‚¤‚ÌƒNƒ‰ƒX
/// </summary>
class Matasaburo : public EnemyBase
{
public:
	Matasaburo();
	virtual ~Matasaburo();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void Start() override;
	virtual void OnDamage() override;

private:
	int m_handle;
	int m_hp;
};

