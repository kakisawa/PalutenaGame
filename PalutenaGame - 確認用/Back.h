#pragma once
class Back
{
public:
	Back();
	~Back();

	void Init();
	void Update();
	void Draw();

	// �O���t�B�b�N�̐ݒ�
	void SetHandle(int handle) {Bg = handle; }


private:
	
	double x, y;		// ���W
	int Bg;				//�O���t�B�b�N�n���h��
};

