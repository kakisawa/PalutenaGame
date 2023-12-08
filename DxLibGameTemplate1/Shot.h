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
	// ’e‚Ì‰æ‘œ
	int Graph;

	// ’e‚Ì‰æ‘œƒTƒCƒY
	int W, H;
};

