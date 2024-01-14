#pragma once
class Back
{
public:
	Back();
	~Back();

	void Init();
	void Update();
	void Draw();

	// グラフィックの設定
	void SetHandle(int handle) {Bg = handle; }


private:
	
	double x, y;		// 座標
	int Bg;				//グラフィックハンドル
};

