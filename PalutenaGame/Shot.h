#pragma once

// �V���b�g�̐�
#define SHOT 20

struct Shot {

	// �V���b�g�̍��W
	int X;
	int Y;

	// �V���b�g�̉摜
	int Graph;

	// �e����ʏ�ɑ��݂��Ă��邩�ێ�����ϐ�
	bool Flag;

	// �V���b�g�̉摜�T�C�Y
	int W;
	int H;
};

void InitShot(Shot& shot);
void UpdateShot(Shot& shot);
void DrawShot(Shot& shot);



// x=16
// y=8