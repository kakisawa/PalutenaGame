#pragma once
#include "Rect.h"
#include "Vec2.h"

class Shot
{
public:
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

	// �e�̍������t���O
	bool LeftDir;
	// �e�̏�����t���O
	bool TopDir;

public:
	// �����蔻��̋�`���擾����
	Rect GetColRect() const { return m_colRect; }

	// �\���ʒu
	Vec2 m_pos;
	// �����蔻��̋�`
	Rect m_colRect;

public:

	Shot();
	~Shot();
	void Init();
	void Update(Player& player);
	void Draw(Player& player);
};