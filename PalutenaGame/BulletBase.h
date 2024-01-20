#pragma once
class BulletBase
{
public:
	BulletBase();
	virtual ~BulletBase();

	virtual void init();
	virtual void Update();
	virtual void Draw();
};

