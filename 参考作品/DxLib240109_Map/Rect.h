#pragma once

#include "Vec2.h"

// ��`�̃f�[�^�Ǘ�
class Rect
{
public:
	float top;
	float bottom;
	float left;
	float right;
public:
	Rect() :
		top(0),
		bottom(0),
		left(0),
		right(0)
	{
	}
	float getWidth() const { return right - left; }
	float getHeight() const { return bottom - top; }

	// �e���W�擾
	Vec2 getCenter();

	// ������(�d�Ȃ�)����
	bool isCol(Rect rect);

	// ���W����`���Ɋ܂܂�邩�ǂ�������


	// rect�f�[�^�ݒ�

	/// <summary>
	/// ������W�ƃT�C�Y����Rect�f�[�^��ݒ�
	/// </summary>
	/// <param name="posTL">������W</param>
	/// <param name="size">�T�C�Y</param>
	void set_TL_Size(Vec2 posTL, Vec2 size);
};

