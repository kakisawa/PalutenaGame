#pragma once
class Shot
{
public:
	Shot();
	~Shot();

	void Init();
	void Update();
	void Draw();

private:
	// �e�̉摜
	int Graph;

	// �e�̉摜�T�C�Y
	int W, H;
};

