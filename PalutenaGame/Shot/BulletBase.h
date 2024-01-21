#pragma once

class Player;
class BulletBase
{
public:
	BulletBase();
	virtual ~BulletBase();

	virtual void init();
	virtual void Update();
	virtual void Draw();

	void RightShot();
	void LeftShot();
	void UpShot();

protected:
	int Se;

	int x;
	int y;

public:
	// ÉvÉåÉCÉÑÅ[
	Player* m_pPlayer;
};

