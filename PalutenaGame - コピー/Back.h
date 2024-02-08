#pragma once
class Back
{
public:
	Back();
	~Back();

	void Init(){}
	void Update(){}
	void Draw(){}

	void DrawBg();
	void DrawGround();

	// グラフィックの設定
	void SetHandle(int handle) {Bg = handle; }
	void SetHandle2(int handle2) { Bg2 = handle2; }
private:
	
	double x, y;		// 座標
	int Bg;				//グラフィックハンドル
	int Bg2;
};

