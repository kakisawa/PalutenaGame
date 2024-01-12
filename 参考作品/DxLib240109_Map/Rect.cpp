#include "Rect.h"

Vec2 Rect::getCenter()
{
	return Vec2((left + right)/2, (top + bottom)/2);
}

bool Rect::isCol(Rect rect)
{
	if (top > rect.bottom)	return false;
	if (bottom < rect.top)	return false;
	if (left > rect.right)	return false;
	if (right < rect.left)	return false;

	return true;
}

void Rect::set_TL_Size(Vec2 posTL, Vec2 size)
{
	top = posTL.y;
	bottom = posTL.y + size.y;
	left = posTL.x;
	right = posTL.x + size.x;
}
