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

	// �O���t�B�b�N�̐ݒ�
	void SetHandle(int handle) {Bg = handle; }
	void SetHandle2(int handle2) { Bg2 = handle2; }
private:
	
	double x, y;		// ���W
	int Bg;				//�O���t�B�b�N�n���h��
	int Bg2;
};

